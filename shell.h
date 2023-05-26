#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>

extern char **environ;
int customAtoi(const char *str);
void executeCommand(const char **command, char **environ);
void displayPrompt();
size_t _strlen(const char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

#endif
