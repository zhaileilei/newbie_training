/*============================================
 *	Filename:
 *       driver.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will Create/Delete the device number and node equipment.
 *		
 *	Author/Create Date:
 *		Myth Zhai,Sep25'14
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
#include<linux/io.h>
#include<linux/errno.h>
#include<linux/mm.h>
#include<asm/uaccess.h>
#include<linux/slab.h>
#include<linux/sched.h>
#include<linux/device.h>
#include<linux/capability.h>
#include"driver.h"

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
};

struct char_dev *char_devp;

static int char_open(struct inode *inode,struct file *filp)
{
	filp->private_data = char_devp;
	printk("open ok!\n");
	return 0;
}
static int char_release(struct inode *inode, struct file *filp)
{	
	printk("release ok!\n");
	return 0;
}
static long char_ioctl(/* struct inode *inodep,*/ struct file *filp,
			unsigned int cmd,unsigned long arg)
{
	struct char_dev *dev = filp->private_data;
	int err = 0, tmp;
	int retval = 0;
	if(_IOC_TYPE(cmd) !=SCULL_IOC_MAGIC)
		return -ENOTTY;
	if(_IOC_NR(cmd) > SCULL_IOC_MAXNR)
		return -ENOTTY;
	if(_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if(_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err) 
		return -EFAULT;
	switch(cmd){
		case CHAR_CLEAR:
			memset(dev->mem,0,CHAR_SIZE);
			printk(KERN_INFO "char is set to zero\n");
			break;


		case SCULL_IOCRESET:
			scull_quantum = SCULL_QUANTUM;
			scull_qset = SCULL_QSET;
			break;

		case SCULL_IOCSQUANTUM:
			printk("hello\n");
			//if(! capable (CAP_SYS_ADMIN))
				//return -EPERM;
			retval = __get_user(scull_quantum, (int __user *) arg);
			break;
		case SCULL_IOCTQUANTUM:
			if(! capable (CAP_SYS_ADMIN))
				return -EPERM;
			scull_quantum = arg;
			break;
		case SCULL_IOCGQUANTUM:
			retval = __put_user(scull_quantum, (int __user *) arg);
			break;
		case SCULL_IOCQQUANTUM:
			return scull_quantum;
		case SCULL_IOCXQUANTUM:
			if(! capable (CAP_SYS_ADMIN))
				return -EPERM;
			tmp = scull_quantum;
			retval = __get_user(scull_quantum,(int __user *)arg);
			if(retval == 0)
				retval = __put_user(tmp, (int __user *) arg);
			break;
		case SCULL_IOCHQUANTUM:
			if(! capable (CAP_SYS_ADMIN))
				return -EPERM;
			tmp = scull_quantum;
			scull_quantum = arg;
			return tmp;
		case SCULL_IOCSQSET:
			if (! capable (CAP_SYS_ADMIN))
				return -EPERM;
			retval = __get_user(scull_qset, (int __user *)arg);
			break;

		case SCULL_IOCTQSET:
			if (! capable (CAP_SYS_ADMIN))
				return -EPERM;
			scull_qset = arg;
			break;

		case SCULL_IOCGQSET:
			retval = __put_user(scull_qset, (int __user *)arg);
			break;

		case SCULL_IOCQQSET:
			return scull_qset;

		case SCULL_IOCXQSET:
			if (! capable (CAP_SYS_ADMIN))
				return -EPERM;
			tmp = scull_qset;
			retval = __get_user(scull_qset, (int __user *)arg);
			if (retval == 0)
				retval = put_user(tmp, (int __user *)arg);
			break;

		case SCULL_IOCHQSET:
			if (! capable (CAP_SYS_ADMIN))
				return -EPERM;
			tmp = scull_qset;
			scull_qset = arg;
			return tmp;
		default:
			return - ENOTTY;
	}
	return retval;
}
static ssize_t char_read(struct file *filp,char __user *buf,
		size_t size,loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int  count = size;
	int ret =0;
	struct char_dev *dev= filp->private_data;
	if(p > CHAR_SIZE)
		return count ? -ENXIO: 0;
	if(count >  CHAR_SIZE - p)
		count = CHAR_SIZE - p;
	if(copy_to_user(buf,(void*)(dev->mem + p),count)){
		ret = -EFAULT;
	}
	else{
		*ppos += count;
		ret=count;
		printk(KERN_INFO "read %d bytes(s) from % ld\n",count,p);
	}
	return ret;
}

static ssize_t char_write(struct file *filp,const char __user *buf,
		size_t size,loff_t *ppos)
{
	unsigned long p =*ppos;
	unsigned int count = size;
	int ret=0;
	struct char_dev *dev = filp->private_data;
	if(p >= CHAR_SIZE)
		return count ? -ENXIO: 0;
	if(count >CHAR_SIZE - p)
		count =	CHAR_SIZE - p;
	if(copy_from_user(dev->mem + p,buf,count))
		ret= - EFAULT;
	else{
		*ppos += count;
		ret = count;

		printk(KERN_INFO "writen %d bytes(s) from %lu\n",count,p);
	}
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
		result = register_chrdev_region(devno,1,"mychar");
	else
	{
		result = alloc_chrdev_region(&devno,0,1,"mychar");
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
	cls = class_create(THIS_MODULE,"mydevice");
	device_create(cls,NULL,devno,NULL,"mydevice");
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
module_param(scull_quantum, int, S_IRUGO);
module_param(scull_qset, int, S_IRUGO);
module_init(char_init);
module_exit(char_exit);
MODULE_LICENSE("GPL"); 
