#include <sys/types.h>
#include <stdio.h>

void print_report(const int foundFileNames, const char* fileNames, const int* changedNumb)
{
	for (u_int64_t i = 0; i < foundFileNames; i++)
	{
		printf("Report\n\n");

		printf("%d. %s: $d", i, fileNames[i], changedNumb[i]);
	}
}