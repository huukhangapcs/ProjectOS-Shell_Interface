#ifndef UTILS
#define UTILS
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include<stdlib.h>
#include <string.h>
#include <fcntl.h>
#define MAX_LINE 80 /* The maximum length command */

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

int cmpr(const void *a, const void *b) { 
   return (strcmp(*(char **)a, *(char **)b));
}
void sort_a(void *array, unsigned n) { 
   qsort(array, n, sizeof(const char *), cmpr);
}

void sortFile(char* a1, char* a2){
    char *lines[1000];  //limit 1000 lines
    lines[1] = "\0";
    char line[1024]; // 1 line 1024 characters
    int cnt = 0;
    if (strcmp(a1,"<")!=0) {
        FILE *file = fopen(a1, "r");
        if (file != NULL)
        {
            while (fgets(line, sizeof (line), file) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (cnt < sizeof (lines)/ sizeof (*lines))
                    lines[cnt++] = strdup(line);
                else break;
            }
            fclose(file);
        }
        else {
            perror(a1);
            return;
        }
        
    } else{
        while (fgets(line, sizeof (line), stdin) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (cnt < sizeof (lines)/ sizeof (*lines))
                    lines[cnt++] = strdup(line);
                else break;
            }
    }
    if (strcmp(lines[1], "\0")){
        sort_a(lines, cnt);    
        for (int j = 0; j < cnt; j++)
            printf("%s\n", lines[j]);
        for (int j = 0; j < cnt; j++)
            free(lines[j]);
    }
    
}

int handleIR(char* iDirFile){
    if (iDirFile == NULL){
        printf("No destination specified\n");
        return 0;
    }
    else{
        int in = open(iDirFile, O_RDONLY);
        int stdin_copy = dup(STDIN_FILENO);
        dup2(in, STDIN_FILENO);
        close(in);
        return stdin_copy;
    }
}
int handleOR(char* oDirFile){
    if (oDirFile == NULL){
        printf("No destination specified\n");
        return 0;
    }
    else{
        int out = open(oDirFile, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        int stdout_copy = dup(STDOUT_FILENO);
        dup2(out, STDOUT_FILENO);
        close(out);
        return stdout_copy;
    }    
}
void stopIR(int stdin){
    if (stdin!=0){
        dup2(stdin, STDIN_FILENO);
        close(stdin);
    }
}
void stopOR(int stdout){
    if (stdout!=0){
        dup2(stdout, STDOUT_FILENO);
        close(stdout);
    }
}
#endif
