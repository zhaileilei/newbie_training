/*===========================
 *	Filename:
 *	qsort.c
 *
 *	Copyright (C) 2014 Wistron
 *	All rights reserved.
 *
 *	Description:
 *		This file will achieve Insertion sort.
 *
 *	Author/Create Date:
 *		Myth Zhai, Oct16'14
 *
 *	Modification History:
 *
 *
 *	Note:
 *=================================
 */

/* Include Files */
#include <stdio.h>
#include <stdlib.h>

/* Before optimization */
void insert1_sort (int data[], size_t size) {
	size_t i;
	for (i = 1; i < size; ++i) {

		size_t j,t;
		for (j = i; j > 0 && data[j] < data[j-1];
				--j){
			t =data[j];
			data[j] = data [j-1];
			data[j-1] =t;
		}

	}
}
/* After optimization */
void insert_sort (int data[], size_t size) {
	size_t i;
	for (i = 1; i < size; ++i) {
		int inserted = data[i];
		size_t j;
		for (j = i; j > 0 && inserted < data[j-1];
				--j){

			data[j] = data[j-1];
		}
		if (j != i)
			data[j] = inserted;
	}
}

/* test */
int main (void) {
	srand (time (NULL));
	int data[10000];

	size_t i, size = sizeof(data) / sizeof(data[0]);
	for (i = 0; i < size; ++i){
		//data[i] = i +1;
		data[i]=1;

		printf("%2d ", data[i] /*=rand () % 10000*/ );
	}
	printf ("\n");
	insert1_sort (data, size);
	for (i = 0; i < size; ++i)
		printf ("%2d ", data[i]);
	printf ("\n");
	return 0;
}
