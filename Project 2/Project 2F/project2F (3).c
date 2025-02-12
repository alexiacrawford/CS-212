#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_strlen(char *s)
{
	int len = 0;
    while (*s != '\0') {
        len += 1;
        s++;
    }
    return len;
}



void str_reverse(char *str)
{
	int len = my_strlen(str);
	int i ;
	for (i = 0; i < len / 2; i++)
	{
		char temp;
		temp = str[len - i -1];
		str[len - i - 1] = str[i];
		str[i] = temp;
	}
}

int main()
{
    char *str = malloc(strlen("hello world")+1);
    char *str2 = malloc(strlen("cs 212")+1);
    strcpy(str, "hello world");
    strcpy(str2, "cs 212");
    str_reverse(str);   
    str_reverse(str2);
    if (strcmp(str, "dlrow olleh") == 0)
    {
        if (strcmp(str2, "212 sc") == 0)
        {
            printf("Congrats!  You have successfully reversed \"hello world\" to \"%s\"\n", str);
            exit(EXIT_SUCCESS);
        }
    }

    printf("Project does not work yet.  You reversed \"hello world\" to \"%s\" and \"cs 212\" to \"%s\"\n", str, str2);
    exit(EXIT_FAILURE);
}
