#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_10

void prompt(char **argv)
{
	char *string = NULL;
	int i, status;
	size_t num = 0;
	ssize_t char_num;
	pid_t child_pid = fork();

	while (i == 1)
	{
		if (isatty(STDIN_FILENO))
		printf("teamwork$ ");

		char_num = getline(&string, &num, stdin);
		if (char_num == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}

		argv[i] = strtok(string, " ");
		while (argv[i] != NULL && i < MAX_COMMAND_10 - 1)
		{
			i++;
			argv[i] = strtok(NULL, " ");

			if (i > 0)
			argv[i] = NULL;
		}

		if (child_pid == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execvp(argv[0], argv) == -1)
				printf("%s: No such file in directory\n", argv[0]);

			free(string);
			exit(EXIT_FAILURE);

		}

		wait(&status);
	}
	free(string);
}
