#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{ 
    struct sysinfo sinfo ;
    if (sysinfo(&sinfo) < 0) { 
        fprintf(2, "sysinfo: error in system call"); 
        exit(-1); 
    }

    sbrk(sinfo.totalram * 2 / 3) ;
    fork() ;
    exit(0); 
}