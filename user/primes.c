#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void func(int *p);

int
main(){
    int p[2];
    pipe(p);
    for(int i = 2; i <= 35; ++i){
        write(p[1], &i, 4);
    }
    close(p[1]);
    func(p);
    exit(0);
}

void
func(int *p){
    if(fork() == 0){
        char buf[64];
        if(read(p[0], buf, 4) == 0){
            exit(0);
        }
        int prime = *buf;
        fprintf(2, "prime %d\n", prime);

        int pi[2];
        pipe(pi);
        while(read(p[0], buf, 4) != 0){
            int tmp = *buf;
            if(tmp % prime != 0){
                write(pi[1], &tmp, 4);
            }
        }
        close(pi[1]);  
        func(pi);
    }else{
        wait((int *)0);
    }
}
