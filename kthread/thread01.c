#include<linux/kthread.h>

struct task_struct *kthread_create(int (*function)(void *data),
                                   void *data,
                                   const char name[],
                                   ...)

static struct task_struct *thread1;

int thread_init(void){
    char our thread[8]="thread";
    printk(KERN_INFO "in init");
    thread1 = kthread_create(thread_fn,NULL,our_thread);
    if((thread1))
        {
        printk(KERN_INFO "in if");
        wake_up_process(thread1);
        }
    return 0;
}
