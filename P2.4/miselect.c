#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, char **argv){

    if (argc < 2) {
      
      printf("Falta un argumento\n");
      
      return -1;
    }


    //abrir la tuberia

    int fd_tub = open(argv[1], O_RDWR);

    fd_set fds;

    char buf[256];

    while(1){

        FD_ZERO(&fds);

        FD_SET(fd_tub, &fds); //descriptor tuberia y descriptores a 0
        FD_SET(0, &fds); //entrada standard y descriptores a 0

        int rc = select(fd_tub +1, &fds, NULL, NULL, NULL);

        if(FD_ISSET(0, &fds)){
            //si la entrada standard está preparada

            rc = read(0, buf, 255);
            buf[rc] = '\0';

            printf("STDIN: %s\n", buf);

        }else if(FD_ISSET(fd_tub, &fds)){

            //salida por tuberia si está preparada
            rc = read(fd_tub, buf, 255);
            buf[rc] = '\0';

            printf("TUBERIA: %s\n", buf);
        }


    }














    return 0;
}