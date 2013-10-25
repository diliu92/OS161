#include <string>
#include <unistd.h>
#include <uio.h>
#include <vfs.h>
#include <syscall.h>
#include <kern/errno.h>
#include <array.h>
#include <kern/iovec.h>
#include <file_des.h>


// open
int open(const char *filename, int flags){
	if (filename == NULL){

	}

	struct vnode *v;
	int result;

	/* Open the file. */
	char *console = NULL;
	console = kstrdup("con:");
	result = vfs_open(filename, flags, &v);
	kfree(console);

	// if (strcmp(flags,O_RDONLY)){

	// }
	// else if (strcmp(flags,O_WRONLY)){

	// }
	// else if (strcmp(flags,O_RDWR)){
		
	// }

	if (result) {
		return result;
	}

}
int open(const char *filename, int flags, int mode){
	open(*filename, flags);
}

// read

int
read(int fd, void *buf, size_t buflen){
	struct vnode *v;
	int result;

	/* Open the file. */
	char *console = NULL;
	console = kstrdup("con:");
	result = vfs_open(filename, flags, &v);
	kfree(console);	
}

// write
int
write(int fd, const void *buf, size_t nbytes>){
	struct vnode *v;
	int result;

	/* Open the file. */
	char *console = NULL;
	console = kstrdup("con:");
	result = vfs_open(filename, flags, &v);
	kfree(console);
}

// close
int
close(int fd){
	struct vnode *v;
	int result;

	/* Open the file. */
	char *console = NULL;
	console = kstrdup("con:");
	result = vfs_open(filename, flags, &v);
	kfree(console);
}