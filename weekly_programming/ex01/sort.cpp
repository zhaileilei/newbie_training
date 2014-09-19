//==========================
// Filename:
//		sort.cpp
// Copyright (C) 2014 Wistron
// All rights reserved.
// Description:
//		This file will Read/Write File .
// Author/Created Date:
//       Myth Zhai,Sep17'14
//
// Modification History:
//
//
//
// Note:
//
//==========================

/* Include Files*/
#include <iostream>      
#include <cstdlib>
#include <cstdio>
#include <ctime>      
#include <cassert>
#include <fstream> 
#include <cstring>
/* MACROS  */
#ifndef EXTERN_SORT_H      
#define EXTERN_SORT_H

/* Add namespaces in the data before the */

using namespace std;

/* The definition of a class */
class ExternSort      
{      
	public:      
		void sort()      
		{   /* VARIABLES */   
			time_t start = time(NULL);              
			int file_count = memory_sort();        
			merge_sort(file_count);      
			time_t end = time(NULL);
			printf("total time:%f\n", (end - start)*1.0 );      
		}      
			/* The constructor */
		ExternSort(const char *input_file, const char * out_file, int count)      
		{      
			m_count = count;      
			m_in_file = new char[strlen(input_file) + 1];      
			strcpy(m_in_file, input_file);      
			m_out_file = new char[strlen(out_file) + 1];      
			strcpy(m_out_file, out_file);      
		} 
		/* The destructor */
		virtual ~ExternSort()      
		{      
			delete [] m_in_file;      
			delete [] m_out_file;      
		}      
	private:
		/* vARIABLES */
		int m_count;        
		char *m_in_file;          
		char *m_out_file;         
	protected:      
		int read_data(FILE* f, int a[], int n)      
		{      
			int i = 0;      
			while(i < n && (fscanf(f, "%d", &a[i]) != EOF))       
				i++;      
			printf("read:%d integer\n", i);      
			return i;      
		}      
		void write_data(FILE* f, int a[], int n)      
		{      
			for(int i = 0; i < n; ++i)      
				fprintf(f, "%d ", a[i]);      
		}      
		char* temp_filename(int index)      
		{      
			char *tempfile = new char[100];      
			sprintf(tempfile, "temp%d.txt", index);      
			return tempfile;      
		}      
		static int cmp_int(const void *a, const void *b)      
		{      
			return *(int*)a - *(int*)b;      
		}      
		/* Member function */
		int memory_sort()      
		{      
			FILE* fin = fopen(m_in_file, "rt");      
			int n = 0, file_count = 0;int *array = new int[m_count];      
           /*Each read m_count integers to do a sort in memory, 
			 and to write temporary file*/
			while(( n = read_data(fin, array, m_count)) > 0)      
			{      
				qsort(array, n, sizeof(int), cmp_int);        
				char *fileName = temp_filename(file_count++);      
				FILE *tempFile = fopen(fileName, "w");      
				free(fileName);      
				write_data(tempFile, array, n);      
				fclose(tempFile);      
			}      
			delete [] array;      
			fclose(fin);      
			return file_count;      
		}      
		/*  Member function */
		void merge_sort(int file_count)      
		{      
			if(file_count <= 0)       
				return;
			FILE*fout=fopen(m_out_file,"wt");
			FILE* *farray = new FILE*[file_count];      
			int i;      
			for(i = 0; i < file_count; ++i)      
			{      
				char* fileName = temp_filename(i);      
				farray[i] = fopen(fileName, "rt");      
				free(fileName);      
			}      
			int *data = new int[file_count];           
			bool *hasNext = new bool[file_count];      
			memset(data, 0, sizeof(int) * file_count);      
			memset(hasNext, 1, sizeof(bool) * file_count);      
			for(i = 0; i < file_count; ++i)      
			{      
				if(fscanf(farray[i], "%d", &data[i]) == EOF)         
					hasNext[i] = false;      
			}      

			while(true)      
			{  
				/*Minimum numbers available in data, 
				  and record the corresponding file index*/         
				int min = data[0];      
				int j = 0;      
				while (j < file_count && !hasNext[j])      
					j++;
				/* No desirable digital terminating merge */
				if (j >= file_count)              
					break;      
				for(i = j + 1; i < file_count; ++i)      
				{      
					if(hasNext[i] && min > data[i])      
					{      
						min = data[i];      
						j = i;      
					}      
				}      
				if(fscanf(farray[j], "%d", &data[j]) == EOF)         
					hasNext[j] = false;      
				fprintf(fout, "%d ", min);      
			}      

			delete [] hasNext;      
			delete [] data;      
			for(i = 0; i < file_count; ++i)      
			{      
				fclose(farray[i]);      
			}    
			delete [] farray;      
			fclose(fout);      
		}      
};      
#endif            
/* CONSTARNTS */
const unsigned int count = 10000000;       
const unsigned number_to_sort=1000000;
/* he original is not sorted file name */
const char *unsort_file = "unsort_data.txt";       
/* Already sorted file name */
const char *sort_file = "sort_data.txt";
/* Randomly generated data files */
void init_data(unsigned int num);       

      

int main(int argc, char* *argv)      
{      
	srand(time(NULL));      
	init_data(count);      
	ExternSort extSort(unsort_file, sort_file, number_to_sort);      
	extSort.sort();            
	return 0;      
}      

void init_data(unsigned int num)      
{      
	FILE* f = fopen(unsort_file, "wt");      
	for(int i = 0; i < num; ++i)      
		fprintf(f, "%d ", rand());      
	fclose(f);      
}     
