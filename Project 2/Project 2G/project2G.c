#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{	

	int counter = 0; // specified set of words
	int matching_words = 0; //how many times the word occurs
	int matched_chars = 0; // amount of matched characters
	int num_args = argc - 2;
	int arg_index = 0;
	int offset = 1; // counts for commas, spaces, periods 
	int *counts = malloc(num_args * sizeof(int));
	int counts_index = 0;

	if (argc < 3)
	{
		printf("file name not provided/n");
		exit(EXIT_FAILURE);
	}
	FILE *fname = fopen(argv[1], "r"); //file to be read
	if (fname == NULL)
	{
		printf("\"<%s>\" is not a valid file", fname);
		exit(EXIT_FAILURE); 
	}
	fseek(fname, 0, SEEK_END); 
	int bytes = ftell(fname); //looks at how pointer has moved
	unsigned char *buff = malloc(bytes);
	fseek(fname, 0, SEEK_SET); //beginning file pointer
	fread(buff, sizeof(unsigned char), bytes, fname);
	fclose(fname);

	int arguments = argc - 1;
	char * args;
	for (int args = 2; args != argc; args++)
	{
		arg_index = 0;
		int max_arg_index = strlen(argv[args]);
		for (int e = 0; e < bytes; e++)
		{
			if (arg_index > max_arg_index)
			{
				arg_index = 0;
			}
			if (buff[e] == argv[args][arg_index])
			{
				matched_chars++;
				arg_index++;
				offset++;
				if ((matched_chars == strlen(argv[args])) && (buff[e + 1] == ' ' || buff[e + 1] == '\0' || buff[e + 1] == '\n' || buff[e + 1]  == '.' || buff[e + 1] == ',' )) // account for spaces, periods, commas...
				{
					if ((e - 1) != 0)
					{
						if (buff[e - offset] == ' ' || buff[e - offset] == '\0' || buff[e - offset] == '\n') // account for offset
						{
							matching_words++;
							counts[counts_index]++;
							arg_index = 0;
							offset = 0;
						}
					}
					if ((e - 1) == 0)
					{
						if (buff[e + 1] == ' ' || buff[e + 1] == '\n' || buff[e + 1] == '.' || buff[e + 1] == '\0' || buff[e + 1] == ',')
						{
							matching_words++;
							counts[counts_index]++;
							arg_index = 0;
							matched_chars = 0;
						}
					}
				}
			}
			if (buff[e] == ' ' || buff[e+1] == '\0' || buff[e+1] == '\n' || buff[e] == '\n')
			{
				matched_chars = 0;
				arg_index = 0;
				offset = 0;
			}
		}
		counts_index++;
	}
	counts_index = 0;
	for (int j = 2; j < argc; j++)
	{
		printf("The word \"%s\" occurs %d times.\n", argv[j], counts[counts_index]);
		counts_index++;
	}
	free(buff); // no memory leaks
	free(counts);
	return 0;
}
