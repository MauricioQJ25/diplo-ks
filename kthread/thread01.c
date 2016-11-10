#include<linux/kthread.h>

struct task_struct *kthread_create(int (*function)(void *data),
                                   void *data,
                                   const char name[],
                                   ...)
