#include "stshell.h"

int main()
{
	char data[BUFFER_SIZE];
	char* splitData[MAX_LENGHT][MAX_ARGUMENT] = {NULL};
	int pipes[MAX_LENGHT-1][2];
	int lenght = 0;

	// ignoring the ^C
	signal(SIGINT, ignore);

	while(1)
	{
		// get commands from user
	    printf("> ");
	    fgets(data, BUFFER_SIZE, stdin);
	    data[strcspn(data, "\n")] = 0; // replace \n with \0

		// parsering the commands
		spilt_command(splitData, data);
		lenght = numberOfCommands(splitData);

	    /* Is command empty */ 
	    if (splitData[0][0] == NULL){ continue; }

		/* Is exit the stshell*/
		if (strcmp(splitData[0][0], "exit") == 0){ return 0; }

		
		pipe(pipes[0]);
		pipe(pipes[1]);
		for(int i = 0; i < lenght; i++)//commands[i][0] != NULL; i++)
		{
			if(fork()==0)
			{
				// make ^C be a valid option.
				signal(SIGINT, SIG_DFL);
				
				/* prepare the pipes before running the commands */
				handlePipes(pipes, lenght, i);

				/* run the current command */
				execute(splitData[i]);
			}
		}

		close(pipes[0][1]);
		close(pipes[0][0]);
		close(pipes[1][1]);
		close(pipes[1][0]);
		
		for(int i = 0; splitData[i][0] != NULL; i++)
		{
			wait(NULL);
		}
	}
}


void ignore()
{
	printf("\n");
}


int getType(char** command)
{
	int argIndx = 0;
	while(argIndx < MAX_ARGUMENT && command[argIndx] != NULL)
	{
		if(strcmp(command[argIndx], ">") == 0)
		{
			return RIGHT;
		}
		if(strcmp(command[argIndx], ">>") == 0)
		{
			return APPEND;
		}
		argIndx++;
	}
	return NOTHING;
}

void HandleCommands(char** command, int truncORAppend)
{
	int argsNum = numberOfArgs(command);
	char* dstFileName = command[argsNum - 1];
	
	// remove the direct sign and the dst file name from list.
	command[argsNum - 1] = NULL;
	command[argsNum - 2] = NULL;
	
	//change the dst in fd
	int fileFD = open(dstFileName, O_WRONLY | O_CREAT | truncORAppend, S_IRUSR | S_IWUSR);
	close(STDOUT_FILENO);          // close output
	dup2(fileFD, STDOUT_FILENO);   // change output to be the file
	close(fileFD);                 // close the old place of dst file in fd

	execvp(command[0], command);   // run the command
}


/*
Parser string of commands and arguments/flags into
structre of 3d array.
For example: "ls -all | sort | grep txt"
will be [["ls", "-all"], ["sort"], ["grep", "txt"]]
input: pointer to 3d array and string of the full string.
output: void
*/
void spilt_command(char* commands[MAX_LENGHT][MAX_ARGUMENT], char* stream)
{
	// divide to commands between the pipes (|)
	commands[0][0] = strtok(stream, "|");
	for(int i = 1; i < MAX_LENGHT; i++)
	{
		commands[i][0] = strtok(NULL, "|");
	}

	// divide each command to parameters
	for(int i = 0; i < MAX_LENGHT; i++)
	{
		commands[i][0] = strtok(commands[i][0], " ");
		for(int j = 1; j < MAX_ARGUMENT; j++)
		{
			commands[i][j] = strtok(NULL, " ");
		}
	}
}


/*
Select the correct option for running command,
according to the command type (direct or not..)
input: pointer to command.
output: void
*/
void execute(char** command)
{
	int type = getType(command);

	if (type == NOTHING)
		execvp(command[0], command);
	else if (type == RIGHT)
		HandleCommands(command, O_TRUNC);
	else if (type == APPEND)
		HandleCommands(command, O_APPEND);

}


/*
counter the number of arguments in command.
For example: ["ls", "-a"] return 2.
input: pointer to command
output: number as explain abouv.
*/
int numberOfArgs(char** command)
{
	int count = 0;
	for(; count < MAX_ARGUMENT && command[count] != NULL; count++){}
	return count;
}


/*
counter the number of commands
input: pointer to commands 3D array
output: number as explain abouv.
*/
int numberOfCommands(char* commands[MAX_LENGHT][MAX_ARGUMENT])
{
	int i = 0;
	for(; i < MAX_LENGHT && commands[i][0] != NULL; i++);

	return i;
}


/*
Prepre the pipes according to the order of the current command.
input: pipes array, number of commands and number of current command
output: void
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

	close(pipes[0][1]);
	close(pipes[0][0]);
	close(pipes[1][1]);
	close(pipes[1][0]);
}
