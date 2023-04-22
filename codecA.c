#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
        if(input[length - 1] >= 65 && input[length - 1] <= 90)
        {
            result[length - 1] = (char)(tolower(input[length - 1]));
        }
        else if(input[length - 1] >= 97 && input[length - 1] <= 122)
        {
            result[length - 1] = (char)(toupper(input[length - 1]));
        }
        else
        {
            result[length - 1] = (char)(input[length - 1]);
        }

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
        if(input[length - 1] >= 65 && input[length - 1] <= 90)
        {
            result[length - 1] = (char)(tolower(input[length - 1]));
        }
        else if(input[length - 1] >= 97 && input[length - 1] <= 122)
        {
            result[length - 1] = (char)(toupper(input[length - 1]));
        }
        else
        {
            result[length - 1] = (char)(input[length - 1]);
        }

        length++;

        result = (char*)realloc(result, length);
        if(result == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    return result;
}