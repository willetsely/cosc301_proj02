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


int main(int argc, char **argv)
{
	const char * prompt = ">>>";
	int moreinput = 1;
	int mode = 0;	//mode = 0 for sequential, 1 for parallel, 3 to exit

	while(moreinput)
    	{
		printf("%s",prompt);
		//fflush
		char input [1024];	
		fgets(input, 1024, stdin); //get input

		int comcount = 1; //start at 1 because there is one more command than there are semicolons
		int i = 0;
		for(;input[i] != '\0'; i++)  //this loop counts the number of commands
		{
			if(input[i] == ';')
				comcount++;
		}

		char * argc[comcount] = tokenify(input, 0)//the 0 indicates prompt, ie split on semicolons

		if(mode == 0) //start sequential execution
		{
			int j = 0;
			for(;j < comcount; j++)
			{
		        mode = sequential(*argc[j], mode) //mode is set equal because sequential returns what mode should be for the next command line
			}
		}

		else if(mode == 1) //start parallel execution
			//parallel execution function

        if(mode == 3) //if an exit command has been issued, return
            return 0;
	}

    return 0;
}

