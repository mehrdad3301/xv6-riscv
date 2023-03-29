#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2] ; 
    pipe(p) ;
    char buf[10] ; 
    int pid = fork() ; 

    if (pid < 0) { 
        fprintf(2, "Couldn't fork process");
        exit(-1); 
    } else if (pid == 0) { 
        read(p[0], buf, sizeof(buf)); 
        printf("%d received: %s\n", getpid(), buf); 
        write(p[1], "pong", 5); 
        close(p[1]); 
        close(p[0]); 
        exit(0); 
    } else { 
        write(p[1], "ping", 5); 
        wait(0); 
        read(p[0], buf, sizeof(buf)); 
        printf("%d received: %s\n", getpid(), buf); 
        close(p[1]); 
        close(p[0]); 
        exit(0); 
    }
    exit(0); 
}