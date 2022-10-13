#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "traversal.h"

void find_files(const char* rootName, FILE* found[])
{	
	int start = 0;

	find_files_directory(rootName, found, &start);
}

void find_files_directory(const char* rootName, FILE* found[], int* n)
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
			find_files_directory(".", found, n);
			chdir("..");
			continue;
		}

		FILE* file = fopen(p_dirEntry->d_name, "r+");

		if (file == NULL) continue;

		found[*n] = file;

		(*n)++;
	}

	closedir(p_rootDir);
}

const int is_invalid_directory(const char* dirName)
{
	return !strcmp(dirName, ".") || !strcmp(dirName, "..") || !strcmp(dirName, "ass_1.out");
}