#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

volatile int stop = 0;

void senal(int senial){
  if (senial == SIGUSR1) stop = 1;
}


int main(int argc, char **argv){

    if(argc < 2){
        printf("ERROR: faltan los segundos \n");
        return -1;
    }

    sigset_t set;
    sigemptyset(&set);

    sigaddset(&set, SIGUSR1);

    sigprocmask(SIG_UNBLOCK, &set, NULL);


    struct sigaction sa;
    sa.sa_handler = senal;

    int secs = atoi(argv[1]);

    //sleep(secs);

    int i=0;

    while(i<secs && stop == 0){
        i++;
        sleep(1);
    }

    if(stop==0){
        printf("No se ha recibido senal SIGUSR1, se borra el programa!");

        unlink(argv[0]);
    }else{
        printf("Se ha recibido la senal SIGUSR1 y el programa no se borra");
    }

    return 0;
    
}