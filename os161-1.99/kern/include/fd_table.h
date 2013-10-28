#ifndef FD_TABLE_H
#define FD_TABLE_H

#include "opt-A2.h"
#include <file_des.h>

struct fd_table{
	struct array *fds;
};
 
struct fd_table *fd_table_create(void);
void fd_table_init(void);
void fd_table_destroy(struct fd_table *fdt);
struct fd_table *fd_table_dup(struct fd_table *fdt);

int fd_table_add_fd(struct fd_table *fdt, struct file_des *fd);
struct file_des *fd_table_get_fd(struct fd_table *fdt, int fd);
int fd_table_rm_fd(struct fd_table *fdt, int fd);

#endif
