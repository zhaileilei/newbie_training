/*
Filename:
	hellowork.c
Copyright (C) 2014 Wistron
All rights reserved.
Description:
	This file is a simple kernel module,make it,and insert/remove from system.
Author/Created Date:
	Myth Zhai,Sep15'14
Modification History:



Note:

 */

#include<linux/init.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
	printk(KERN_ALERT "Hello,world\n");
	return 0;	
}
static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye,cruel world\n");
}
module_init(hello_init);
module_exit(hello_exit);

