#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#define BUFSIZE  100
 
 
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Liran B.H");
 
 
static struct proc_dir_entry *ent;

// static int irq=20;
// module_param(irq,int,0660);
 
// static int mode=1;
// module_param(mode,int,0660);
  
static ssize_t mywrite(struct file *file, const char __user *ubuf,size_t count, loff_t *ppos) 
{
	printk( KERN_DEBUG "write handler\n");
	return -1;
}
 

static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	char buf[BUFSIZE];
	int len=0;
	printk( KERN_DEBUG "read handler\n");
	if(*ppos > 0 || count < BUFSIZE)
		return 0;
	//codigo de escribir 	
	len += sprintf(buf,"irq HOla mundo \n");
	len += sprintf(buf + len,"mode dd\n");
	
	//fin del codigo de escribir 
	if(copy_to_user(ubuf,buf,len))
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

	printk( KERN_DEBUG "\n");
	ent=proc_create("mydev",0660,NULL,&myops);
	return 0;
}
 
static void simple_cleanup(void)
{
	proc_remove(ent);
}
 
module_init(simple_init);
module_exit(simple_cleanup);