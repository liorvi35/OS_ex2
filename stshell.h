#ifndef STSHELL_H
#define STSHELL_H

#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define MAX_LENGHT 3
#define MAX_ARGUMENT 10

#define NOTHING 0
#define RIGHT 1
#define APPEND 2


void ignore();
int getType(char**);
void HandleCommands(char**, int);
void spilt_command(char* [MAX_LENGHT][MAX_ARGUMENT], char*);
void execute(char** );
int numberOfArgs(char**);
int numberOfCommands(char* [MAX_LENGHT][MAX_ARGUMENT]);
void handlePipes(int [MAX_LENGHT - 1][2], int, int );

#endif
