#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define LONGEST 64

int
readline(char **buf, int i){
    char com[LONGEST];
    int j = 0;
    while(read(0, com+j, 1)){
        if(j == LONGEST){
            fprintf(2, "xargs: argv is too long\n");
            exit(1);
        }

        if(com[j] != '\n' && com[j] != ' '){
            ++j;
            continue;
        }
        
        buf[i] = malloc(strlen(com)); 
              
        if(com[j] == ' '){
            com[j] = '\0';          
            strcpy(buf[i], com);

            j = 0;       
            ++i;
            continue;
        }

        if(com[j] == '\n'){
            com[j] = '\0';
            strcpy(buf[i], com);
           
            ++i;
            return i;
        }      
    }
    return -1;
}

int
main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(2, "Usage: xargs [command]\n");
        exit(1);
    }
    char *buf[MAXARG];
    
    for(int i = 1; i < argc; ++i){
        buf[i-1] = argv[i];
    }

    int end;
    while((end = readline(buf, argc-1)) != -1){     
        buf[end] = 0;
        if(fork() == 0){
            exec(buf[0], buf);
        }else{
            wait((int *)0);
        }
    }
    exit(0);
}




