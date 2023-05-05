#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define INVALID_PID -1 

int
main(int argc, char *argv[])
{
    
    if(argc != 2){
      fprintf(2, "usage: proctick pid...\n");
      exit(1);
    }

    int ticks ; 
    if ((ticks = proctick(atoi(argv[1]))) < 0) {
        switch (ticks) { 
            case INVALID_PID: 
                fprintf(2, "error: getproctick: invalid pid\n");
            default: 
                fprintf(2, "error: getproctick\n");
        }
      exit(1);
    } 
    printf("%d\n", ticks);
    exit(0); 
}