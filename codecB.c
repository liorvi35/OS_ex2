/**
 * @brief Assignment 2, `Operating Systems` course at Ariel University
 * 
 * this file contains implementation of second coder-decoder
 * 
 * @version 1
 * @since 28/04/2023
 * @authors Lior Vinman & Yoad Tamar
*/

#include <stdio.h>
#include <stdlib.h>

char* encode(char*);
char* decode(char*);


/**
 * @brief this function encodes each char to the next 3-rd char
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


/**
 * @brief this function decodes each char to the past 3-rd char
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