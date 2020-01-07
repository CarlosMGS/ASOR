#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

volatile int stop = 0;
volatile int inte = 0;

void senal(int signal){
    if(signal == SIGINT){
        inte++;
    }else if(signal == SIGTSTP){
        stop++;
    }
}

int main(int argc, char **argv){

    sigset_t set;

    sigemptyset(&set);

    //sigaddset(&set, SIGINT);
    //sigaddset(&set, SIGTSTP);

    //sigprocmask(SIG_UNBLOCK, &set, NULL);

    struct sigaction sa_int;
    sa_int.sa_handler = senal;
    sigaction(SIGINT, &sa_int, NULL);

    struct sigaction sa_stp;
    sa_stp.sa_handler = senal;
    sigaction(SIGTSTP, &sa_stp,NULL);

    printf("ID del proceso: %d\n", getpid());
    printf("esperando senales...\n");
    while(stop + inte < 10){
        sigsuspend(&set);
    }

    printf("\nSIGTSTP: %d\nSIGINT: %d\n", stop, inte);

    
}