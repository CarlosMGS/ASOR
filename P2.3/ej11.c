#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int main(int argc, char **argv[]){

    if(argc < 2){
        printf("ERROR: faltan los segundos \n");
        return -1;
    }

    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);

    sigprocmask(SIG_BLOCK, &set, NULL);

    int secs = atoi(argv[1]);

    sleep(secs);

    sigset_t pend;
    sigpending(&pend);

    if(sigismember(&pend, SIGINT)==1){
        printf("Se ha recibido la senal SIGINT\n");

         sigdelset(&set, SIGINT);
    }else{
        printf("No se ha recibido la senal SIGINT\n");
    }

    if(sigismember(&pend, SIGTSTP)==1){
        printf("Se ha recibido la senal SIGTSTP\n");

         sigdelset(&set, SIGTSTP);
    }else{
        printf("No se ha recibido la senal SIGTSTP\n");
    }

    sigprocmask(SIG_UNBLOCK, &set, NULL);

    return 0;
    
}