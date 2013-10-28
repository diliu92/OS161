#include "opt-A2.h"
#include <file_syscalls.h>
#include <vfs.h>
#include <proc.h>

struct fd_table *curfdt;

// open
int sys_open(const char *filename, int flags, int mode, int * return_val){
	if (filename == NULL){
	}
	struct vnode *v;
	int result;
	struct file_des *fd;

	/* Open the file. */
	char *console = NULL;
	curfdt = curthread->fdt;
	console = kstrdup("con:");
	result = vfs_open((char*)filename, flags, mode, &v);
	kfree(console);

	curfdt->fds->v[0]=fd_create(v,O_RDONLY,0);
	curfdt->fds->v[1]=fd_create(v,O_WRONLY,0);
	curfdt->fds->v[2]=fd_create(v,O_WRONLY,0);

	if (result) {
		vfs_close(v);
		return result;
	}

	fd = fd_create(v, flags, 0);
	*return_val = fd_table_add_fd(curfdt, fd);

	return 0;
}

// read
int
sys_read(int fd, void *buf, size_t buflen, int * return_val){
	curfdt = curthread->fdt;
	struct file_des *file_d;
	file_d = array_get(curfdt->fds, fd);
	// file_d = curfdt->fds->v[fd];
	if (file_d == NULL){
		// DEBUG file not opened
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
		u.uio_space = curproc->p_addrspace;

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
sys_write(int fd, const void *buf, size_t nbytes, int * return_val){
	curfdt = curthread->fdt;
	struct file_des *file_d = curfdt->fds->v[fd];
	if (file_d == NULL){
		// DEBUG file not opened
	}
	else {

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
		u.uio_space = curproc->p_addrspace;

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
	int result;
	curfdt = curthread->fdt;
	result = fd_table_rm_fd(curfdt,fd);
	return result;
}
