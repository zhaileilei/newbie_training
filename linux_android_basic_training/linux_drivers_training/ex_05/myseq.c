/*============================================
 *	Filename:
 *      myseq.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will Create/Delete the device number and node equipment.
 *		
 *	Author/Create Date:
 *		Myth Zhai,Sep30'14
 *
 *  Modification History:
 *
 *
 *  Note:
 *
 *============================================
 */

/* Include Files */
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<asm/io.h>
#include<linux/errno.h>
#include<linux/mm.h>
#include<asm/uaccess.h>
#include<linux/slab.h>
#include<linux/sched.h>
#include<linux/device.h>
#include<linux/semaphore.h>
#include<linux/delay.h>
/* MACROS */
#define CHAR_SIZE 0x1000
#define CHAR_CLEAR 0x1
#define CHAR_MAJOR 254

static int char_major;
static struct class *cls;
struct  char_dev
{
	struct cdev cdev;
	unsigned  char mem[CHAR_SIZE];
	struct semaphore sem;
};

struct char_dev *char_devp;
int char_open(struct inode *inode,struct file *filp)
{
	filp->private_data = char_devp;

	//if(down_interruptible(&dev->sem)){
		//return -ERESTARTSYS;
	//}
	printk("open ok!\n");
	return 0;
}
int char_release(struct inode *inode, struct file *filp)
{   
	//up(&dev->sem);
	return 0;
}
static long char_ioctl(/* struct inode *inodep,*/ struct file*filp,unsigned 
						int cmd,unsigned long arg)
{
	struct char_dev *dev = filp->private_data;
	switch(cmd){
		case CHAR_CLEAR:
			if (down_interruptible(&dev->sem))
				return -ERESTARTSYS;
			memset(dev->mem,0,CHAR_SIZE);
			up(&dev->sem);
			printk(KERN_INFO "char is set to zero\n");
			break;
		default:
			return - EINVAL;
	}
	return 0;
}

static ssize_t char_read(struct file *filp,char __user *buf,
							size_t size,loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int  count = size;
	int ret =0;
	struct char_dev *dev= filp->private_data;
	if(p > CHAR_SIZE){
		return count ? -ENXIO: 0;
	}
	if(count >  CHAR_SIZE - p)
		count = CHAR_SIZE - p;
	if(down_interruptible(&char_devp->sem))
		return -ERESTARTSYS;
	if(copy_to_user(buf,(void*)(dev->mem + p),count)){
		ret = -EFAULT;
	}
	else{
		*ppos += count;
		 ret=count;
		 printk(KERN_INFO "read %d bytes(s) from % ld\n",count,p);
	}
	up(&char_devp->sem);
	return ret;
}

static ssize_t char_write(struct file *filp,const char __user *buf,
							size_t size,loff_t *ppos)
{
	unsigned long p =*ppos;
	unsigned int count = size;
	int ret=0;
	struct char_dev *dev = filp->private_data;
	if(p > CHAR_SIZE)
		return count ? -ENXIO: 0;
	if(count > CHAR_SIZE - p)
		count =	CHAR_SIZE - p;
	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;
	if(copy_from_user(dev->mem + p,buf,count))
		ret= - EFAULT;
	else{
		*ppos += count;
		ret = count;

		 printk(KERN_INFO "writen %d bytes(s) from %lu\n",count,p);
	}
	mdelay(2000);
	up(&char_devp->sem);
	return ret;
}

static struct file_operations char_fops = {
	.owner = THIS_MODULE,
	.read  = char_read,
	.write = char_write,
	.open  = char_open,
	.release = char_release,
	.unlocked_ioctl = char_ioctl,
};

static void char_setup_cdev(struct char_dev *dev, int index)
{
	int err,devno = MKDEV(char_major,index);

	cdev_init(&dev->cdev,&char_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops   = &char_fops;
	err = cdev_add(&dev->cdev,devno,1);
	if (err)
		printk(KERN_NOTICE "Error %d adding LED%d",err,index);
}
/* IMPLEMENTATION */
static int  char_init(void)
{
	int result;
	dev_t devno = MKDEV(char_major,0);
	if(char_major)
		result = register_chrdev_region(devno,1,"myseq");
	else
	{
		result = alloc_chrdev_region(&devno,0,1,"myseq");
		char_major = MAJOR(devno);
	}
	if(result < 0)
		return result;
	char_devp = kmalloc(sizeof(struct char_dev),GFP_KERNEL);
	if(!char_devp)
	{
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(char_devp,0, sizeof(struct char_dev));
	char_setup_cdev(char_devp,0);
	cls = class_create(THIS_MODULE,"cseq");
	device_create(cls,NULL,devno,NULL,"cseq");
	//MUTEX(&char_devp->sem);
	sema_init(&char_devp->sem,1);
	return 0;
fail_malloc: unregister_chrdev_region(devno,1);
	return result;
}
/* IMPLEMENTATION */
static void  char_exit(void)
{	dev_t devno=MKDEV(char_major,0);
	device_destroy(cls,devno);
	class_destroy(cls);
	cdev_del(&char_devp->cdev);
	kfree(char_devp);
	unregister_chrdev_region(MKDEV(char_major,0),1);
}
module_param(char_major,int,S_IRUGO);
module_init(char_init);
module_exit(char_exit);
MODULE_LICENSE("GPL"); 
