/**
 * @brief Assignment 2, `Operating Systems` course at Ariel University
 * 
 * this file contains implementation for basic shell
 * 
 * @version 1
 * @since 28/04/2023
 * @authors Lior Vinman & Yoad Tamar
*/


#include "stshell.h"


/**
 * @brief this function is the signal-caller function,
 * used to interrupt the CTRL+C signal, do nothing (so CTRL+C do nothing)
*/
void ignore()
{
	fprintf(stdout, "\n");
	return;
}


/**
 * @brief Determines the type of command based on its arguments
 * @param args An array of command arguments
 * @return An integer representing the type of command
 */
int getType(char** command)
{
	int argIndx = 0;
	while(argIndx < MAX_ARGUMENT && command[argIndx] != NULL)
	{
		if(strcmp(command[argIndx], WRITE_REDIRECTOR) == 0)
		{
			return WRITE;
		}
		if(strcmp(command[argIndx], APPEND_REDIRECTOR) == 0)
		{
			return APPEND;
		}
		argIndx++;
	}
	return NOTHING;
}


/**
 * @brief this function handles executing a command with output redirection to a file.
 * @param command An array of command arguments, with the last argument being the destination file name.
 * @param truncORAppend An integer value indicating whether the output should be truncated or appended to the destination file.
*/
void HandleCommands(char** command, int truncORAppend)
{
	int argsNum = numberOfArgs(command);
	char* dstFileName = command[argsNum - 1];
	
	command[argsNum - 1] = NULL;
	command[argsNum - 2] = NULL;
	
	int fileFD = open(dstFileName, O_WRONLY | O_CREAT | truncORAppend, S_IRUSR | S_IWUSR);
	close(STDOUT_FILENO); 
	dup2(fileFD, STDOUT_FILENO);
	close(fileFD);

	execvp(command[0], command); 
}

/**
 * @brief This function takes a command string and splits it into an array of arrays of commands.
 * @param commands A 2D char array representing the commands and their arguments. This array will be modified by the function.
 * @param stream The command string to be split.
*/
void spilt_command(char* commands[MAX_LENGHT][MAX_ARGUMENT], char* stream)
{
	commands[0][0] = strtok(stream, PIPE);
	for(int i = 1; i < MAX_LENGHT; i++)
	{
		commands[i][0] = strtok(NULL, PIPE);
	}

	for(int i = 0; i < MAX_LENGHT; i++)
	{
		commands[i][0] = strtok(commands[i][0], SPACE);
		for(int j = 1; j < MAX_ARGUMENT; j++)
		{
			commands[i][j] = strtok(NULL, SPACE);
		}
	}
}

/**
 * @brief This function executes a given command by calling the appropriate system call.
 * @param command A null-terminated array of null-terminated strings representing the command and its arguments.
*/
void execute(char** command)
{
	int type = getType(command);
	if (type == NOTHING)
	{
		execvp(command[0], command);
	}	
	else if (type == WRITE)
	{
		HandleCommands(command, O_TRUNC);
	}	
	else if (type == APPEND)
	{
		HandleCommands(command, O_APPEND);
	}
}


/**
 * @brief This function counts the number of arguments in a given command.
 * @param command A null-terminated array of null-terminated strings representing the command and its arguments.
 * @return The number of arguments in the command.
*/
int numberOfArgs(char** command)
{
	int count = 0;
	for(; count < MAX_ARGUMENT && command[count] != NULL; count++){}
	return count;
}


/**
 * @brief This function counts the number of commands in a given array of arrays of commands.
 * @param commands A 2D char array representing the commands and their arguments.
 * @return The number of commands in the array.
*/
int numberOfCommands(char* commands[MAX_LENGHT][MAX_ARGUMENT])
{
	int i = 0;
	for(; i < MAX_LENGHT && commands[i][0] != NULL; i++);

	return i;
}


/**
 * @brief This function handles the redirection of input and output for commands in a pipeline.
 * @param pipes A 2D array of file descriptors for the pipeline.
 * @param numberOfCommands The total number of commands in the pipeline.
 * @param commandNo The position of the current command in the pipeline.
*/
void handlePipes(int pipes[MAX_LENGHT - 1][2], int numberOfCommands, int commandNo)
{
	if(commandNo == 0 && numberOfCommands > 1)
	{
		close(STDOUT_FILENO);
		dup2(pipes[0][1], STDOUT_FILENO);
	}
	else if(commandNo == 1)
	{
		close(STDIN_FILENO);
		dup2(pipes[0][0], STDIN_FILENO);

		if(numberOfCommands > 2)
		{
			close(STDOUT_FILENO);
			dup2(pipes[1][1], STDOUT_FILENO);
		}
	}
	else if(commandNo == 2)
	{
		close(STDIN_FILENO);
		dup2(pipes[1][0], STDIN_FILENO);
	}
	
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
}


/**
 * @brief main function, implementing basic shell 
*/
int main(int argc, char **argv)
{
	char data[BUFFER_SIZE] = {0};
	char* splitData[MAX_LENGHT][MAX_ARGUMENT] = {0};
	int pipes[MAX_LENGHT-1][2] = {0};
	int lenght = 0, i = 0;

	signal(SIGINT, ignore);

	while(1)
	{
	    fprintf(stdout, "%s ", WRITE_REDIRECTOR);

	    fgets(data, BUFFER_SIZE, stdin);
	    data[strcspn(data, "\n")] = 0;

		spilt_command(splitData, data);
		lenght = numberOfCommands(splitData);

	    if(splitData[0][0] == NULL)
		{
			continue; 
		}
		else if(!strcmp(splitData[0][0], "exit"))
		{
			return 0; 
		}
		else
		{
			pipe(pipes[0]);
			pipe(pipes[1]);

			i = 0;
			for(i = 0; i < lenght; i++)
			{
				if(fork() == 0)
				{
					signal(SIGINT, SIG_DFL);
					handlePipes(pipes, lenght, i);
					execute(splitData[i]);
				}
			}

			close(pipes[0][0]);
			close(pipes[0][1]);
			close(pipes[1][0]);
			close(pipes[1][1]);

			i = 0;
			for(i = 0; splitData[i][0] != NULL; i++)
			{
				wait(NULL);
			}
		}
	}
}
