/**
 * @brief Assignment 2, `Operating Systems` course at Ariel University
 * 
 * this file contains implementation for copy tool
 * 
 * @version 1
 * @since 28/04/2023
 * @authors Lior Vinman & Yoad Tamar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_files();
int check(FILE*, char*, char);
void nonExist_or_forceCopy(FILE*, FILE*, char*);



/**
 * @brief this function copy one file to another
 * @param f1 source
 * @param f2 destination
*/
void copy_files(FILE *f1, FILE *f2)
{
    size_t bytes_read = 0;
    unsigned char buffer[BUFSIZ] = {0};

    while ((bytes_read = fread(buffer, 1, BUFSIZ, f1)) > 0)
    {
        fwrite(buffer, 1, bytes_read, f2);
    }
}

/**
 * @brief this function open the dest in writing mode and copy the files
 * @param f1 source
 * @param f2 destination
 * @param path a path to new file
*/
void nonExist_or_forceCopy(FILE *f1, FILE *f2, char *path)
{
    f2 = fopen(path, "wb");
    if(f2 == NULL)
    {
        fprintf(stderr, "general failure\n");
        exit(EXIT_FAILURE);
    }

    copy_files(f1, f2);

    fclose(f2);
    f2 = NULL;
}


/**
 * @brief this function checks if file already exists
 * @param f file to copy
 * @param path destination file
 * @param fFlag force flag
 * @return 0 on success , 1 on failure
*/
int check(FILE *f, char *path, char fFlag)
{
    FILE *copy = NULL;
    copy = fopen(path, "r");
    if((copy == NULL) || (copy != NULL && fFlag))
    {
        if(copy == NULL)
        {
            nonExist_or_forceCopy(f, copy, path);
        }
        else if(copy != NULL && fFlag)
        {
            fclose(copy);
            copy = NULL;

            nonExist_or_forceCopy(f, copy, path);
        }

        return EXIT_SUCCESS;
    }
    else
    {
        fclose(copy);
        copy = NULL;

        return EXIT_FAILURE;
    }
}


/**
 * @brief main function, implementing the copy tool
*/
int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 5)
    {
        fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -f]\n");
        exit(EXIT_FAILURE);
    }
    else if(argc == 3)
    {
        if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "-i") || !strcmp(argv[2], "-v") || !strcmp(argv[2], "-v"))
        {
            fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -f]\n");
            exit(EXIT_FAILURE);
        }
    }

    char verbose = '\0', force = '\0';

    if(argc == 4)
    {
        if(!strcmp(argv[3], "-v"))
        {
            verbose = 1;
            force = 0;
        }
        else if(!strcmp(argv[3], "-f"))
        {
            verbose = 0;
            force = 1;
        }
        else
        {
            fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -f]\n");
            exit(EXIT_FAILURE);
        }
    }
    else if(argc == 5)
    {
        if((!strcmp(argv[3], "-f") && !strcmp(argv[4], "-v")) || (!strcmp(argv[3], "-v") && !strcmp(argv[4], "-f")))
        {
            verbose = 1;
            force = 1;
        }
        else
        {
            fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -f]\n");
            exit(EXIT_FAILURE);
        }
    }

    FILE *f = NULL;
    f = fopen(argv[1], "r");
    if(f == NULL)
    {
        fprintf(stderr, "general failure\n");
        exit(EXIT_FAILURE);
    }

    int result = 0;
    result = check(f, argv[2], force);

    if(verbose)
    {
        if(!result)
        {
            fprintf(stdout, "success\n");
        }
        else
        {
            fprintf(stdout, "taget file exist\n");
        }
    }

    fclose(f);
    f = NULL;

    return(result);
}