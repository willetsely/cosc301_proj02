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
	int mode = 0;	//mode = 0 for sequential, 1 for parallel
	int modechange = 0; //modechange tracks if a change in mode needs to be made at the end of the command line
	while(moreinput)
    	{
		printf("%s",prompt);
		//fflush
		//get input
		int comcount = 1; 	//start at 1 because there is one more command than there are semicolons
		//loop through input and count ;s
		char * argc[count] = tokenify(count, 1) //the 1 indicates prompt, ie split on semicolons
		for(size of argc)
			if(mode == 0)
				//sequential execution function
			if(mode == 1)
				//parallel execution function
			//both executions should return an int for modechange
	}

    return 0;
}

