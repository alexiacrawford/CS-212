#include <stdio.h>

int main (int argc, char *argv[])
{
	int buffer[25];
	int result[25];
	char *f1 = argv[1];
	char *f2 = argv[2];
	FILE *in = fopen(f1, "rb");
	FILE *out = fopen(f2, "w");

	for (int i = 0; i < 5; i++)
	{
		if (fseek(in, i * sizeof(int) * 10, SEEK_SET) != '\0')
		{
			printf("Error in the input file");
			fclose(in);
			fclose(out);
			return 1;
		}
		size_t num_of_bytes = fread(buffer, sizeof(int), 5, in);
		for (int j = 0; j < 5; j++)
		{
			result[j + 5 * i] = buffer[j];
		}
	}
	for (int i = 0; i < 25; i++)
	{
		fprintf(out, "%d\n", result[i]);
	}
	fclose(in);
	fclose(out);
	return 0;
}

