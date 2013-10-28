#include "opt-A2.h"
#include <file_des.h>
// File descriptor

struct file_des *fd_create(struct vnode *v, int flg, off_t os){
	struct file_des *fd;
	fd = kmalloc(sizeof(struct file_des));
	if (fd == NULL){
		return NULL;
	}
    else {
        fd->vnode = v; 
        fd->flag = flg;
        fd->offset = os;
        return fd;
    }
}

void fd_destroy(struct file_des *fd){
    KASSERT(fd->vnode == NULL);
    kfree(fd->vnode);
    kfree(fd);
}
