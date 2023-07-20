#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INSTRUCTION_LENGTH 200

/* prototype */
void showShellPrompt(void);


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
