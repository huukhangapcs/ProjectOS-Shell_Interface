#ifndef __SHELLBUILTINS___
#define __SHELLBUILTINS___
#include <dirent.h>
#include "file_sorting.h"
void getHistory(){
    char line[80];
    int cnt = 0;
    FILE *file = fopen("history.txt", "r");
    if (file == NULL)
    {
        perror("history.txt");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line,"") && strcmp(line,"\n") && cnt <1000){
            cnt++;
            printf("%i %s", cnt, line);
        }
        else break;
    }
    fclose(file);
}
void getWorkingDirectory(){
    char cwd[255];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%s\n", cwd);
    } else {
       perror("getcwd() error");
   }
}
void listSubDirectory(){
    char cwd[255];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
       perror("getcwd() error");
       return;
    }
    DIR *dir = opendir(cwd);
    struct dirent *file;
    char *fileName;
    while((file = readdir(dir)) != NULL)
    {
        fileName = file->d_name;
        if (strcmp(fileName,".")!=0 && strcmp(fileName,"..")!=0)
            printf("%s  ",fileName);
    }
    printf("\n");
    closedir(dir);
}



void process_shell_builtins_cmd(char *args[], int* running, int iFlag, int *doneBuiltins){
    *doneBuiltins = 1;
    if (strcmp(args[0], "exit")==0){
        *running =0;
        return;
    }
    if (strcmp(args[0], "history")==0){
        getHistory();
    }    
    else if (strcmp(args[0], "pwd")==0)
        getWorkingDirectory();
    else if (strcmp(args[0], "ls")==0)
        listSubDirectory();
    else if (strcmp(args[0], "cd")==0){
        if (args[1] != NULL)
            if (chdir(args[1])!=0)
                perror(args[1]);
    }
        
    else if (strcmp(args[0], "sort")==0){
        if (args[1] != NULL && !iFlag){
            sortFile(args[1]);
        }
        else{
            *doneBuiltins = 0;
        }
    }
    else *doneBuiltins = 0;
}


#endif
