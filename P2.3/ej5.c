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

    pid = getpid();
    ppid = getppid();
    gid = getpgid(pid);
    sid = getsid(pid);

    struct rlimit rlim;

    int max=getrlimit(RLIMIT_NOFILE, &rlim);

    printf("El pid es %d, el ppid %d, el gid es %d, el sid es %d \n", pid, ppid, gid, sid);
    printf("El numero maximo de ficheros del proceso es %d", rlim.rlim_max);

    return 0;
}