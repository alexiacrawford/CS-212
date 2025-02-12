#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int allowedChars(int bytes, int index, unsigned char *buff)
{
       index++;
       if (index < 0)
        return 1;           
    if (bytes - 1 == index) 
    {
        return 1; 
    }
    if (buff[index] == ' ' || buff[index] == '\0' || buff[index] == '\n' || buff[index] == '.' || buff[index] == ',')
    {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int arguments = 0;     
    int matchingWords = 0; 
    int matchedChars = 0;  
    int numArgs = argc - 2;
    int argIndex = 0; 
    int offset = 1;  
    int *counts = malloc(numArgs * sizeof(int));
    int countsInd = 0;
    int lengthStr = 0;
    int numBytes, args, maxArgIndex, q, idk, mem, bIdx;


    for (mem = 0; mem != numArgs; mem++)
        counts[mem] = 0;

    if (argc < 3) 
    {
        printf("File and or word(s) not provided");
        exit(EXIT_FAILURE);
    }

    FILE *fName = fopen(argv[1], "r");
    if (fName == NULL) 
    {
        printf("\"<%s>\" is not a valid file", argv[1]);
        exit(EXIT_FAILURE);
    }

    fseek(fName, 0, SEEK_END);                           
    numBytes = (ftell(fName));                          
    unsigned char *buff = malloc(numBytes);             
    fseek(fName, 0, SEEK_SET);                           
    fread(buff, sizeof(unsigned char), numBytes, fName); 
    fclose(fName);
    
    arguments = argc - 1;
    
    for (args = 2; args != argc; args++)
    {
        lengthStr = strlen(argv[args]);
        
        argIndex = 0;
        maxArgIndex = strlen(argv[args]);
        
        for (q = 0; q < numBytes; q++)
        {
            if (argIndex > maxArgIndex)
                argIndex = 0;
            if (buff[q] == argv[args][argIndex])
            {
                
                matchedChars++;
                argIndex++;
                offset++;
                if ((matchedChars == lengthStr) && (allowedChars(numBytes, q, buff) == 1))
                {
                    if ((q - 1) != 0)
                    {
                        if (allowedChars(numBytes, (q - offset) - 1, buff) == 1)                         {
                            
                            matchingWords++;
                            counts[countsInd]++;
                            argIndex = 0;
                            matchedChars = 0;
                            offset = 0;
                            if (q == numBytes - 1)
                                break;
                        }
                    }
                    if ((q - 1) == 0)
                    {
                        if (allowedChars(numBytes, q, buff))
                        {
                           
                            matchingWords++;
                            counts[countsInd]++;
                            argIndex = 0;
                            matchedChars = 0;
                            if (q == numBytes - 1)
                                break;
                        }
                    }
                }
            }
            if (allowedChars(numBytes, q - 1, buff) == 1 || allowedChars(numBytes, q, buff) == 1)
            {
                matchedChars = 0;
                argIndex = 0;
                offset = 0;
            }
        }
        countsInd++;
    }

    countsInd = 0;
    for (idk = 2; idk < argc; idk++)
    {
        printf("The word \"%s\" occurs %d times.\n", argv[idk], counts[countsInd]);
        countsInd++;
    }

    free(buff);
    free(counts);
    return 0;
}
