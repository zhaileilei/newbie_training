/*============================================
 *	Filename:
 *       Intest.h
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will achieve that the definition of functions 
 *		and variables.
 *		
 *	Author/Create Date:
 *		Myth Zhai,Nov21'14
 *
 *  Modification History:
 *
 *
 *  Note:
 *
 *============================================
 */
typedef int bool;
#define true 0
#define false 1
void intset_init(int maxelements, int maxval);
bool isinset(int t);
int getsize();
void report(int *v);
void destory_set();
