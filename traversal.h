#pragma once

#include <sys/types.h>
#include <stdio.h>

void find_files(const char* rootName, FILE* found[], char* fileNames[], u_int64_t* foundNumb);

const int is_invalid_directory(const char* dirName);