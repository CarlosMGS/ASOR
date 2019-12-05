#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define WR 1
#define RD 0

int main(int argc, char **argv){

    if (argc < 5) {
      
      printf("Debe haber 4 argumentos\n");
      
      return -1;
    }

    int fds[2];

    pipe(fds);

    pid_t pid = fork();

    if(pid==0){
        //hijo
        close(fds[WR]);

        dup2(fds[RD], 0);//entrada estandard

        close(fds[RD]);

        //system() no se usa

        execlp(argv[3], argv[3], argv[4], NULL); //argv[3] posicion del ejecutable para el hijo

    }else{
        //padre
        close(fds[RD]);

        dup2(fds[WR], 1); //salida standard

        close(fds[WR]);

        //system() no se usa

        execlp(argv[1], argv[1], argv[2], NULL);

    }

    return 0;
}