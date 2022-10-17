// Assignment #1 - COMP 348, F2022
// Augusto M. Pinheiro - 40208080

#pragma once

#include <stdio.h>

#include "cfile.h"

//Reads each file and replaces the found token by its uppercase version
void process(CFILE* files[], const int foundQty, const char* tokenToUppercase);