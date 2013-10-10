#include <stdio.h>
#include <stdlib.h>
#include <mode.h>

int  mode_funct(const char *command, int mode_type)
{
   if (command == NULL)
   {
	switch (mode_type)
	{
	    case 0:
		printf = "___________The shell is currently running in Sequential Mode__________\n";
		break;
	    case 1:
		printf = "___________The shell is currently running in Parallel Mode___________\n";
		break;
	}
    }
    if (strcmp(command, "p") == 0 || strcmp(command, "parallel") == 0)
	mode_type = 1;
    if (strcmp(command, "s") == 0 || strcmp(command, "sequential") == 0)
	mode_type = 0;
    else
    {
	printf = "__________Not a valid arguement for Command: mode__________\n";
    }
    return mode_type;
}
	
	
