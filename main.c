#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "preprocessing.h"
#include "io_redirection.h"
#include "shell_builtins.h"
#define MAX_LINE 80 /* The maximum length command */


int main(void)
{
    unsigned long sig = 0;
    char *args[MAX_LINE/2 + 1];
    char cmd[MAX_LINE];
    char cmd_to_process[MAX_LINE];
    int running = 1;
    char previous_cmd[80];
    int iFlag=0, oFlag=0, stdmode=0;
    int doneBuiltins =0;
    get_previous_command(previous_cmd);
    while (running){
        init_shell(cmd);
        set_shell_state(args, &iFlag, &oFlag, &stdmode, &doneBuiltins);
        save_history(cmd, previous_cmd);
        strcpy(previous_cmd, cmd);
        strcpy(cmd_to_process, cmd);
        process_command(cmd_to_process, args, &iFlag, &oFlag);
        set_o_mode(args, oFlag, &stdmode);
        process_shell_builtins_cmd(args, &running, iFlag, &doneBuiltins);
        if (!doneBuiltins){
            printf("helllo\n");
        }
        reset_o_mode(args, oFlag, &stdmode);
    }
    return 0;
}
