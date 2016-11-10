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

int thread_fn(){
    unsigned long j0, j1;
    int delay = 60*HZ;
    j0 = jiffies;
    j1 = j0 + delay;

    printk(KERN_INFO "In thread");

    while (time_before(jiffies, j1))
        schedule();

    return 0; 
}

void thread_cleanup(void) {
    int ret;
    ret = kthread_stop(thread1);
    if(!ret)
    printk(KERN_INFO "Thread stopped");
}
