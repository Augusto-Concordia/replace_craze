// Assignment #1 - COMP 348, F2022
// Augusto M. Pinheiro - 40208080

#pragma once

#include <sys/types.h>
#include <stdio.h>

typedef struct _custom_file CFILE;

struct _custom_file
{
	FILE* original; //original file stream to be read
	char* filePath; //working directory-relative path of the original file
	int updates; //the number of updates applied on the file
};


//Constructs a custom file
CFILE* ctr_cfile(u_int16_t filePathSize);

//Deconstructs a custom file
void dctr_cfile(CFILE* cfile);


//Default comparing function for a custom file
int cfile_cmpfunc(const void* fa, const void* fb);