#include "opt-A2.h"
#include <file_des.h>
// File descriptor

struct file_des *fd_create(struct vnode *v, int flg, off_t os){
	struct file_des *fd;
	fd = kmalloc(sizeof(struct file_des));

	if (fd == NULL){
        kfree(fd);
		return NULL;
	}
    else {
        fd->vnode = v; 
        fd->flag = flg;
        fd->offset = os;
        // fd->opencount = 1;
        return fd;
    }
}

void fd_destroy(struct file_des *fd){
    if (fd != NULL){
        kfree(fd->vnode);
    }    
    kfree(fd);
}
