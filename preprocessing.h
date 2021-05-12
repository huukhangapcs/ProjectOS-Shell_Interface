#ifndef __PREPROCESSING___
#define __PREPROCESSING___
#include <stdio.h>
#include <string.h>
#define MAX_LINE 80 /* The maximum length command */

void get_previous_command(char *cmd){
    strcpy(cmd,"\n");
    FILE *fp;
    fp  = fopen("history.txt", "a+");
    while( fgets(cmd, sizeof(cmd), fp)!=NULL ){}
    fclose(fp);
}
void init_shell(char* cmd){
    printf("osh>");
    fflush(stdout);
    fgets(cmd, MAX_LINE, stdin);
}
void set_shell_state(char* args[], int*iFlag, int*oFlag, int*stdin, int*stdout){
    for(int i = 0; i <(MAX_LINE/2 + 1);i++)
		args[i] = '\0';
    *iFlag = 0;
    *oFlag = 0;
    *stdin = 0;
    *stdout = 0;
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
        i++;
        if (!strcmp(token,"<"))
            *iFlag = i;
        else if (!strcmp(token,">"))
            *oFlag = i;
        args[i] = token;
    	token = strtok(NULL, " ");
    }
}

#endif