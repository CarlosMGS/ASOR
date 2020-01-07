#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


/*Cree dos tuberías con nombre (​ tuberia1 y ​ tuberia2​ ) y escriba un
programa que espere hasta que haya datos listos para leer en alguna de ellas. El programa mostrará
el nombre de la tubería desde la que se leyó y los datos leídos. El programa detectará cuándo se
cierra​ ​ el​ ​ extremo​ ​ de​ ​ escritura​ ​ de​ ​ una​ ​ tubería​ ​ ( ​ read()​​ ​ devuelve​ ​ 0)​ ​ para​ ​ cerrarla​ ​ y ​ ​ volver​ ​ a ​ ​ abrirla.
Nota: ​ Se recomienda hacer este ejercicio en dos partes: primero un programa que lea de la tubería
adecuada​ ​ y ​ ​ luego​ ​ modificarlo​ ​ para​ ​ que​ ​ la​ ​ vuelva​ ​ a ​ ​ abrir​ ​ si​ ​ se​ ​ cierra​ ​ el​ ​ extremo​ ​ de​ ​ escritura.*/

#define BUFSIZE 256

int main(int argc, char **argv){

    if(argc < 1){
        perror("Faltan argumentos.");
        return -1;
    }

    int tub1, tub2;
    fd_set readfds;
    struct timeval tv;
    char *buf;

    remove("tub1");
    remove("tub2");

    if(mkfifo("tub1", 0666)<0 || mkfifo("tub2", 0666)<0){
        perror("Error en mkfifo.");
        return -1;
    }

    tub1 = open("tub1", O_RDONLY | O_NONBLOCK);
    tub2 = open("tub2", O_RDONLY | O_NONBLOCK);

    while(1){
        FD_ZERO(&readfds);
        FD_SET( tub1, &readfds);
        FD_SET( tub2, &readfds);

        tv.tv_sec = 0;
        tv.tv_usec = 0;
        buf = malloc(BUFSIZE);

        if(select((tub1 > tub2 ? tub1+1: tub2+1), &readfds, NULL, NULL, &tv)<0){
            perror("Error en select().");
            return -1;
        }

        if(FD_ISSET(tub1, &readfds)){
            
            read(tub1, buf,BUFSIZE);
            printf("Leyendo de la tuberia 1\n%s\n", buf);

            close(tub1);
            tub1 = open("tub1", O_RDONLY | O_NONBLOCK);
            
        }else if(FD_ISSET(tub2, &readfds)){
            read(tub2, buf,BUFSIZE);
            printf("Leyendo de la tuberia 2\n%s\n", buf);

            close(tub2);
            tub2 = open("tub2", O_RDONLY | O_NONBLOCK);
        }

        free(buf);
    }

    return 0;
}