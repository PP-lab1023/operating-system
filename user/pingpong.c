#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
    
int
main(){
    int p[2];
    pipe(p);
    char buf[64];
    write(p[1], "hi", 3);
    if(fork() == 0){
        int pid = getpid();
        read(p[0], buf, sizeof(buf));
        fprintf(1, "%d: received ping\n", pid);
        write(p[1], "hello", 6);
        exit(0);
    }else{
        wait((int *)0);
        int pid = getpid();
        read(p[0], buf, sizeof(buf));
        fprintf(1, "%d: received pong\n", pid);
        exit(0);
    }
}   

