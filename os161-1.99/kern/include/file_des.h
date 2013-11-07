#ifndef FILE_DES_H
#define FILE_DES_H

#include "opt-A2.h"
#include <types.h>
#include <vnode.h>
#include <array.h>
#include <lib.h>
#include <kern/fcntl.h>

// File descriptor
struct file_des
{
	struct vnode *vnode;
	int flag;
	off_t offset;
	// int opencount;
};

struct file_des *fd_create(struct vnode *v, int flg, off_t os);
void fd_destroy(struct file_des *fd);

#endif
