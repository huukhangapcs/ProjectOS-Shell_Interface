#ifndef __IOREDIRECTION___
#define __IOREDIRECTION___
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <string.h>
#include <fcntl.h>
void set_o_mode(char* args[], int oFlag, int* stdmode){
    if (oFlag){
        int out = open(args[oFlag], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        if (-1 == out) { perror(args[oFlag]); return; }
        int save_out = dup(fileno(stdout));
        if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return; }
        *stdmode = save_out;
    }
}
void reset_o_mode(char* args[], int oFlag, int *std){
    if (oFlag && *std){
        dup2(*std, fileno(stdout));
        close(*std);
    }
    
}

#endif
