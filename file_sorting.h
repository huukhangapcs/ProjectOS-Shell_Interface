#ifndef __FILESORTING__
#define __FILESORTING__
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

int cmpr(const void *a, const void *b) { 
   return (strcmp(*(char **)a, *(char **)b));
}
void sort_a(void *array, unsigned n) { 
   qsort(array, n, sizeof(const char *), cmpr);
}
void sortFile(char* a1){
    char *lines[1000];  //limit 1000 lines
    lines[1] = "\0";
    char line[1024]; // 1 line 1024 characters
    int cnt = 0;
    FILE *file = fopen(a1, "r");
    if (file == NULL)
    {
        perror(a1);
        return;
    }
    while (fgets(line, sizeof (line), file) != NULL)
        {
            line[strcspn(line, "\n")] = '\0';
            if (cnt < sizeof (lines)/ sizeof (*lines))
                lines[cnt++] = strdup(line);
            else break;
        }
    fclose(file);
    if (strcmp(lines[1], "\0")){
        sort_a(lines, cnt);    
        for (int j = 0; j < cnt; j++)
            printf("%s\n", lines[j]);
        for (int j = 0; j < cnt; j++)
            free(lines[j]);
    }
}





#endif