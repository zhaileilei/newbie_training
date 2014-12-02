/*============================================
 *	Filename:
 *       qsort.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will achieve that use list to sort.
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include "Intset.h"


static int *set = NULL;
static int size;
typedef struct node *pnode; 
typedef struct node{
	int val;
	pnode next;

}node; 

static pnode head = NULL;
static pnode sentinel = NULL;
void intset_init(int maxelements, int maxval)
{

	if((head = sentinel = (pnode)malloc(sizeof(node))) != NULL)
	{
		sentinel->val = maxval;
		sentinel->next = NULL;
		size = 0;
	}
	else 
	{
		printf("intset_init failed to malloc\n");
		exit(1);
	}
}


bool isinset(int t)
{
	pnode p = head;
	while(p != sentinel)
	{
		if(p->val == t)
			return true;
		else
			p = p->next;
	}
	return false;
}

void insert_norec(int t)
{
	pnode p = head, q = NULL, new;

	while(p->val < t)
	{
		q = p;
		p = q->next;
	}

	new = (pnode)malloc(sizeof(node));
	new->val = t;
	new->next = p;

	if(q == NULL)
	{
		head = new;
	}
	else
	{
		q->next = new;
	}
	size ++;
	return;
}



int getsize()
{
	return size;
}


void report(int *v)
{
	int i=0;
	pnode p = head;
	while(p != sentinel)
	{
		v[i ++] = p->val;
		p = p->next;
	}
}

void destory_set()
{
	pnode p = head, q;
	if(p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
}
