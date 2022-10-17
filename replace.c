// Assignment #1 - COMP 348, F2022
// Augusto M. Pinheiro - 40208080

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "cfile.h"
#include "traversal.h"
#include "report.h"
#include "text.h"

//Cleans up any memory allocation created by the process
void clean(CFILE* files[], int foundFilesNumb)
{
	for (int i = 0; i < foundFilesNumb; i++)
	{
		dctr_cfile(files[i]);
	}
}

//Driver function of replace_craze
int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		fprintf(stderr, "Too many arguments passed (expecting 1), exiting...\n");
		return -1;
	}

	if (argc == 1)
	{
		fprintf(stderr, "Too little arguments passed (expecting 1), exiting...\n");
		return -1;
	}

	CFILE* files[10000]; //all found files that we'll change
	int found_files_numb = 0; //the number of files found

	find_files(".", files, &found_files_numb); 

	process(files, found_files_numb, argv[argc - 1]);

	print_report(argv[argc -1], found_files_numb, files);

	clean(files, found_files_numb);

	return 0;
}