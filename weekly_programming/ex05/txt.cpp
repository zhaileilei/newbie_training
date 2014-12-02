/*============================================
 *	Filename:
 *       txt.cpp
 *
 *  Copright (C) 2014 Wistron
 *  All rights reserved
 *	Description:
 *		This file will generate K integers that don't repeat.
 *		
 *	Author/Create Date:
 *		Myth Zhai,Oct24'14
 *
 *  Modification History:
 *
 *
 *  Note:
 *
 *============================================
 */



#include<cstdlib>  
#include<iostream>  
#include<ctime>  
#include<fstream>
#include<cstdio>
#include<cstring>
using namespace std;  

#define N 10000000  

void swap(int a,int b);  
int main()  
{  
	int i;  
	int k;
	int *num = new int[N];  

	srand((unsigned)time(NULL));  
	FILE *f = fopen("a.txt","wt");
	if(f){
		cout<<"please input k:";  
		cin>>k;  
		//initialized num array  
		for(i = 0;i < N;i++)  
			num[i] = i;  
		
		//swap numbers of array  
		for(i = 0;i < k;i ++){  
			swap(num[i],num[rand()%N]);  

			fprintf(f,"%d ",num[i]);
		}
	//output numbers  
	for(i = 0;i < k;i ++)
	
		cout<<num[i]<<"  "; 

		delete[] num;  
		cout<<endl;
		fwrite(&k,sizeof(int),1,f);
		fclose(f);
		f = NULL;
	}
	
	return 0;
}  

void swap(int a,int b)  
{  
	int temp;  
	temp = a;  
	a = b;  
	b = temp;  
}  
