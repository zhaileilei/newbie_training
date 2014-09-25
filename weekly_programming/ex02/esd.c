/*===========================
 *	Filename:
 *	esd.c
 *	Copyright (C) 2014 Wistron
 *	All rights reserved.
 *
 *	Description:
 *		This file will achieve the number of output 1
 *
 *	Author/Create Date:
 *		Myth Zhai, Sep26'14
 *	Modification History:
 *
 *
 *	Note:
 *=================================
*/
/* Include Files */
#include<stdio.h>
int main(){
int num1;
/* DEFINES */
int num2=0;
int i=0;
printf("请输入一个整数:");
scanf("%d",&num1);
for(i=0;i<32;i++){
	num2+=(num1 >> i) & 0x1;
}
	printf("该整数1的个数为%d\n",num2);
	return 0;
}
