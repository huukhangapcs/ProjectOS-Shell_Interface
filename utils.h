#ifndef UTILS
#define UTILS
#include <stdio.h>
#include <unistd.h>
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


#endif