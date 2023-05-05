
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int 
main (int argc, char *argv[]) 
{

    if (argc != 2) { 
        fprintf(2, "invalid number of arguments") ;
        exit(-1) ; 
    }

    sched(argv[1]) ; 

    exit(0) ; 
}