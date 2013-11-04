#ifndef _FILE_SYSCALLS_H_
#define _FILE_SYSCALLS_H_
#include "opt-A2.h"
#include <fd_table.h>
#include <uio.h>
#include <current.h>
#include <kern/errno.h>

int sys_open(const char *filename, int flags, int mode, int *return_val);
int sys_read(int fd, void *buf, size_t buflen, int *return_val);
int sys_write(int fd, const void *buf, size_t nbytes, int *return_val);
int sys_close(int fd);
void sys__exit(int exitcode);	

#endif
