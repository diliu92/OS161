#include "opt-A2.h"
#include <fd_table.h>	
#include <limits.h>

struct fd_table *fd_table_create(void){
	
	struct fd_table *fdt;
	fdt = kmalloc(sizeof(struct fd_table));

	if (fdt != NULL) {
		fdt->fds = array_create();
		for (int i=0; i<__OPEN_MAX; i++){
			array_set(fdt->fds, i, NULL);
		}
	}
	else {
		return NULL;
	}
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
	int fd_index = 3;
	for (int i=3; array_get(fdt->fds,i)!=NULL; i++){
		fd_index ++;
	}
	array_set(fdt->fds, fd_index, fd);
	return fd_index;
}

struct file_des *fd_table_get_fd(struct fd_table *fdt, int fd){
	return array_get(fdt->fds, fd);
}

int fd_table_rm_fd(struct fd_table *fdt, int fd){
	if ((array_num(fdt->fds)!=0) && (array_get(fdt->fds,fd)!=NULL)){
		array_remove(fdt->fds,fd);
		return 1;
	}
	return 0;
}
