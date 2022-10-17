// Assignment #1 - COMP 348, F2022
// Augusto M. Pinheiro - 40208080

#include <string.h>
#include <stdlib.h>

#include "cfile.h"

CFILE* ctr_cfile(u_int16_t filePathSize)
{
	CFILE* new_cfile = malloc(sizeof(CFILE)); //initial struct size

	//if we ever cannot allocate memory for a specific member of the struct, clean whatever allocation we did and leave

	if (new_cfile == NULL)
		return NULL;

	new_cfile->original = malloc(sizeof(FILE));

	if (new_cfile->original == NULL)
	{
		free(new_cfile);
		return NULL;
	}

	new_cfile->filePath = malloc(filePathSize);

	if (new_cfile->filePath == NULL)
	{
		fclose(new_cfile->original);
		free(new_cfile);
		return NULL;
	}

	return new_cfile;
}

void dctr_cfile(CFILE* cfile)
{
	if (cfile != NULL)
	{
		fclose(cfile->original);

		free(cfile->filePath);

		free(cfile);
	}
}

int cfile_cmpfunc(const void* fa, const void* fb)
{
	return (*(CFILE**)fb)->updates - (*(CFILE**)fa)->updates;
}