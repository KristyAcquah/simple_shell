#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INSTRUCTION_LENGTH 200

/* Function Prototype */
void showShellPrompt(void);

void runShellinstruction(const char *instruction)
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
