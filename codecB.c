#include <stdio.h>
#include <stdlib.h>

char* encode(char*);
char* decode(char*);


char* encode(char *input)
{
    int length = 1;

    char *result = NULL;
    result = (char*)calloc(length, sizeof(char));
    if(result == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while(input[length - 1] != '\0')
    {
        result[length - 1] = (char)(input[length - 1] + 3);

        length++;

        result = (char*)realloc(result, length);
        if(result == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    return result;
}

char* decode(char *input)
{
    int length = 1;

    char *result = NULL;
    result = (char*)calloc(length, sizeof(char));
    if(result == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while(input[length - 1] != '\0')
    {
        result[length - 1] = (char)(input[length - 1] - 3);

        length++;

        result = (char*)realloc(result, length);
        if(result == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    return result;
}