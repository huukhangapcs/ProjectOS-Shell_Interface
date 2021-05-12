#ifndef __SHELLBUILTINS___
#define __SHELLBUILTINS___

void getHistory(){
    FILE *fp;
    fp  = fopen ("history.txt", "r");
    char cmd[255];
    int counter = 1;
    while( fgets(cmd, sizeof(cmd), fp)!=NULL ){
        printf("%i %s", counter, cmd);
        counter++;        
    }
    fclose(fp);
}


void process_shell_builtins_cmd(char *args[], int* running){
    if (strcmp(args[0], "exit")==0){
        *running =0;
        return;
    }
    if (strcmp(args[0], "history")==0)
        getHistory();
        
}


#endif