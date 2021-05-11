#ifndef UTILS
#define UTILS
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include<stdlib.h>
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
void splitToken(char* cmd, char* args[]){
    char *token = strtok(cmd, " ");
    int i = 0;
    args[i] = token;
    while(token != NULL){
    	args[i++] = token;
    	token = strtok(NULL, " ");
    }
}
int cmpr(const void *a, const void *b) { 
   return (strcmp(*(char **)a, *(char **)b));
}
void sort_a(void *array, unsigned n) { 
   qsort(array, n, sizeof(const char *), cmpr);
}
void sortFile(char* fileName){
    char *lines[1000];  //limit 1000 lines
    char line[1024]; // 1 line 1024 characters
    int cnt = 0;
    FILE *file = fopen(fileName, "r");

    if (file != NULL)
    {
        while (fgets(line, sizeof (line), file) != NULL)
        {
            line[strcspn(line, "\n")] = '\0';
            if (cnt < sizeof (lines)/ sizeof (*lines))
            {
                lines[cnt++] = strdup(line);
            }
            else
            {
                break;
            }
        }
        fclose(file);
        sort_a(lines, cnt);
        for (int j = 0; j < cnt; j++)
        {
            printf("%s\n", lines[j]);
        }
        for (int j = 0; j < cnt; j++)
        {
            free(lines[j]);
        }
    }
    else
    {
        perror(fileName);
    }
}


#endif
