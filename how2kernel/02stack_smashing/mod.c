#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

int bug2_write(struct file *file, const char *buf, unsigned long len)
{
    char localbuf[8];
    memcpy(localbuf, buf, len);
    return len;
}

static int __init stack_smashing_init(void)
{
    printk(KERN_ALERT "stack_smashing driver init!\n");
    create_proc_entry("bug2", 0666, 0)->write_proc = bug2_write;
    return 0;
}

static void __exit stack_smashing_exit(void)
{
    printk(KERN_ALERT "stack_smashing driver exit!\n");
}

module_init(stack_smashing_init);
module_exit(stack_smashing_exit);
