#include "VC_shell.h"

/**
 * prompt - function that displays for user to input
 *
 * Return: 0
 */

void prompt(void)
{
	char *line, **args;
	pid_t pid;
	int status = 1;

	do {
		printf("cisfun$ ");
		line = read_line();
		args = parse_line(line);
		pid = fork();

		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Error");
			}
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Error");
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
		}

		free(line);
		free(args);

	} while (status != -1);
}

/**
 * read_line - reads a line of input
 *
 * Return: line input
 */

char *read_line(void)
{
	char *line = NULL;
	size_t r = 0;

	getline(&line, &r, stdin);

	return (line);
}

/**
 * parse_line - parses a line of input
 * @line: line entered by user
 *
 * Return: line token
 */

char **parse_line(char *line)
{
	int r = 64, a = 0;
	char *token, **tokens = malloc(r * sizeof(char *));

	if (!tokens)
	{
		fprintf(stderr, "error allocated\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \n");
	while (token != NULL)
	{
		tokens[a] = token;
		a++;

		if (a >= r)
		{
			r = r + 64;
			tokens = realloc(tokens, r * sizeof(char *));

			if (!tokens)
			{
				fprintf(stderr, "error allocated\n");
				exit(EXIT_FAILURE);
			}

		}
		token = strtok(NULL, " \n");
	}

	tokens[a] = NULL;

	return (tokens);
}
