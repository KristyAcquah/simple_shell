#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INSTRUCTION_LENGTH 200

/**
 * showShellPrompt - display prompt "(teamwork$) "
 */

void showShellPrompt(void)
{
	printf("(teamwork$) ");
}


/**
 * runShellinstruction -  execute the shell instruction
 * @instruction: the shell instruction executed
 * @args: an array of string
 */
void runShellinstruction(const char *instruction, char *args[])
{

	/* Execute array of strings for arguments */
	pid_t pid = fork();
	int status;

	if (pid == 0)
	{
		execve("/bin/sh", args, NULL);
		perror("execve"); /* execve() only returns if an error occurs */
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		/* The Parent process waits for the child process to terminate */
		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "An error occurred: %s\n", instruction);
		}
	}
}

/**
 * main - the function for the shell
 * @argc: the number of command-line arguments
 * @argv: an array of string containing command-line arguments
 *
 * Return: Always 0
 */

int main(int argc, char *argv[])
{
	char instruction[MAX_INSTRUCTION_LENGTH];
	char *command;
	char *arg;
	char *args[MAX_INSTRUCTION_LENGTH];

	if (argc > 1)
	{
		for (int k = 1; k < argc; k++)
		{
			args[0] = "/bin/sh";
			args[1] = "-c";
			args[2] = argv[k];
			args[3] = NULL;
			runShellinstruction(argv[k], args);
		}
	}

	while (1) /* using while loop to iterate the beginning procss */
	{
		showShellPrompt();

		if (fgets(instruction, MAX_INSTRUCTION_LENGTH, stdin) == NULL)
		{
			break;
		}

		instruction[strcspn(instruction, "\n")] = '\0'; /* Clear trailing newlines */
		if (strcmp(instruction, "exit") == 0)
		{
			break;
		}
		command = strtok(instruction, " ");
		arg = strtok(NULL, " ");

		args[0] = command;
		args[1] = arg;
		args[2] = NULL;
		runShellinstruction(command, args);
	}
	return (0);
}
