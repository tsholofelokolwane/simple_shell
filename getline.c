#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 100

/**
 * main - my own getline function
 *
 * Return: Always 0
 */

int main(void)
{
	char buffer[MAX_LENGTH];
	int i = 0;
	char c;

	const char *message = "Type something: ";
	int message_length = strlen(message); /* Length of the message */
	const char *message1 = "%d characters were read.\n";
	const char *message2 = "You typed: '%s'\n";
	int length1 = strlen(message1);
	int length2 = strlen(message2);

	const char *newline = "\n";
	int length3 = strlen(newline);

	char length_str[10];
	int length_str_len = 0;
	int temp;

	int j, k;

	write(1, message, message_length);

	while (read(0, &c, 1) > 0 && c != '\n')
	{
		if (i < MAX_LENGTH - 1)
		{
			buffer[i++] = c;
		}
	}

	buffer[i] = '\0';  /* Null-terminate the string */

	write(1, message1, length1);

	/* Manually convert `i` to a string */
	temp = i;

	do {
		length_str[length_str_len++] = temp % 10 + '0';
		temp /= 10;
	} while (temp > 0);

	/* Reverse the string */
	for (j = 0, k = length_str_len - 1; j < k; j++, k--)
	{
		char tmp = length_str[j];

		length_str[j] = length_str[k];
		length_str[k] = tmp;
	}

	write(1, length_str, length_str_len);
	write(1, newline, length3);
	write(1, message2, length2);
	write(1, buffer, i);
	write(1, newline, length3);

	return (0);
}
