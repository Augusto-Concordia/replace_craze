#include <stdio.h>
#include <dirent.h>

#include "traversal.h"
#include "text.h"

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		fprintf(stderr, "Too many arguments passed, exiting...\n");
		return -1;
	}

	FILE* found[10];

	find_files(".", found);

	process(found, 1/*sizeof(found) / sizeof(found[0])*/, argv[argc - 1]);

	return 0;
}