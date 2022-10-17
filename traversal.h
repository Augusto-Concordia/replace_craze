// Assignment #1 - COMP 348, F2022
// Augusto M. Pinheiro - 40208080

#pragma once

#include <sys/types.h>
#include <stdio.h>

#include "cfile.h"

//Traverses the current directory and looks for .txt files
void find_files(const char pathStart[], CFILE* files[], int* foundNumb);

//checks if the testing directory is an invalid folder and if it ends with the correct extension
const int is_invalid_folder(const char* folderName);

//checks if the testing directory is an invalid file and if it ends with the correct extension
const int is_invalid_file(const char* fileName);