#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "text.h"
#include "list.h"

void process(FILE* files[], const int l, const char* tokenToUppercase)
{
	for (u_int32_t i = 0; i < l; i++)
	{
		if (files[i] == NULL) continue;

		fseek(files[i], 0, SEEK_END);
		u_int32_t file_size = ftell(files[i]);
		fseek(files[i], 0, SEEK_SET);

		u_int8_t size_of_token = 0;

		while (tokenToUppercase[size_of_token] != '\0')
		{
			size_of_token++;
		}

		char buffer[size_of_token + 1];
		int buffer_pos = 0;

		for (u_int32_t j = 0; j < file_size; j++)
		{
			char c = fgetc(files[i]);

			if (!isalnum(c)) {
				buffer_pos = 0;
				memset(buffer, 0, size_of_token);
				continue;
			}

			buffer[buffer_pos] = tolower(c);
			buffer_pos = min(buffer_pos+ 1, size_of_token);

			if (buffer_pos == size_of_token)
			{
				buffer[size_of_token] = '\0';
			}

			if (!strcmp(buffer, tokenToUppercase))
			{
				fseek(files[i], -size_of_token, SEEK_CUR);
				
				for (u_int8_t k = 0; k < size_of_token; k++)
				{
					fputc(toupper(buffer[k]), files[i]);
				}
			}
			else
			{
				fseek(files[i], -1, SEEK_CUR);
				fputc(c, files[i]);
			}

			continue;

			if (isalnum(c))
			{
				//addval(token, &c);
				//j++;
			}
			else
			{
				/*char string_token[token->size];

				for (size_t m = 0; m < token->size; m++)
				{
					char* ch = (char*)getval(token, m);
					printf("%c", ch);
					string_token[m] = ch;
				}

				if (!strcmp(tokenToUppercase, string_token)) strupr(string_token);

				for (size_t k = 0; k < j; k++)
				{
					fputc(last_token[k], files[i]);
				}

				fputc(c, files[i]);*/

				/*if (last_token[0] == 0) break;

				if (!strcmp(tokenToUppercase, last_token)) strupr(last_token);

				printf("%s ", last_token);

				int s = addval(content, last_token);

				char* val = (char*)getval(content, s - 1);

				printf("Val: %s\n", val);*/

				//memset(last_token, 0, 26);
				//j = 0;
			}
		}

		fclose(files[i]);
	}
}

int min(int a, int b)
{
	return a > b ? b : a;
}

void strupr(char* str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		str[i] = toupper(str[i]);
		i++;
	}
}