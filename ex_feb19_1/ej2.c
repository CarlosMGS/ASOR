#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv){

    int status;

    if(argc < 2){
        printf("Faltan argumentos!");
        return -1;
    }

    pid_t pid = fork();

    if(pid == 0){

        setsid();
        //cambiar el entorno de trabajo a /tmp
        chdir("/tmp");

        pid_t _pid = getpid();

        printf("id del proceso: %d\nid del proceso padre: %d\nid de sesion: %d\nid del grupo: %d\n", _pid, getppid(),getsid(_pid), getgid());

        execvp(argv[1], argv+1);

    }else if(pid==-1){
        printf("Error en el fork.");
        return -1;
    }else{
        wait(&status);
        return 0;
    }

    return 0;

}