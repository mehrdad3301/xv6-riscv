
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


#define NUM_CHILD  32  
#define MAX_SIZE   2e9

int 
main (int argc, char *argv[]) 
{ 

    int i ; 
    for (i = 0 ; i < NUM_CHILD ; i++ ){ 

        int pid = fork() ; 
        if (pid < 0) { 
            fprintf(2, "failed to fork process"); 
            exit(-1) ;
        } else if (pid == 0) { 
            int j ; 
            for (j = 0 ; j < MAX_SIZE ; j++) {}
            exit(0) ; 
        } 
    }

    exit(0) ;
}