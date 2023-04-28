/**
 * @brief Assignment 2, `Operating Systems` course at Ariel University
 * 
 * this file contains implementation of first coder-decoder
 * 
 * @version 1
 * @since 28/04/2023
 * @authors Lior Vinman & Yoad Tamar
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* encode(char*);
char* decode(char*);


/**
 * @brief this function encodes upper case to lower case and vise versa
 * @param input a string to encode
 * @return encoded string
*/
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


/**
 * @brief this function decodes upper case to lower case and vise versa
 * @param input a string to decode
 * @return decoded string
*/
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