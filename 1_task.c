#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * displayPrompt - Display a prompt
 */

void displayPrompt(void)
{
	printf(">>> ");
}

/**
 * executeCommand - Executes given command
 * @command: command line
 */

void executeCommand(const char *command)
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
		execlp(command, command, NULL);

		/* If exec fails, print error and exit child process */
		perror("Command execution failed");
		exit(EXIT_FAILURE);
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

		executeCommand(command);
	}

	return (0);
}
