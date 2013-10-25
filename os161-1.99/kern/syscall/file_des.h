#include <vnode.h>

struct file_des
{
	struct *vnode vnode;
	int flag;
	off_t offset;
};

file_des * fd_create(*vnode v, int flag, off_t offset){
	struct file_des *fd;
	fd = kmalloc(sizeof(struct file_des));
	if (fd == NULL){
		return NULL;
	}

	fd->vnode = v;
	if ()
}

        sem->sem_name = kstrdup(name);
        if (sem->sem_name == NULL) {
                kfree(sem);
                return NULL;
        }

    sem->sem_wchan = wchan_create(sem->sem_name);
    if (sem->sem_wchan == NULL) {
        kfree(sem->sem_name);
        kfree(sem);
        return NULL;
    }

    spinlock_init(&sem->sem_lock);
        sem->sem_count = initial_count;

        return sem;