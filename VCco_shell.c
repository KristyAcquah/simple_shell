#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INSTRUCTION_LENGTH 200

/* Function Prototype */
void showShellPrompt(void);
void processInstructions(void);
void tokenizeInstruction(const char *instruction, char *args[]);


/**
 * showShellPrompt - Displays shell prompt
 */
void showShellPrompt(void)
{
    printf("(teamwork$) ");
}

/**
 * processInstructions - Processes instructions for interactive mode
 */
void processInstructions()
{
    char instruction[MAX_INSTRUCTION_LENGTH];
    char *args[MAX_INSTRUCTION_LENGTH];                                                                                   while (1) /* using while loop to iterate the beginning process */
    {                                                              showShellPrompt(); /* Displays the prompt */

        if (fgets(instruction, MAX_INSTRUCTION_LENGTH, stdin) == NULL)
        {
            break; /* Exit if Ctrl+D is pressed */
        }

        instruction[strcspn(instruction, "\n")] = '\0'; /* Clear newlines */

        if (strcmp(instruction, "exit") == 0)
        {
            break; /* Exit shell if the instruction is "exit" */
        }

        tokenizeInstruction(instruction, args);
    }
}

/**
 * tokenizeInstruction - Tokenizes the instruction into command and argument
 * @instruction: the instruction to tokenize
 * @args: array of strings to store command and argument
 */
void tokenizeInstruction(const char *instruction, char *args[])
{
    char instructionCopy[MAX_INSTRUCTION_LENGTH];
    char *command;
    char *arg;

    strncpy(instructionCopy, instruction, MAX_INSTRUCTION_LENGTH);
    instructionCopy[MAX_INSTRUCTION_LENGTH - 1] = '\0';

    command = strtok(instructionCopy, " ");
    arg = strtok(NULL, " ");

    args[0] = command;
    args[1] = arg;
    args[2] = NULL;
}    
