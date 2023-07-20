#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INSTRUCTION_LENGTH 200

/* Function Prototype */
void showShellPrompt(void);
void runShellinstruction(const char *instruction);

{
	pid_t pid = fork(); /* creating a new child process using fork */

	if (pid == 0) /* Result when it is in the child process */
	{
		/* Child process using execve to execute the instruction from user */
		char *const args[] = {"/bin/sh", "-c", NULL};

		execve("/bin/sh", args, NULL);
		perror("execve"); /* execve() only returns if an error occurs */
		exit(EXIT_FAILURE);
	}
	else if (pid == -1) /* Result if there was an error during compilation */
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0) /* Result if it is in the parent process */
	{
		/* The Parent process waits for the child process to terminate */
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			/* Checking if the child process exited normally or not */
			fprintf(stderr, "Error occurred while running code: %s\n", instruction);
		}
	}
}

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments in the code
 * @argv: Array of command-line argument strings
 * Return: 0 when program is successful or 1 on failure
 */
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		/* If there are arguments provided, enters Non-interactive mode */
		int k;
		
		for (k = 1; k < argc; k++)
		{
			runShellinstruction(argv[k]);
		}
	}	
	else
	{
		while (1) /* using while loop to iterate the beginning process */
		{
			char instruction[MAX_INSTRUCTION_LENGTH];
			showShellPrompt(); /* Displays the prompt */

			if (fgets(instruction, MAX_INSTRUCTION_LENGTH, stdin) == NULL)
			{
				break; /* Exit if Ctrl+D is pressed */
			}

			instruction[strcspn(instruction, "\n")] = '\0'; /* Clear newlines */

			if (strcmp(instruction, "exit") == 0)
			{
				break; /* Exit shell if the instruction is "exit" */
			}
			runShellinstruction(instruction); /* Execute instruction */
		}
	}

	return (0);
}
