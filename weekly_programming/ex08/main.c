/*============================================
 *	Filename:
 *       main.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will achieve that test about list.
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


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Intset.h"
int randInt(lower, upper)
{
	assert( lower < upper);
	return rand()%(upper - lower + 1) + lower;
}

void print(int arry[], int length)
{
	int i;
	printf("the set is \n");
	for(i = 0; i < length; i ++)
		printf("%d  ", arry[i]);
	printf("\n");
}
int main()
{

	int count , i, lower, upper, *v;
	srand (time (NULL));
	count = rand()%20;
	lower =rand()%3 +1;
	upper = rand ()% 30;
	
	printf("lower=%d upper=%d count=%d\n", lower, upper, count);
	v = (int *)malloc(count * sizeof(int));
	intset_init(count , upper + 1);
	i = count;
	while(i > 0)
	{
		int t = randInt(lower, upper);
		printf("rand=%d\n", t);
		if( isinset(t) == false)
		{
				insert_norec(t);
				i --;
		}

	}
	report(v);
	destory_set();
	print(v, count);
	return 0;
}
