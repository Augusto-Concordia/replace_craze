#pragma once
#include <stdio.h>

void find_files(const char* rootName, FILE* found[]);

void find_files_directory(const char* rootName, FILE* found[], int* n);

const int is_invalid_directory(const char* dirName);