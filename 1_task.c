#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define EXITCMD "exit"

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

	int i;

	const char *newline = "\n";

	ssize_t bytesRead;

	for (i = 0; environ[i] != NULL; i++)
	{
		write(1, environ[i], _strlen(environ[i])); /* Use write() to print the environment variable */
				write(1, "\n", 1); /* Add a newline character after each printed environment variable */
	}

	while (1)
	{
		displayPrompt();

		bytesRead = read(0, command, sizeof(command));

		if (bytesRead == -1)
		{
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}

		else if (bytesRead == 0)
		{
			/* EOF condition (Ctrl+D)*/
			write(1, "\n", 1);
			break;

		}

		/* Remove trailing newline character */
		command[bytesRead - 1] = '\0';

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
			executeCommand(arguments, environ);
		}
		else
		{
			const char *error_message = "Command not found: ";
			const char *command = arguments[0];

			/* Write the error message */
			write(1, error_message, _strlen(error_message));

			/* Write the command */
			write(1, command, _strlen(command));

			/* Write a newline character */
			write(1, newline, 1);
		}

		/* Built-in: Exit */
		if (_strcmp(EXITCMD, arguments[0]) == 0)
		{
			int status = 0;

			/* Check if an argument is provided */
			if (numArgs > 1)
			{
				status = customAtoi(arguments[1]); /* Convert argument to an integer */
			}

			exit(status); /* Use the exit status to exit the shell */
		}

		/* Wait for program to finish and exit status */
		wait(&wstatus);

		if (WIFEXITED(wstatus))
		{
			int status = WEXITSTATUS(wstatus);
			char exit_status_str[10];
			int len = snprintf(exit_status_str, sizeof(exit_status_str), "<%d>", status);

			write(1, exit_status_str, len);
		}

	}

	return (0);
}
