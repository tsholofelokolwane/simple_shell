#include "shell.h"
#include <stdio.h>

/**
 * displayPrompt - Display a prompt
 */

void displayPrompt(void)
{
	const char *prompt = ">>> ";
	int length = 0;

	while (prompt[length] != '\0')
	{
		length++;
	}

	write(1, prompt, length);  /* Use write() to print the prompt */
}
