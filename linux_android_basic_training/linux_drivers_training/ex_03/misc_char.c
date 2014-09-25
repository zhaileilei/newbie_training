/*=================================
 *	Filename:
 *		misc_char.c
 *
 *	Copright (C) 2014 Wistron
 *  All rights reserved
 *
 *	Description:
 *	This file will Create/Delete the device number and node quipment.
 *
 *	Author/Create Date:
 *				Myth Zhai,Sep23'14
 *
 *	Modification History:
 *
 *
 *
 *	Note:
 * =================================
 */

/* Include Files */
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/mm.h>
#include<linux/miscdevice.h>
#include<asm/io.h>
#include<linux/errno.h>
#include<linux/slab.h>
#include<linux/sched.h>

/* MACROS */
#define CHAR_SIZE 0x1000
#define CHAR_CLEAR 0x1

struct char_dev
{
	unsigned char mem[CHAR_SIZE];
};
struct char_dev *char_devp;

int char_open(struct inode *inode,struct file *filp)
{
	filp->private_data = char_devp;
	printk("open sucess!\n");
	return 0;
}

int char_release(struct inode *inode,struct file *filp)
{
	return 0;
}

static long char_ioctl( struct file *filp,unsigned
						int cmd,unsigned long arg)
{
	struct char_dev *dev = filp->private_data;
	switch(cmd){
			case CHAR_CLEAR:
				  memset(dev->mem,0,CHAR_SIZE);
				  printk(KERN_INFO "char is set to zero\n");
				  break;
			default:
				  return -EINVAL;
	}
		return 0;
}

static ssize_t char_read(struct file *filp,char __user *buf,
							size_t size,loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int  count = size;
	int ret = 0;
	struct char_dev *dev = filp->private_data;
	if(p > CHAR_SIZE)
		return count ? -ENXIO: 0;
	if(count > CHAR_SIZE - p)
		count = CHAR_SIZE - p;
	if(copy_to_user(buf,(void*)dev->mem + p, count)){
		ret = -EFAULT;
	}
	else {
		*ppos += count;
		ret = count;
		printk(KERN_INFO "read %d bytes(s) from %ld\n",count,p);
	}
	return ret;
}

static ssize_t char_write(struct file *filp,const char __user *buf,
							size_t size, loff_t *ppos)
{
	unsigned long p =*ppos;
	unsigned int count = size;
	int ret = 0;
	struct char_dev *dev =filp->private_data;
	if(p >= CHAR_SIZE)
		return count ? -ENXIO : 0;
	if(count > CHAR_SIZE - p)
		count = CHAR_SIZE - p;
	if(copy_from_user(dev->mem + p,buf,count))
		ret = -EFAULT;
	else {
		*ppos += count;
		ret = count;
		printk(KERN_INFO "writen %d bytes(s) from %lu\n",
										count,p);
	}
	return ret;
}

static struct file_operations char_fops = {
	.owner = THIS_MODULE,
	.read = char_read,
	.write = char_write,
	.open = char_open,
	.release = char_release,
	.unlocked_ioctl = char_ioctl,
};
static struct miscdevice char_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "mymisc_char",
	.fops  = &char_fops,
};

/* IMPLEMENTATION */
static int char_init(void)
{
	misc_register(&char_misc);
	char_devp = kmalloc(sizeof(struct char_dev),GFP_KERNEL);
	memset(char_devp,0,sizeof(struct char_dev));
	return 0;
}

/* IMPLEMENTATION */
static void char_exit(void)
{
	kfree(char_devp);
	misc_deregister(&char_misc);
}

module_init(char_init);
module_exit(char_exit);
MODULE_LICENSE("GPL");
