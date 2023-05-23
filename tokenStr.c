#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * tokenString - tokenize string
 * @command: command string
 * @arguments: arguments string
 */

void tokenString(char command[], char arguments[])
{
	int i, j;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == arguments[0])
		{
			command[i] = '\0';
		}
	}

	for (j = 0; j < i; j++)
	{
		if (command[j] != '\0')
		{
			write(1, &command[j], 1);
		}
		else
		{
			write(1, "\n", 1);
		}
	}
}

/**
 * tokenStringMain - tokenizes command and arguments string
 *
 * Return: Always 0
 */

int tokenStringMain(void)
{
	char command[100];
	char arguments[100];

	write(1, "Enter command: ", 15);
	read(0, command, sizeof(command) - 1);
	command[strcspn(command, "\n")] = '\0';

	write(1, "Enter arguments: ", 17);
	read(0, arguments, sizeof(arguments) - 1);
	arguments[strcspn(arguments, "\n")] = '\0';

	tokenString(command, arguments);

	return (0);
}
