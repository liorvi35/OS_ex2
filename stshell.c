#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define EXIT_MESSAGE "exit"
#define SPACE " "

void handler(int);


void handler(int signal) { return; }

int main()
{
    signal(SIGINT, handler); // disable ^C

    char command[BUFSIZ] = {0};
    char *argv[BUFSIZ] = {0};
    char *token = NULL;

    int i = 0;

    while (1)
    {
        fscanf(stdin, "%s", command);

        if(!strcmp(command, EXIT_MESSAGE))
        {
            exit(EXIT_SUCCESS);
        }

        if(!strcmp(command, ""))
        {
            continue;
        }

        i = 0;
        token = strtok(command, SPACE);
        while(token != NULL)
        {
            argv[i] = token;
            token = strtok(NULL, SPACE);
            i++;
        }
        argv[i] = NULL;
    
        if(fork() == 0)
		{
			execvp(argv[0], argv);
			wait(NULL);
		}
    }
    
}
