// Assignment #1 - COMP 348, F2022, F2022
// Augusto M. Pinheiro - 40208080

#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "text.h"
#include "cfile.h"

void process(CFILE* files[], const int foundQty, const char* tokenToUppercase)
{
	for (int i = 0; i < foundQty; i++)
	{
		if (files[i] == NULL) continue; //if it's a null pointer, the file doesn't exist

		size_t search_token_length = strlen(tokenToUppercase);
		u_int16_t buffer_length = 0;
		u_int16_t last_token_length = 0;

		int c;

		while (1)
		{
			c = fgetc(files[i]->original);

			if (c == EOF) break; //we reached the end of the file, get outta here

			if (isspace(c))
			{
				//if we encounter a whitespace character, the last token, the search token and the buffer are the same size, it means that the current token matches our searched one
				if (last_token_length == search_token_length && buffer_length == search_token_length)
				{
					//we found a corresponding token, go back the length of the token and we'll rewrite it uppercased
					fseek(files[i]->original, -search_token_length - 1, SEEK_CUR);

					for (u_int16_t k = 0; k < search_token_length; k++)
					{
						fputc(toupper(tokenToUppercase[k]), files[i]->original);
					}

					files[i]->updates++;
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

				//if we haven't surpassed the length of the token we're looking for, add the current character (lowercased) to the buffer if it equals to the corresponding one of our searched-for token
				if (buffer_length < search_token_length + 1 && c == tolower(tokenToUppercase[buffer_length])) {
					buffer_length++;
				}
			}

		}
	}
}