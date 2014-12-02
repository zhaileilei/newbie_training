/*============================================
 *	Filename:
 *       proc.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will Create and delete device node 
 *		
 *	Author/Create Date:
 *		Myth Zhai,Nov25'14
 *
 *  Modification History:
 *
 *
 *  Note:
 *
 *============================================
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#define MAX_UL_LEN 8
static struct proc_dir_entry *proc_entry;

static unsigned long  val = 121;

static int proc_file_read(char *page,char **start,off_t off,int count,
								int* eof, void* data){
	int len;
	if (off > 0) {
		*eof = 1;
		return 0;
	}
	len = sprintf(page, "%lu\n",val);
		return len;
}
static int  proc_file_write(struct file* filp,const char __user *buff,
						unsigned long len, void *data)
{
	char k_buf[MAX_UL_LEN];
	char *endp;
	int count;
	int ret;
	unsigned long new;
	if (MAX_UL_LEN > len)
		 count = len;
	else 
		 count = MAX_UL_LEN;
	if (copy_from_user(k_buf,buff,count)){
		ret = -EFAULT;
		goto err;
	}
	else{
		new = simple_strtoul(k_buf,&endp,10);
		if(endp == k_buf) {
			ret = - EINVAL;
			goto err;
		}
		val = new;
		return count;
	}
	err:
	return ret;
}
int __init proc_init(void)
{
	proc_entry =create_proc_entry ("hello",0666,NULL);
	if (proc_entry == NULL) {
		printk(KERN_INFO "couldn't create proc entry\n");
		goto err;
	}
	else {
		proc_entry->read_proc = proc_file_read;
		proc_entry->write_proc = proc_file_write;
	//	proc_entry->owner = THIS_MODULE;
	}
	return 0;
	err:
	return -ENOMEM;
}
void __exit proc_exit(void)
{
	remove_proc_entry("hello",NULL);
}
module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0");
