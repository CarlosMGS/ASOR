#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char **argv) {
    

    if (argc < 2) {

    printf("ERROR: Falta PID\n");
    return -1;

    }

    pid_t pid = atoi(argv[1]);
    int sched = sched_getscheduler(pid);

    struct sched_param param;

    sched_getparam(pid,&param);

    int min = sched_get_priority_min(sched);
    int max = sched_get_priority_max(sched);

    switch (sched)
    {
    case SCHED_FIFO:
        printf("Planificacion FIFO con prioridad %i, prioridad maxima %i, prioridad minima %i", param.sched_priority, max, min );
        return 0;
        break;
    case SCHED_OTHER:
        printf("Planificacion OTHER con prioridad %i, prioridad maxima %i, prioridad minima %i", param.sched_priority, max, min );
        return 0;
        break;

    case SCHED_RR:
        printf("Planificacion ROUND ROBIN con prioridad %i, prioridad maxima %i, prioridad minima %i", param.sched_priority, max, min );
        return 0;
        break;

    default:
        return -1;
        break;
    }

}