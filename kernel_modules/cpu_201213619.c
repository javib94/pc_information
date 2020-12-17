#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/sysinfo.h>
#include <linux/sys.h>
#include <linux/mm.h>
#include <linux/cpufreq.h>

#define BUFSIZE 100

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Javier Barreda");

static struct proc_dir_entry *ent;
const long minute = 60;
const long hour = 3600;
const long day = 86400;
const double megabyte = 1048576;
    
// static int irq=20;
// module_param(irq,int,0660);

// static int mode=1;
// module_param(mode,int,0660);

static ssize_t mywrite(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
    printk(KERN_DEBUG "write handler\n");
    return -1;
}

static ssize_t myread(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
    struct sysinfo si;
    char buf[BUFSIZE];
    int len = 0;
    unsigned long uc_temp, tc_temp, um_temp, tm_temp;

    printk(KERN_DEBUG "read handler\n");
    if (*ppos > 0 || count < BUFSIZE)
        return 0;
    //codigo de escribir
   
    /* Obtain system statistics. */
    si_meminfo(&si); //gets memory info
    um_temp = si.totalram - si.freeram; //used memory
    tm_temp = si.totalram; //total memory
    len += sprintf(buf, "{\n\"totalram\": \"%lu\",\n\"usedram\": \"%lu\",\n\"freeram\": \"%lu\",\n}\n ", tm_temp, um_temp, si.freeram);

    /*
    sysinfo(&si);
     Summarize interesting values. 
    len += sprintf(buf, "system uptime : %ld days, %ld:%02ld:%02ld\n",
                   si.uptime / day, (si.uptime % day) / hour,
                   (si.uptime % hour) / minute, si.uptime % minute);
    len += sprintf(buf, "total RAM   : %5.1f MB\n", si.totalram / megabyte);
    len += sprintf(buf, "free RAM   : %5.1f MB\n", si.freeram / megabyte);
    len += sprintf(buf, "process count : %d\n", si.procs);
    len += sprintf(buf, "irq HOla mundo \n");
    len += sprintf(buf + len, "mode dd\n");
    */
    //fin del codigo de escribir
    if (copy_to_user(ubuf, buf, len))
        return -EFAULT;
    *ppos = len;
    return len;
}

static struct file_operations myops =
    {
        .owner = THIS_MODULE,
        .read = myread,
        .write = mywrite,
};

static int simple_init(void)
{

    printk(KERN_DEBUG "Javier Barreda\n");
    ent = proc_create("mysysinfo", 0660, NULL, &myops);
    return 0;
}

static void simple_cleanup(void)
{
    printk(KERN_DEBUG "Sistemas Operativos 1 2020\n");
    proc_remove(ent);
}

module_init(simple_init);
module_exit(simple_cleanup);