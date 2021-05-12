#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "preprocessing.h"
#include "io_redirection.h"
#include "shell_builtins.h"
#define MAX_LINE 80 /* The maximum length command */


int main(void)
{
    char *args[MAX_LINE/2 + 1];
    char cmd[MAX_LINE];
    int running = 1;
    char previous_cmd[80];
    int iFlag=0, oFlag=0, out=0, in=0;
    get_previous_command(previous_cmd);
    while (running){
        init_shell(cmd);
        set_shell_state(args, &iFlag, &oFlag, &out, &in);
        save_history(cmd, previous_cmd);
        process_command(cmd, args, &iFlag, &oFlag);
        set_io_mode(args, iFlag, oFlag, &out, &in);
        process_shell_builtins_cmd(args, &running);
        reset_io_mode(args, iFlag, oFlag, &out, &in);
    }
    return 0;
}