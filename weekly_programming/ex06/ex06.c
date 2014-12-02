/*============================================
 *	Filename:
 *       ex06.c
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will achieve Sort bitmap
 *		
 *	Author/Create Date:
 *		Myth Zhai,Oct31'14
 *
 *  Modification History:
 *
 *
 *  Note:
 *
 *============================================
 */


#include <stdio.h>  
#include <math.h>  
#include <time.h>  

#define BITSPERWORD 32  
#define SHIFT 5  
#define MASK 0x1F  
#define N 10000000  
#define M 1000000
 
int a[1 + N/BITSPERWORD];  

void set(int i){  
	a[i >> SHIFT] |= (1<<(i & MASK));  
}  
void clr(int i){  
	a[i >> SHIFT] &= ~(1<<(i & MASK));  
}  
int test(int i){  
	return a[i >> SHIFT] & (1<<(i & MASK));  
}  

int myRand()    
{  
	int num;  
	num = rand() % 10000000;  
	return num;  
}  
int main(void) {  
	int i;  
	int j;
	int k;
	int arr[M];  
	int count=0;  
	for (i = 0; i < N; i++) {  
		clr(i);  
	}  
 
	srand( (unsigned)time( NULL ) );       
	printf("The count of array is %2d:/n\n",5*M);  
	for (k=0;k<5;k++){
		for (j = 0; j < M; j++) {    
			arr[j]=myRand();        
			printf("%2d ",arr[j]);  
		}  

		for (j = 0; j < M; j++) {     
			set(arr[j]);  
		}  
	}
	printf("\n");
	printf("/nAfter Sorted:/n\n");  
	for (i = 0; i < N; i++) {  
		if (test(i)) {  
			printf("%2d ", i);  
			count++;  
		}  
	}
	printf("\n");
	printf("The count of array is %2d:/n\n",5*M);  
	printf("/nAfter sorted count is %2d/n\n",count);      
	return 0;  
}   


