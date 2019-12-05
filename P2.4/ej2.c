#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#define WR 1
#define RD 0

int main(int argc, char **argv){

    int p_h[2];
    int h_p[2];

    pipe(p_h);
    pipe(h_p);

    pid_t pid = fork();

    if(pid==-1){

        perror("error al hacer el fork");
        return -1;
        
        //execlp(argv[3], argv[3], argv[4], NULL); //argv[3] posicion del ejecutable para el hijo

    }else if(pid==0){

        //hijo
        close(p_h[WR]); 
        close(h_p[RD]);

        dup2(p_h[RD], 0);//entrada estandard
        dup2(h_p[WR], 1);//salida standard

        close(p_h[RD]);
        close(h_p[WR]);

        //system() no se usa
        char *buf_h;
        char *mensaje;

        //bucle para leer mensaje del padre y responder

        for(int i = 0; i<10; i++){
            mensaje = "0";

            while(mensaje != "e"){
                read(0, mensaje, 1);
            }
            
            read(0, buf_h, strlen(buf_h));

            

            printf("Hijo: mensaje recibido.\n %s \n", buf_h);

            sleep(1);

            if(i==9){
                write(1, "q", 1);
            }else{
                write(1, "l", 1);
            }

        }
        
        //execlp(argv[1], argv[1], argv[2], NULL);

    }else{

        //padre
        close(p_h[RD]); 
        close(h_p[WR]);

        dup2(p_h[WR], 1); //salida standard
        dup2(h_p[RD], 0); //entrada standard

        close(p_h[WR]);
        close(h_p[RD]);

        //system() no se usa


        char *buf_p;
        char *mensaje_h = "0";
        //bucle para leer mensaje del hijo y responder

        while(mensaje_h != "q"){

            mensaje_h = "0";
            printf("mensaje del padre: \n");
            scanf("%s", buf_p);

            write(1, "e", 1);

            sleep(1);

            write(1, buf_p, strlen(buf_p));
            

            while(mensaje_h != "l" ){
                read(0, mensaje_h, 1);
            }

            
        }
        
    
    }

    printf("10 mensajes leídos");

    return 0;
}