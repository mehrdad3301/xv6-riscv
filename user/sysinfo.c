#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

#define M 1000000

int 
main(int argc, char *argv[])
{ 

    if(argc != 1) { 
        fprintf(2, "sysinfo takes no arguments!"); 
        exit(-1); 
    }

    struct sysinfo sinfo ;
    if (sysinfo(&sinfo) < 0) { 
        fprintf(2, "sysinfo: error in system call"); 
        exit(-1); 
    }

    printf("uptime: %d\ntotal memory: %dM\nfree memory: %dM\nused processes: %d\n",
    sinfo.uptime, sinfo.totalram, sinfo.freeram/M , sinfo.procs); 

    exit(0); 
}