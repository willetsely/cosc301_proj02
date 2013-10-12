// Willets Ely, Daniel Drucker, Markos Georges
// 10/8/2013
// Cosc 301

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <errno.h>
#include <signal.h>

int sequential(char *, int);
int parallel(char *, int);
int mode_func(const char *, int);
char **tokenify(const char *, int);

int main(int argc, char **argv)
{
	const char * prompt = ">>>";
	int mode = 0;	//mode = 0 for sequential, 1 for parallel, 3 to exit
    char input [1024];     

    printf("%s", prompt);
    fflush(stdout);

	while(fgets(input, 1024, stdin) != NULL)  //keep looping while there is still input
    	{	

		int comcount = 1; //start at 1 because there is one more command than there are semicolons
		int i = 0;
		for(;input[i] != '\0'; i++)  //this loop counts the number of commands
		{
			if(input[i] == ';')
				comcount++;
            if(input[i] == '\n')
            {
                input[i] = '\0';
                break;
            }
		}
        char * goodinput = strdup(input);

		char ** commands = (char **)malloc(sizeof(char**));
		commands = tokenify(input, 0); //the 0 indicates prompt, ie split on semicolons
        if(strcmp(commands[0],"\n") == 0) //check for an empty line
            continue;        

		if(mode == 0) //start sequential execution
		{
			int j = 0;
			for(;j < comcount; j++)
			{
		        mode = sequential(commands[j], mode); //mode takes the value because sequential
                                                // returns what mode should be for the next command line
			}
		}

		else if(mode == 1){ //start parallel execution
			mode = parallel(goodinput, mode);
        }
        if(mode == 3) //if an exit command has been issued, return
            return 0;

        printf("%s",prompt);
        fflush(stdout);
	}
    
    return 0;
}

int sequential(char *line, int mode)
{
    
    char **cmd;
    cmd = tokenify(line, 1);
    if (strcmp(cmd[0], "mode") == 0 && mode != 3)
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
    if (strcmp(cmd[0], "exit") == 0 && cmd[1] == NULL)
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
    return mode;
}

int parallel(char *line, int mode)
{
    char **commands;
    commands = tokenify(line, 0);   //break the line into commands by separating at ;s
	int childrv;
    pid_t *pids;

	int i = 0;
	while(commands[i] != NULL)
	{
		char **cmd;
        cmd = tokenify(commands[i], 1); //cmd = the array of strings that make up each command
		if (strcmp(cmd[0], "mode") == 0 && mode != 3)
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
		if (strcmp(cmd[0], "exit") == 0 && cmd[1] == NULL)
		{
			mode = 3;
		}

		pids[i] = fork();
		if (pids[i] < 0)
		{
			perror("Error in the fork"); 
		}
		if (pids[i] == 0)
		{
		 /***  Run Child Process  ***/
			if (execv(cmd[0], cmd) < 0) {
				fprintf(stderr, "execv failed: %s\n", strerror(errno));
			}
			printf("\n");
		}
        i++;
    }
    int j = 0;
    while(commands[j] != NULL)
	{
		waitpid(pids[j], &childrv, 0);
        j++;
	}
    return mode;
}


char **tokenify(const char *str, int switch_value)
{
	char *sep;
	if (switch_value == 0)		//case 0 - tokenifies prompts by separating every semicolon
	    	sep = ";";
    	if (switch_value == 1)		//case 1 - tokenifies commands by separating at any white space
	    	sep = " \n\t";
    	char **result = (char **)malloc(sizeof(char **));
    	char *s = strdup(str);
	char *comment = "#";
	char *comment_check = strtok(s, comment); 	//nothing after the '#' is considered
    	char *word, *temp;
    	int i = 0;
    	for (word = strtok_r(comment_check, sep, &temp); word != NULL; word = strtok_r(NULL, sep, &temp))
    	{
		result[i] = word;
		i++;
    	}
    	result[i] = NULL;
    	free(s);
	free(comment_check);
    	return result;
}


int mode_func(const char *command, int mode_type)
{
	if (command == NULL)
	{
		if (mode_type == 0)		// 0 - indicates Sequential Mode
			printf("___________The shell is currently running in Sequential Mode__________\n");
		if (mode_type == 1)		// 1 - indicates Parallel Mode
			printf("___________The shell is currently running in Parallel Mode___________\n");
    	}
    	if (strcmp(command, "p") == 0 || strcmp(command, "parallel") == 0) //allows for 'p' to act as a shortcut
		mode_type = 1;
    	if (strcmp(command, "s") == 0 || strcmp(command, "sequential") == 0) //allows for 's' to act as a shortcut
		mode_type = 0;
    	else
    	{
		printf("__________Not a valid arguement for Command: mode__________\n");
    	}
    	return mode_type;
}

