/*============================================
 *	Filename:
 *       sort.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will achieve quick sort.
 *		
 *	Author/Create Date:
 *		Myth Zhai,Nov14'14
 *
 *  Modification History:
 *
 *
 *  Note:
 *
 *============================================
 */

#include<stdio.h>
#include<stdlib.h>
void quick_sort (int data[], size_t left,
		size_t right) {
	size_t p = (left + right) / 2;
	int pivot = data[p];
	size_t i = left, j = right;
	while (i < j) {
		for (; ! (i >= p || pivot < data[i]); ++i);
		if (i < p) {
			data[p] = data[i];
			p = i;
		}
		for (; ! (j <= p || data[j] < pivot); --j);
		if (j > p) {
			data[p] = data[j];
			p = j;
		}
	}
	data[p] = pivot;
	if (p - left > 1)
		quick_sort (data, left, p - 1);
	if (right - p > 1)
		quick_sort (data, p + 1, right);
}
/* 测试用例 */
int main (void) {
	srand (time (NULL));
	int data[100000];
	size_t i, size = sizeof(data) / sizeof(data[0]);
	for (i = 0; i < size; ++i){
		//data[i] = 1;
		data[i] = i + 1; 
		printf ("%2d ", data[i] /*= rand () % 100000*/);
	}
	printf ("\n");
	quick_sort (data, 0, size - 1);
	for (i = 0; i < size; ++i)
		printf ("%2d ", data[i]);
	printf ("\n");
	return 0;
}
