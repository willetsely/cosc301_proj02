#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "sequential.h"
#include "tokenify.h"
#include "mode.h"

int sequential(char *cmd, int mode)
{
    char *cmd[] = tokenify(cmd, 1);
    if (cmd[0] == "mode" && mode != 3 && cmd[2] == NULL)
    {
        mode = mode(cmd[1], mode);
    }
    if (cmd[0] == "exit" && cmd[2] == NULL)
    {
        mode = 3;
    }

    int childrv;
    pid_t pid = fork();
    if (pid == 0)
    {
     /***  Run Child Process  ***/
        if (execv(cmd[0], cmd) < 0) {
            fprintf(stderr, "execv failed: %s\n", strerror(errno));
        }
        printf("\n");
    } 
    else if (pid > 0)
    {
     /***  Wait for Child Process to finish then run Parent ***/
        waitpid(pid, &childrv, 0);
        printf("~~~~~~~~~~~Child Process Finished!~~~~~~~~~~~~\n");
    }

}

