/**
 * @brief Assignment 2, `Operating Systems` course at Ariel University
 * 
 * this file contains implementation for compare tool
 * 
 * @version 1
 * @since 28/04/2023
 * @authors Lior Vinman & Yoad Tamar
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compare_files(FILE*, FILE*, char);


/**
 * @brief this function compares between two files
 * @param f1 first file
 * @param f2 seconds file
 * @param iFlag ignore flag to ignore upper and lower case
 * @return 0 on success , 1 on failure
*/
int compare_files(FILE *f1, FILE *f2, char iFlag)
{   
    char c1 = '\0', c2 = '\0';
    c1 = fgetc(f1);
    c2 = fgetc(f2);

    while(c1 != EOF || c2 != EOF)
    {
        if(c1 != c2)
        {
            if(!(iFlag && ((c1 == c2 + 32) || (c2 == c1 + 32))))
            {
                return EXIT_FAILURE;
            }
        }
        c1 = fgetc(f1);
        c2 = fgetc(f2);
    }

    return EXIT_SUCCESS;
}


/**
 * @brief main function, implementing the cmp tool
*/
int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 5)
    {
        fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -i]\n");
        exit(EXIT_FAILURE);
    }
    else if(argc == 3)
    {
        if(!strcmp(argv[1], "-v") || !strcmp(argv[1], "-i") || !strcmp(argv[2], "-v") || !strcmp(argv[2], "-v"))
        {
            fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -i]\n");
            exit(EXIT_FAILURE);
        }
    }

    char verbose = '\0', ignore = '\0';

    if(argc == 4)
    {
        if(!strcmp(argv[3], "-v"))
        {
            verbose = 1;
            ignore = 0;
        }
        else if(!strcmp(argv[3], "-i"))
        {
            verbose = 0;
            ignore = 1;
        }
        else
        {
            fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -i]\n");
            exit(EXIT_FAILURE);
        }
    }
    else if(argc == 5)
    {
        if((!strcmp(argv[3], "-i") && !strcmp(argv[4], "-v")) || (!strcmp(argv[3], "-v") && !strcmp(argv[4], "-i")))
        {
            verbose = 1;
            ignore = 1;
        }
        else
        {
            fprintf(stderr, "Usage: ./cmp <file1> <file2> [optinal: -v] [optional: -i]\n");
            exit(EXIT_FAILURE);
        }
    }

    FILE *f1 = NULL, *f2 = NULL;

    f1 = fopen(argv[1], "r");
    if(f1 == NULL) 
    {
        fprintf(stderr, "general failure\n");
        exit(EXIT_FAILURE);
    }

    f2 = fopen(argv[2], "r");
    if(f2 == NULL) 
    {
        fprintf(stderr, "general failure\n");

        fclose(f1);
        f1 = NULL;

        exit(EXIT_FAILURE);
    }


    int result = 0;
    result = compare_files(f1, f2, ignore);
    
    if(verbose)
    {
        if(!result)
        {
            fprintf(stdout, "equal\n");
        }
        else
        {
            fprintf(stdout, "distinct\n");
        }
    }

    fclose(f1);
    fclose(f2);

    f1 = NULL;
    f2 = NULL;

    return(result);
}