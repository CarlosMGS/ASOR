#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


int main(int argc, char **argv){


    if(argc < 3){
        printf("Error: Debes introducir una dirección y un puerto.");

        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *result;
    
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
    while(1){
    int sd_client = accept(sd, (struct sockaddr *) &client, &clientlen);

    getnameinfo(&client,clientlen, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV );

    freeaddrinfo(result);

    printf("Conexion %s (%s) \n", host, server);

    while(1){
        char buf[256];

        int rc = recv(sd_client, buf, 255, 0);
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

    close(sd);
    return 0;


}