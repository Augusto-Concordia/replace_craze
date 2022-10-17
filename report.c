// Assignment #1 - COMP 348, F2022
// Augusto M. Pinheiro - 40208080

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cfile.h"

void print_report(const char* target, const int foundFileNumb, CFILE* files[])
{
	//get the current working directory
	char cwd[512];
	getcwd(cwd, sizeof(cwd));

	printf("Update report for target string \"%s\" (%d text files found):\n\n", target, foundFileNumb);

	printf("Currently in: %s\n\n", cwd);

	//if we haven't found any files, say it and leave it
	if (foundFileNumb == 0)
	{
		puts("No files found.");
		return;
	}

	//sort the array according to the comparator function (by desc updates)
	qsort((CFILE**)files, foundFileNumb, sizeof(files[0]), cfile_cmpfunc);

	puts("-------------------------\n");
	puts("Updates       File Path");

	for (int i = 0; i < foundFileNumb; i++)
	{
		printf("%d		 %s\n", files[i]->updates, files[i]->filePath);
	}


	puts("\nDone! See you later :)");
}