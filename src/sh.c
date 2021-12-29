#include "os.h"

void sh(){
    char input[50];
    while(;;){
        lib_puts("$ ");
        gets(input);
        int pid = fork();
        if(pid == 0){
            // child process
            exec(input);
        }else{
            // parent process
        }
    }
}