#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main(int argc, char **argv) {
    
    pid_t pid;
    pid_t ppid;
    pid_t gid;
    pid_t sid;

    
    pid_t cur = fork();

    if(cur==0){
        pid = getpid();
        ppid = getppid();
        gid = getpgid(pid);
        sid = getsid(pid);
        printf("Soy el hijo.El pid es %d, el ppid %d, el gid es %d, el sid es %d \n", pid, ppid, gid, sid);
    }else if(cur>0){
        sleep(50);
        pid = getpid();
        ppid = getppid();
        gid = getpgid(pid);
        sid = getsid(pid);
        printf("Soy el padre.El pid es %d, el ppid %d, el gid es %d, el sid es %d \n", pid, ppid, gid, sid);
    }else{
        printf("Ha habido un error!!");
        return -1;
    }

    
    

    return 0;
}