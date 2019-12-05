#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char **argv){

    if (argc < 2) {

      printf("Falta un argumento.\n");
      
      return -1;
    
    }

    char *dir = getenv("HOME");
	char *tuberia = strcat(dir, "/P2.4/tuberia");


    printf("SIMON SAYS: %s\n", argv[1]);
  	mkfifo(tuberia, 0644);

	int fd = open(tuberia, O_WRONLY);

    char *mensaje=strcat(argv[1], "\n");

	if(write(fd, argv[1], strlen(argv[1]))==-1){
        
        perror("error al escribir en la tubería");
        close(fd);
        return -1;
    }

	close(fd);


    return 0;
}
