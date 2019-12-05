#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int int_count = 0;
volatile int tstp_count = 0;

void senal (int senal){
    if(senal==SIGINT) int_count++;
    if(senal==SIGTSTP) tstp_count++;
}


int main(int argc, char **argv[]){

    sigset_t set;
    sigemptyset(&set);

    struct sigaction sa_int;
    sa_int.sa_handler = senal;
    sigaction(SIGINT, &sa_int, NULL);

    struct sigaction sa_stp;
    sa_stp.sa_handler = senal;
    sigaction(SIGTSTP, &sa_stp,NULL);

    while(int_count+tstp_count < 10){
        sigsuspend(&set);
    }

    printf("Senales SIGINT: %i \n", int_count);
    printf("Senales SIGTSTP: %i \n", tstp_count);
    
}