#include "shell.h"
#include <stdlib.h>

/**
 * customAtoi - custom argument to integer function
 * @str: argument string
 *
 * Return: sign * result
 */

int customAtoi(const char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

    /* Check for a negative sign */
	if (str[0] == '-')
	{
		sign = -1;
		i = 1;
	}

	/* Process each digit character */
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
		}
		else
		{
			/* Invalid character encountered, break the loop */
			break;
		}
		i++;
	}

	return (sign * result);
}
