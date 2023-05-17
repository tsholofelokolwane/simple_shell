#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define EXITCMD "exit"

/**
 * displayPrompt - Display a prompt
 */

void displayPrompt(void)
{
	printf(">>> ");
}

/**
 * executeCommand - Executes given command with arguments
 * @command: array of strings containing command and arguments
 */

void executeCommand(const char *command[])
{
	pid_t pid;

	pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}

	else if (pid == 0)
	{
		/* Child process */
		if (execvp(command[0], (char *const *)command) == -1)
		{
			/* If exec fails, print error and exit child process */
			perror("Command execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);
	}
}

/**
 * main - UNIX command line interpreter
 *
 * Return: Always 0
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	const char *arguments[MAX_ARGUMENTS + 1];

	int numArgs;
	char *token;

	int wstatus;

	while (1)
	{
		displayPrompt();

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			/* EOF condition (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove trailing newline character */
		command[strcspn(command, "\n")] = '\0';

		/* Tokenize command and arguments */
		numArgs = 0;
		token = strtok(command, " ");

		while (token != NULL && numArgs < MAX_ARGUMENTS - 1)
		{
			arguments[numArgs++] = token;
			token = strtok(NULL, " ");
		}
		arguments[numArgs] = NULL;

		/* Check if the command exists and is accessible */
		if (access(arguments[0], X_OK) == 0)
		{
			executeCommand(arguments);
		}
		else
		{
			printf("Command not found: %s\n", arguments[0]);
		}

		/* Built-in: Exit */
		if (strcmp(EXITCMD, arguments[0]) == 0)
			return (0);

		/* Wait for program to finish and exit status */
		wait(&wstatus);

		if (WIFEXITED(wstatus))
			printf("<%d>", WEXITSTATUS(wstatus));
	}

	return (0);
}
