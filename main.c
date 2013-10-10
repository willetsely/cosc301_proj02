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
#include <signal.h>
#include "functions.h"


int main(int argc, char **argv)
{
	const char * prompt = ">>>";
	int mode = 0;	//mode = 0 for sequential, 1 for parallel, 3 to exit
    char input [1024];    

	while(fgets(input, 1024, stdin) != NULL)  //keep looping while there is still input
    	{
		printf("%s",prompt);
		fflush(stdout);	

		int comcount = 1; //start at 1 because there is one more command than there are semicolons
		int i = 0;
		for(;input[i] != '\0'; i++)  //this loop counts the number of commands
		{
			if(input[i] == ';')
				comcount++;
		}

		char ** commands;
		commands = tokenify(input, 0); //the 0 indicates prompt, ie split on semicolons
        if(strcmp(commands[0],"\n") == 0) //check for an empty line
            continue;        

		if(mode == 0) //start sequential execution
		{
			int j = 0;
			for(;j < comcount; j++)
			{
		        mode = sequential(commands[j], mode); //mode takes the value because sequential returns
                                                      // what mode should be for the next command line
			}
		}

		else if(mode == 1) //start parallel execution
			//parallel execution function

        if(mode == 3) //if an exit command has been issued, return
            return 0;
	}

    return 0;
}

