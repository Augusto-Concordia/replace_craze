#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>

#include "text.h"

void process(FILE* files[], const u_int64_t foundQty, const char* tokenToUppercase, u_int64_t changeNumb[])
{
	for (u_int64_t i = 0; i < foundQty; i++)
	{
		if (files[i] == NULL) continue; //if it's a null pointer, the file doesn't exist

		u_int16_t search_token_length = strlen(tokenToUppercase);
		u_int16_t buffer_length = 0;
		u_int16_t last_token_length = 0;

		char c;

		while (1)
		{
			c = fgetc(files[i]);

			if (c == EOF) break; //we reached the end of the file, get outta here

			if (isspace(c))
			{
				//if we encountered a whitespace character, the last token, the search token and the buffer are the same size, it means that the current token matches our searched one
				if (last_token_length == search_token_length && buffer_length == search_token_length)
				{
					changeNumb[i]++;

					fseek(files[i], -search_token_length - 1, SEEK_CUR);

					for (u_int16_t k = 0; k < search_token_length; k++)
					{
						fputc(toupper(tokenToUppercase[k]), files[i]);
					}
				}

				//reset our length counters
				last_token_length = 0;
				buffer_length = 0;
			}
			else 
			{
				//the current token always increases length if it's a non-space character
				last_token_length++;

				c = tolower(c);

				//if we haven't surpassed the length of the token we're looking for, add the current character (lowercased) to the buffer
				if (buffer_length < search_token_length + 1 && c == tolower(tokenToUppercase[buffer_length])) {
					buffer_length++;
				}
			}

		}

		//we're done with the file, closed!
		fclose(files[i]);
	}
}