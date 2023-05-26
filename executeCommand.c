#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXITCMD "exit"

/**
 * executeCommand - Executes given command with arguments
 * @command: array of strings containing command and arguments
 * @environ: environmental variables
 *
 */

void executeCommand(const char **command, char **environ)
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
