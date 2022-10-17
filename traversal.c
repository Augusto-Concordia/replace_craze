// Assignment #1 - COMP 348, F2022
// Augusto M. Pinheiro - 40208080

#define _GNU_SOURCE

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "cfile.h"
#include "traversal.h"

void find_files(const char pathStart[], CFILE* files[], int* foundNumb)
{
	DIR* p_rootDir = opendir("."); //opens the current directory

	if (p_rootDir == NULL) return;

	struct dirent* p_dirEntry;

	while ((p_dirEntry = readdir(p_rootDir))) //while there's a directory
	{
		if (is_invalid_folder(p_dirEntry->d_name)) continue; //if it's an invalid folder, we don't care about it

		char fullDirName[1 + sizeof(p_dirEntry->d_name)] = ""; //will contain the relative path of the file 

		strcat(fullDirName, pathStart);
		strcat(fullDirName, "/");
		strcat(fullDirName, p_dirEntry->d_name);

		if (p_dirEntry->d_type == DT_DIR) //it's a folder! let's get in
		{
			chdir(p_dirEntry->d_name); //change the current working directory to the one we found
			find_files(fullDirName, files, foundNumb); //look for files in that folder (and the subsequent ones)
			chdir(".."); //come back to the previous working directory
			continue;
		}

		if (is_invalid_file(p_dirEntry->d_name)) continue; //if it's an invalid file, we don't care about it

		FILE* file = fopen(p_dirEntry->d_name, "r+"); //opens the file with reading + writing permissions

		if (file == NULL) continue; //failed to create a file, probably doesn't exist or is being used: we don't take it into account

		CFILE* cfile = ctr_cfile(sizeof(fullDirName));

		if (cfile == NULL) continue; //out of memory? just leave

		cfile->original = file;

		strcpy(cfile->filePath, fullDirName);

		files[*foundNumb] = cfile; //assigns the custom file struct to the array

		(*foundNumb)++; //increase the pointer-referenced counter
	}

	closedir(p_rootDir); //close the directory, we're done with it
}

const int is_invalid_folder(const char* folderName)
{
	//if it's this or the parent directory, it's invalid
	return !strcmp(folderName, ".") || !strcmp(folderName, "..");
}

const int is_invalid_file(const char* fileName)
{
	size_t dir_name_length = strlen(fileName);

	//if it's not a text file, it's invalid
	return !(fileName[dir_name_length - 1] == 't' && fileName[dir_name_length - 2] == 'x' && fileName[dir_name_length - 3] == 't' && fileName[dir_name_length - 4] == '.');
}