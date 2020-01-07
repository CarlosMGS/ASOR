#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define RD 0
#define WR 1



int main(int argc, char **argv){

    if(argc < 3){
        perror("Error: faltan argumentos de entrada.");
        return -1;
    }

    pid_t pid;
    int fds[2];
    int status;

    pipe(fds);


    pid = fork();

    
    if(pid == 0){

        //hijo
        printf("ID del proceso hijo: %d\n", getpid());

        close(fds[WR]);

        dup2(fds[RD], 0);

        close(fds[RD]);

        execvp(argv[2],argv+2);

    }else if(pid == -1){
        perror("Error en el fork().");
        return -1;
    }else{
        //padre

        
        printf("ID del proceso padre: %d\n", getpid());

        close(fds[RD]);

        dup2(fds[WR], 1);

        close(fds[WR]);

       execlp(argv[1], argv[1], NULL);

       //wait(&status);

    }

    return 0;
}