#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "functions.h"

int sequential(char *cmd, int mode)
{
    char *cmd[] = tokenify(cmd, 1);
    if (strcmp(cmd[0] == "mode") && mode != 3)
    {
	if (cmd[2] != NULL)
	{
	    	printf("__________ERROR: Too many arguements for Command: Mode__________");
	}
	else		//Mode function is only called if there is a valid number of arguements
	{
           	mode = mode_func(cmd[1], mode);
	}
    }
    if (strcmp(cmd[0] == "exit") && cmd[2] == NULL)
    {
        mode = 3;
    }

    int childrv;
    pid_t pid = fork();
    if (pid < 0)
    {
		perror("Error in the fork"); 
	}
	if (pid == 0)
    {
     /***  Run Child Process  ***/
        if (execv(cmd[0], cmd) < 0) {
            fprintf(stderr, "execv failed: %s\n", strerror(errno));
        }
        printf("\n");
    }
    else
    {
     /***  Wait for Child Process to finish then run Parent ***/
        waitpid(pid, &childrv, 0);
        printf("~~~~~~~~~~~Child Process Finished!~~~~~~~~~~~~\n");
    }

}

int parallel(char *cmds, int mode)
{
	char *commands[] = tokenify(cmd, 1);
	int childrv;

	int i = 0
	for (; i < sizeof(commands + 1) ; i++)
	{
		char *cmd[] = tokenify(cmd, 0);
		if (strcmp(cmd[0] == "mode") && mode != 3)
		{
			if (cmd[2] != NULL)	//Built-in Command should only take one arguement
			{
				printf("_____________ERROR: Too many arguements for Command: Mode____________");
			}
			else		// mode function should not be called if the size of cmd is >2
			{
				mode = mode_func(cmd[1], mode);
			}
		}
		if (strcmp(cmd[0] == "exit") && cmd[2] == NULL)
		{
			mode = 3;
		}

		pid_t pids[i] = fork();
		if (pid < 0)
		{
			perror("Error in the fork"); 
		}
		if (pid == 0)
		{
		 /***  Run Child Process  ***/
			if (execv(cmd[0], cmd) < 0) {
				fprintf(stderr, "execv failed: %s\n", strerror(errno));
			}
			printf("\n");
		}
	}
	for (; i < sizeof(commands + 1) ; i++)
	{
		waitpid(pids[i], &childrv, 0);
	}
}


char *tokenify(const char *str, int switch_value)
{
    switch (switch_value)
    {
	case 0:				//case 0 - tokenifies prompts by separating every semicolon
	    char *sep = ";";
	    break;
        case 1:				//case 1 - tokenifies commands by separating at any white space
	    char *sep = " \n\t";
	    break;
    }
    char *result = (char *)malloc(sizeof(char *) * strlen(str)); 	//malloc's enough space for an array of pointers the size of the string to be parsed
    char *s = strdup(str);
    char *word, *temp;
    int i = 0;
    for (word = strtok_r(s, sep, &temp); word != NULL; word = strtok_r(NULL, sep, &temp))
    {
	int j = 0;
	for (;word[j] != NULL; j++)  	//tests for first instance of a '#'
	{
	    if (isalnum(word[j]) != 0 || (ispunct(word[j]) != 0 && word[j] != '#'))
	    {
		break;
	    }
	    if (word[j] == '#')
	    {
		result[i] = NULL;	//if it finds a '#' the index of result is given a NULL character
		return result;		//and immediately returned
	    }
	}
	result[i] = word;
	i++;
    }
    result[i] = NULL;
    free(s);
    return result;
}


int mode_func(const char *command, int mode_type)
{
	if (command == NULL)
	{
		switch (mode_type)
		{
			case 0:		// 0 - indicates Sequential Mode
			printf = "___________The shell is currently running in Sequential Mode__________\n";
			break;
			case 1:		// 1 - indicates Parallel Mode
			printf = "___________The shell is currently running in Parallel Mode___________\n";
			break;
		}
    }
    if (strcmp(command, "p") == 0 || strcmp(command, "parallel") == 0) //allows for 'p' to act as a shortcut
		mode_type = 1;
    if (strcmp(command, "s") == 0 || strcmp(command, "sequential") == 0) //allows for 's' to act as a shortcut
		mode_type = 0;
    else
    {
		printf = "__________Not a valid arguement for Command: mode__________\n";
    }
    return mode_type;
}
