#include "opt-A2.h"
#include <file_syscalls.h>
#include <vfs.h>
#include <proc.h>
#include <kern/fcntl.h>	
#include <copyinout.h>

struct fd_table *curfdt;
int DEADBEEF = 0xdeadbeef;

// open
int sys_open(const char *filename, int flags, int mode, int *return_val){
	struct vnode *v;
	int result;
	struct file_des *fd;

	// kprintf("In open;\n");
	if (filename == NULL){
	}

	int * temp_pt = kmalloc(sizeof(*filename));
	result = copyin((userptr_t)filename, temp_pt, sizeof(*filename));
	kfree(temp_pt);
	if (result == EFAULT){
		return result;
	}

	result = vfs_open((char*)filename, flags, mode, &v);

	if (result) {
		return result;
	}

	// kprintf("Creating fd;\n");
	fd = fd_create(v, flags, 0);

	// kprintf("Created fd;\n");
	if (curthread == NULL){
		return -2;
	}

	curfdt = curthread->fdt;
	int new_fd = (int)fd_table_add_fd(curfdt, fd);

	if (new_fd == -1){
		return 28;
		// Open too many files.
	}

	*return_val = new_fd;

	// vfs_close(v);
	return 0;
}

// read
int
sys_read(int fd, void *buf, size_t buflen, int *return_val){
	if (fd == DEADBEEF){
		return 30;		
	}
	// kprintf("In Read \n");
	curfdt = curthread->fdt;
	struct file_des *file_d;
	file_d = array_get(curfdt->fds, fd);
	if ((file_d == NULL) || (file_d->flag == 1)){
		return 30;
		// DEBUG mode is not opened or is write only
	}
	else {
		struct iovec iov;
		struct uio u;
		int result;

		iov.iov_ubase = buf;
		iov.iov_len = buflen;

		u.uio_iov = &iov;
		u.uio_iovcnt = 1;
		u.uio_offset = file_d->offset;
		u.uio_resid = buflen;
		u.uio_segflg = UIO_USERSPACE;
		u.uio_rw = UIO_READ;
		u.uio_space = curproc_getas();

		result = VOP_READ(file_d->vnode, &u);

		if (result){
			return result;
		}

		file_d->offset = u.uio_offset;
		if (u.uio_resid == 0){
			*return_val = buflen;
		}
		else {
			*return_val = buflen-u.uio_resid;
		}
	}
	return 0;
}

// write
int
sys_write(int fd, const void *buf, size_t nbytes, int *return_val){
	if (fd == DEADBEEF){
		return 30;		
	}
	curfdt = curthread->fdt;
	struct file_des *file_d;
	file_d = array_get(curfdt->fds,fd);
	if ((file_d == NULL) || (file_d->flag == 0)){
		return 30;
		// DEBUG mode is not opened or is read only
	}
	else {
	// kprintf("In Write\n");
		struct iovec iov;
		struct uio u;
		int result;

		iov.iov_ubase = (void*)buf;
		iov.iov_len = nbytes;

		u.uio_iov = &iov;
		u.uio_iovcnt = 1;
		u.uio_offset = file_d->offset;
		u.uio_resid = nbytes;
		u.uio_segflg = UIO_USERSPACE;
		u.uio_rw = UIO_WRITE;
		u.uio_space = curproc_getas();

		result = VOP_WRITE(file_d->vnode, &u);

		if (result){
			return result;
		}

		file_d->offset = u.uio_offset;
		if (u.uio_resid == 0){
			*return_val = nbytes;
		}
		else {
			*return_val = nbytes-u.uio_resid;
		}
	}
	return 0;
}

// close
int
sys_close(int fd){
	// kprintf("In close\n");
	if (fd == DEADBEEF){
		return 30;		
	}
	int result;
	curfdt = curthread->fdt;
	if (fd > fd_table_fd_nums(curfdt)){
		return 30;
		// Fd number exceed maximum file nums
	}
	result = fd_table_rm_fd(curfdt,fd);
	if (result){
		return result;
	}
	return 0;
}

// https://github.com/rbui/projectJailBait/blob/master/os161-1.11/kern/syscall/syscall_mine.c
void sys__exit(int exitcode){
	thread_exit();
	return;
	(void)exitcode;
}	
