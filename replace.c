#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "traversal.h"
#include "report.h"
#include "text.h"

int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		fprintf(stderr, "Too many arguments passed, exiting...\n");
		return -1;
	}

	FILE* found[100000];
	char* file_names[100000];
	u_int32_t found_numb = 0;

	find_files(".", found, file_names, &found_numb);

	u_int64_t changed_per_file_numb[found_numb];

	process(found, found_numb, argv[argc - 1], changed_per_file_numb);

	print_report(found_numb, file_names, changed_per_file_numb);

	return 0;
}