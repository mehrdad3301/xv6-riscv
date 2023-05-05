
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


// change NOFILE in param.h to 68 
// so that you can have 32 open fds 
// for your children 
#define NUM_CHILD  32  
#define MAX_SIZE   2e9

int 
main (int argc, char *argv[]) 
{ 

    // swtime -> sum of waiting time 
    // sutime -> sum of turn around time 
    // sbtime -> sum of cpu burst time 
    int swtime, sutime, sbtime ; 
    swtime = sutime = sbtime = 0 ; 

    int fd[NUM_CHILD][2] ; 

    int i ; 
    for (i = 0 ; i < NUM_CHILD ; i++) { 
        if (pipe(fd[i]) < 0) {
            fprintf(2, "pipe failed"); 
            exit(-1) ; 
        }
    }

    int pid;
    for (i = 0 ; i < NUM_CHILD ; i++ ){ 

        pid = fork() ; 
        if (pid < 0) { 
            fprintf(2, "failed to fork process"); 
            exit(-1) ;
        } else if (pid == 0) { 
            close(fd[i][0])  ; 

            int j ; 
            for (j = 0 ; j < MAX_SIZE ; j++) {} ;

            int p = getpid() ; 
            int w = wtime(p) ; 
            if (write(fd[i][1], (void *)&w , sizeof(int)) < 0) { 
                fprintf(2, "write failed"); 
                exit(-2) ; 
            }

            int u = utime(p) ; 
            if (write(fd[i][1], (void *)&u , sizeof(int)) < 0) { 
                fprintf(2, "write failed"); 
                exit(-2) ; 
            }

            int b = btime(p) ; 
            if (write(fd[i][1], (void *)&b , sizeof(int)) < 0) { 
                fprintf(2, "write failed"); 
                exit(-2) ; 
            }
            printf("%d %d %d %d %d\n", p, i, w, u, b) ; 

            close(fd[i][1]); 
            exit(0) ; 
        } 
    }

    for (i = 0 ; i < NUM_CHILD ; i++ ) {
        close(fd[i][1]) ; 
    }
    for (i = 0 ; i < NUM_CHILD ; i++ ) {
        int j;
        for (j = 0 ; j < 3 ; j++){
            int x ; 
            if (read(fd[i][0], (void *)&x , sizeof(int)) < 0) { 
                fprintf(2, "read failed"); 
                exit(-2) ; 
            }
            if(j == 0) { 
                swtime += x ; 
            } else if (j == 1) { 
                sutime += x ; 
            } else { 
                sbtime += x ; 
            }
        }

    }
    for (i = 0 ; i < NUM_CHILD ; i++ ) {
        close(fd[i][0]) ; 
    }
    printf("avg btime: %d\navg ttime: %d\navg wtime: %d", sbtime/NUM_CHILD, 
                                                            sutime/NUM_CHILD, 
                                                            swtime/NUM_CHILD) ; 


    exit(0) ;
}