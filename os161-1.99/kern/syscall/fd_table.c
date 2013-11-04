#include "opt-A2.h"
#include <fd_table.h>	
#include <limits.h>
#include <current.h>
#include <vfs.h>
#include <array.h>

struct fd_table *fd_table_create(void){
	
	struct fd_table *fdt;
	
	fdt = kmalloc(sizeof(struct fd_table));

	if (fdt == NULL) {
		return NULL;
	}

	fdt->fds = array_create();
	return fdt;
}

struct fd_table *fd_table_init(struct fd_table *fdt) {
	int result;
	unsigned int index;
	// struct fd_table *fdt = curthread->fdt;

	char *console1 = NULL;
	console1 = kstrdup("con:");
	struct vnode *v1;
	result = vfs_open((char*)console1, O_RDONLY, 0, &v1);
	struct file_des *fd1 = fd_create(v1,O_RDONLY,0);
	
	kfree(console1);
	array_add(fdt->fds, fd1, &index);

	char *console2 = NULL;
	console2 = kstrdup("con:");
	struct vnode *v2;
	result = vfs_open((char*)console2, O_WRONLY, 0, &v2);
	struct file_des *fd2 = fd_create(v2,O_WRONLY,0);
	
	kfree(console2);
	array_add(fdt->fds, fd2, &index);

	char *console3= NULL;
	console3 = kstrdup("con:");
	struct vnode *v3;
	result = vfs_open((char*)console3, O_WRONLY, 0, &v3);
	struct file_des *fd3 = fd_create(v3,O_WRONLY,0);
	
	kfree(console3);
	array_add(fdt->fds, fd3, &index);

	return fdt;
}

void fd_table_destroy(struct fd_table *fdt){
	KASSERT(array_num(fdt->fds) == 0);
	array_destroy(fdt->fds);
	kfree(fdt);
}

struct fd_table *fd_table_dup(struct fd_table *fdt){
	struct fd_table *dup_fdt;
	dup_fdt = kmalloc(sizeof(struct fd_table));
	dup_fdt->fds = fdt->fds;
	return dup_fdt;
}

int fd_table_add_fd(struct fd_table *fdt, struct file_des *fd){
	unsigned *index_ret = NULL;
	unsigned int fd_index;
	fd_index = array_num(fdt->fds);
	if (fd_index == OPEN_MAX-1){
		return -1;
	}
	array_add(fdt->fds, fd, index_ret);
	return (int)fd_index;
}

struct file_des *fd_table_get_fd(struct fd_table *fdt, int fd){
	return array_get(fdt->fds, fd);
}

int fd_table_rm_fd(struct fd_table *fdt, int fd){
	if ((array_num(fdt->fds)!=0) && (array_get(fdt->fds,fd)!=NULL)){
		struct vnode *close_v = (fd_table_get_fd(fdt,fd))->vnode;
		vfs_close(close_v);
		array_set(fdt->fds, fd, NULL);
		return 0;
	}
	return 1;
}

int fd_table_fd_nums(struct fd_table *fdt){
	return fdt->fds->num;
}
