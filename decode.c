#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

#define DECODE_FUNC "decode"
#define CODEC_A "./libcodecA.so"
#define CODEC_B "./libcodecB.so"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: ./encode <codec> <message>\n");
        exit(EXIT_FAILURE);
    }

    char* codec = NULL;

    if(!strcmp(argv[1], "codecA"))
    {
        codec = CODEC_A;
    }
    else if(!strcmp(argv[1], "codecB"))
    {
        codec = CODEC_B;
    }
    else
    {
        fprintf(stderr, "Usage: ./encode <codec> <message>\n");
        exit(EXIT_FAILURE);
    }
    
    void *handle = NULL;
    char *(*decode)(char*) = NULL;
    
    handle = dlopen(codec, RTLD_LAZY);
    if(handle == NULL)
    {
        fprintf(stderr, "general failure\n");
        exit(EXIT_FAILURE);
    }

    decode = dlsym(handle, DECODE_FUNC);
    if(decode == NULL)
    {
        fprintf(stderr, "general failure\n");
        exit(EXIT_FAILURE);
    }

    char *result = (*decode)(argv[2]);

    fprintf(stdout, "decoded %s\n", result);

    free(result);
    result = NULL;

    return(EXIT_SUCCESS);
}