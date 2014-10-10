/*============================================
 
 *	Filename:
 *       time.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will Create/Delete the device number and node equipment.
 *		
 *	Author/Create Date:
 *		Myth Zhai,Oct10'14
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
#include<linux/timer.h>
#include<linux/jiffies.h>
#include<linux/param.h>
#include<linux/delay.h>
#include<linux/sched.h>
#include<linux/slab.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kfifo.h>
#include<linux/time.h>

/* DEFINES */
static void print_current_time(int);
static void test_short_delay(void);
static void test_delay(void);
static void test_schedule_timeout(void);
static void my_delay_function(unsigned long);
 
static void print_current_time(int is_new_line)
{
	struct timeval *tv;
	struct tm *t;
	tv = kmalloc(sizeof(struct timeval), GFP_KERNEL);
	t  = kmalloc(sizeof(struct tm),GFP_KERNEL) ;
	do_gettimeofday(tv);
	time_to_tm(tv->tv_sec, 0, t);

	printk(KERN_ALERT "%ld-%d-%d %d:%d:%d",t->tm_year + 1900,
			t->tm_mon + 1, t->tm_mday,(t->tm_hour + 8),
			t->tm_min,t->tm_sec);
	if (is_new_line == 1)
		printk(KERN_ALERT "\n");
	kfree(tv);
	kfree(t);
}
/* IMPLEMENTATION */
static int testdelay_init(void)
{
	printk(KERN_ALERT "HZ in current system: %dHZ\n",HZ);
	test_short_delay();
	test_delay();
	test_schedule_timeout();
	return 0;
}

static void testdelay_exit(void)
{
	printk(KERN_ALERT ".................\n");
	print_current_time(0);
	printk(KERN_ALERT "testdelay is exited!\n");
	printk(KERN_ALERT "..................\n");
}

static void test_short_delay()
{
	//ndelay(5);
	//unsigned long delay = jiffies + 100;
	printk(KERN_ALERT "jiffies [before] short delay:%lu\n",jiffies);
	//printk(KERN_ALERT"delay=%lu\n",delay);
	//while(time_before(jiffies,delay));
	msleep(2000);
	printk(KERN_ALERT "jiffies  [after] short delay: %lu\n",jiffies);

}

static void test_delay()
{
	struct timer_list my_timer;
	init_timer(&my_timer);
	my_timer.expires = jiffies + HZ;
	my_timer.data = jiffies;
	my_timer.function = my_delay_function;
	add_timer(&my_timer);
}

static void my_delay_function(unsigned long data)
{
	printk(KERN_ALERT "This is my delay function start....\n");
	printk(KERN_ALERT "The jiffies when init timer: %lu\n",data);
	printk(KERN_ALERT "The jiffies when timer is running: %lu\n",jiffies);
	printk(KERN_ALERT "This  is my delay function end ......\n");
}

static void test_schedule_timeout()
{
	printk(KERN_ALERT "This sample start at : %lu\n",jiffies);
	set_current_state(TASK_INTERRUPTIBLE);
	printk(KERN_ALERT "sleep 2s....\n");
	schedule_timeout(2*HZ);
	printk(KERN_ALERT "This sample end at :%lu\n",jiffies);
}

module_init(testdelay_init);
module_exit(testdelay_exit);
MODULE_LICENSE("GPL");
