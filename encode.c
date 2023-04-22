#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

#define ENCODE_FUNC "encode"
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
    char *(*encode)(char*) = NULL;
    
    handle = dlopen(codec, RTLD_LAZY);
    if(handle == NULL)
    {
        fprintf(stderr, "general failure\n");
        exit(EXIT_FAILURE);
    }

    encode = dlsym(handle, ENCODE_FUNC);
    if(encode == NULL)
    {
        fprintf(stderr, "general failure\n");
        exit(EXIT_FAILURE);
    }

    char *result = (*encode)(argv[2]);

    fprintf(stdout, "encoded %s\n", result);

    free(result);
    result = NULL;

    return(EXIT_SUCCESS);
}