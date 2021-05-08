#ifndef UTILS
#define UTILS
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
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

#endif
