#ifndef __PREPROCESSING___
#define __PREPROCESSING___
#include <stdio.h>
#include <string.h>
#define MAX_LINE 80 /* The maximum length command */

void get_previous_command(char *cmd){
    strcpy(cmd,"\n");
    char tmp[80]; 
    FILE *fp;
    fp  = fopen("history.txt", "a+");
    while( fgets(tmp, sizeof(tmp), fp)){
        if (!strcmp(tmp,"") || !strcmp(tmp,"\n"))
            break;
        strcpy(cmd, tmp);
    }
    fclose(fp);
}
void init_shell(char* cmd){
    printf("osh>");
    fflush(stdout);
    fgets(cmd, MAX_LINE, stdin);
}
void set_shell_state(char* args[], int*iFlag, int*oFlag, int*std, int* doneBuiltins){
    for(int i = 0; i <(MAX_LINE/2 + 1);i++)
		args[i] = '\0';
    *iFlag = 0;
    *oFlag = 0;
    *std = 0;
    *doneBuiltins = 0;
}
void save_history(char* cmd, char* history){
    if (strcmp(cmd, history) != 0){
            FILE* fp  = fopen ("history.txt", "a+");
            fputs(cmd, fp); // save to history file
            fclose(fp);
    }
}
void process_command(char* cmd, char*args[], int *iFlag, int *oFlag){
    strtok(cmd, "\n");
    char *token = strtok(cmd, " ");
    int i = 0;
    args[i] = token;
    while(token != NULL){
        if (!strcmp(token,"<"))
            *iFlag = i+1;
        else if (!strcmp(token,">"))
            *oFlag = i+1;
        args[i++] = token;
    	token = strtok(NULL, " ");
    }
}

#endif
