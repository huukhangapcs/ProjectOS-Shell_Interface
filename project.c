#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"
#define MAX_LINE 80 /* The maximum length command */
int iDirection = 0;
int oDirection = 0;
char *iDirectionFile="\0";
char* oDirectionFile = "\0";

void resetState(char *args[]){
    int iDirection = 0;
    int oDirection = 0;
    char *iDirectionFile="\0";
    char* oDirectionFile = "\0";
    for(int i = 0; i <(MAX_LINE/2 + 1);i++)
		args[i] = '\0';
}
void splitToken(char* cmd, char* args[]){
    resetState(args);
    char *token = strtok(cmd, " ");
    int i = 0;
    args[i] = token;
    while(token != NULL){
        if (!strcmp(token,">")){
            oDirection = 1;
            args[i++] = token;
    	    token = strtok(NULL, " ");
            oDirectionFile = token;
        } else if (!strcmp(token,"<")){
            iDirection = 1;
            args[i++] = token;
    	    token = strtok(NULL, " ");
            iDirectionFile = token;
        }
        else{
            args[i++] = token;
    	    token = strtok(NULL, " ");
        }
    	
    }
}


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
            while (run) {
                        printf("osh>");
                        fflush(stdout);
                        fgets(cmd, MAX_LINE, stdin);
                        if (strcmp(cmd, final_history) != 0)
                            fputs(cmd, fp); // save to history file
                        strtok(cmd,"\n");

                        if (strcmp(cmd,"!!")==0){
                            if (strcmp(final_history,"\0")==0){
                                printf("No command in history\n");
                                continue;
                            }
                            else{
                                printf("Recently entered command: %s\n",final_history);
                                strcpy(cmd, final_history);
                            }
                        }
                        
                        splitToken(cmd, args);
                        if (strcmp(args[0], "exit")==0)
                            break;
                        //handleIR OR
                        int stdin = 0;
                        int stdout = 0;// use for IO REDIRECTION       
                        if (iDirection)
                            stdin = handleIR(iDirectionFile);
                        else if (oDirection){ // start output REDIRECTION
                            stdout = handleOR(oDirectionFile);
                        }
                            


                        if (strcmp(args[0], "history")==0){
                            getHistory();
                        }

                        else if (strcmp(args[0], "pwd")==0)
                            getWorkingDirectory();
                        else if (strcmp(args[0], "ls")==0)
                            listSubDirectory();
                        else if (strcmp(args[0], "cd")==0){
                            if (args[1] != NULL){
                                if (chdir(args[1])!=0){
                                    perror(args[1]);
                                }
                            }
                        }
                        else if (strcmp(args[0], "sort")==0){
                            if (args[1] != NULL){
                                sortFile(args[1],args[2]);
                            }
                        /**
                        * After reading user input, the steps are:
                        * (1) fork a child process using fork()
                        * (2) the child process will invoke execvp()
                        * (3) parent will invoke wait() unless command included &
                        */
                       if (iDirection)
                            stopOR(stdin); //stop Output redirection
                       else if (oDirection)
                            stopIR(stdout); // stop Input redirection
                       strcpy(final_history, cmd);
                        }

            }
            fclose(fp);
            return 0;
}
