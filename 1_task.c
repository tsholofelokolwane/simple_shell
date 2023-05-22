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
	const char *prompt = ">>> ";
	write(1, prompt, strlen(prompt));  /* Use write() to print the prompt */
}

/**
 * executeCommand - Executes given command with arguments
 * @command: array of strings containing command and arguments
 * @environ: environmental variables
 *
 */

void executeCommand(const char **command, const char *environ)
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
		if (execve(command[0], (char *const *)command, (char *const *)environ) == -1)
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
extern char **environ;

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	const char *arguments[MAX_ARGUMENTS + 1];

	int numArgs;
	char *token;

	int wstatus;

	int i;

	const char *newline = "\n";

	for (i = 0; environ[i] != NULL; i++)
	{
		write(1, environ[i], strlen(environ[i])); /* Use write() to print the environment variable */
				write(1, "\n", 1); /* Add a newline character after each printed environment variable */
	}

	while (1)
	{
		displayPrompt();

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			/* EOF condition (Ctrl+D) */
			write(1, "\n", 1);
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
			executeCommand(arguments, environ);
		}
		else
		{
			const char *error_message = "Command not found: ";
			const char *command = arguments[0];

			/* Write the error message */
			write(1, error_message, strlen(error_message));

			/* Write the command */
			write(1, command, strlen(command));

			/* Write a newline character */
			write(1, newline, 1);
		}

		/* Built-in: Exit */
		if (strcmp(EXITCMD, arguments[0]) == 0)
			return (0);

		/* Wait for program to finish and exit status */
		wait(&wstatus);

		if (WIFEXITED(wstatus))
		{
			int exit_status = WEXITSTATUS(wstatus);
			char exit_status_str[10];
			int len = snprintf(exit_status_str, sizeof(exit_status_str), "<%d>", exit_status);
			write(1, exit_status_str, len);
		}

	}

	return (0);
}
