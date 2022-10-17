#define _GNU_SOURCE

#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "traversal.h"

void find_files(const char* rootName, FILE* found[], char* fileNames[], u_int64_t* foundNumb)
{	
	DIR* p_rootDir = opendir(rootName);

	if (p_rootDir == NULL)
	{
		return NULL;
	}

	struct dirent* p_dirEntry;

	while ((p_dirEntry = readdir(p_rootDir)))
	{
		if (is_invalid_directory(p_dirEntry->d_name)) continue;

		if (p_dirEntry->d_type == DT_DIR)
		{
			chdir(p_dirEntry->d_name);
			find_files(".", found, foundNumb, fileNames);
			chdir("..");
			continue;
		}

		FILE* file = fopen(p_dirEntry->d_name, "r+");

		if (file == NULL) continue;

		found[*foundNumb] = file;
		fileNames[*foundNumb] = p_dirEntry->d_name;

		(*foundNumb)++;
	}

	closedir(p_rootDir);
}

const int is_invalid_directory(const char* dirName)
{
	u_int16_t dir_name_length = strlen(dirName);

	return !strcmp(dirName, ".") || !strcmp(dirName, "..") || (dirName[dir_name_length] == '.' && dirName[dir_name_length - 1] == 't' && dirName[dir_name_length - 2] == 't' && dirName[dir_name_length - 3] == 'x' && dirName[dir_name_length - 4] == 't');
}