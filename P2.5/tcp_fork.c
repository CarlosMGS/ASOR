#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


void trata_conexion(int sd_client){
    while(1){
        char buf[256];

        int rc = recv(sd_client, buf, 80, 0);
        buf[rc]='\0'; //fin del mensaje en la ultima posicion del buffer

        if(rc==0){
            exit(0);
        }

        printf("Mensaje: %s \n", buf);
        send(sd_client, buf, rc, 0);
    }

    printf("Fin de conexión");
    close(sd_client);
}

void handler(int s){
    int state;
    while( waitpid(-1, &state, WNOHANG) > 0){

    }
}

int main(int argc, char **argv){


    if(argc < 3){
        printf("Error: Debes introducir una dirección y un puerto.");

        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *result;
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    
    sigaction(SIGCHLD, &sa, 0);

    memset(&hints, 0, sizeof(struct addrinfo));
    
    //inicializamos el filtro, a 0 o null salvo el family
    hints.ai_family = AF_UNSPEC; //unspec para que acepte ipv4 e ipv6
    hints.ai_flags = AI_PASSIVE; 
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(argv[1], argv[2], &hints, &result)!=0){
        printf("No se ha podido recuperar la información de la dirección correctamente.");
        return -1;
    };

    //socket(AF_UNSPEC, SOCK_STREAM, 0);
    int sd = socket(result->ai_family, result->ai_socktype, 0);


    //bind(int sock, const struct sockaddr *addr, socklen_t addrlen)
    bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

    char host[NI_MAXHOST];
    char server[NI_MAXSERV];

    struct sockaddr client;
    socklen_t clientlen = sizeof(struct sockaddr);

    listen(sd, 16);


    while(1){ //fallo de seguridad, no se controla el numero de hijos


        int sd_client = accept(sd, (struct sockaddr *) &client, &clientlen);

        

        getnameinfo(&client,clientlen, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV );

        //connect(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);


        freeaddrinfo(result);

        printf("Conexion %s (%s) \n", host, server);

        pid_t pid = fork();

        if(pid==0){//hijo
            close(sd);
            trata_conexion(sd_client);

            return 0;
        }

        close(sd_client);


    }
    



    

    return 0;
}