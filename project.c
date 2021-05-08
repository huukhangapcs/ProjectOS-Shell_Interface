#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"
#define MAX_LINE 80 /* The maximum length command */

int main(void)
{
            char *args[MAX_LINE/2 + 1]; /* command line arguments */
            int run = 1; /* flag to determine when to exit program */
            char cmd[MAX_LINE];
            // open and load history
            FILE *fp;
            fp  = fopen ("history.txt", "a+");
            char final_history[255];
            final_history[0] = '\0';
            while( fgets(final_history, sizeof(final_history), fp)!=NULL ){
                // loop to get the final line of history file
            }
            // if (final_history[0] != '\0')
            //     printf("1 : %s\n", final_history);


            while (run) {
                        printf("osh>");
                        fflush(stdout);
                        fgets(cmd, MAX_LINE, stdin);
                        if (strcmp(cmd, final_history) != 0)
                            fputs(cmd, fp);
                        strtok(cmd,"\n");
                        if (strcmp(cmd, "history")==0){
                            getHistory();
                        }
                        else if (strcmp(cmd, "exit")==0)
                            run = 0;
                        else if (strcmp(cmd, "pwd")==0)
                            getWorkingDirectory();
                        else if (strcmp(cmd, "ls")==0)
                            listSubDirectory();
                        /**
                        * After reading user input, the steps are:
                        * (1) fork a child process using fork()
                        * (2) the child process will invoke execvp()
                        * (3) parent will invoke wait() unless command included &
                        */

            }
            fclose(fp);
            return 0;
}
