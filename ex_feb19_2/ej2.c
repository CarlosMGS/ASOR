#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>


#define BUFSIZE 256

int main(int argc, char **argv){

    if(argc < 3){
        perror("Debes introducir direccion y puerto.");
        return -1;
    }

    struct addrinfo *result;
    struct addrinfo hints;

    struct sockaddr client;
    socklen_t clientlen = sizeof(struct sockaddr);

    char *buf, host[BUFSIZE], port[BUFSIZE];

    if(memset(&hints, 0, sizeof(struct addrinfo)) < 0){
        perror("Error en memset().");
        return -1;
    }

    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;

    if(getaddrinfo(argv[1], argv[2], &hints,&result)<0){
        perror("Error en getaddrinfo().");
        return -1;
    }

    int sd, sd_client;

    if((sd=socket(result->ai_family,result->ai_socktype,0))<0){
        perror("Error en socket().");
        return -1;
    }

    if(bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen)<0){
        perror("Error en bind().");
        return -1;
    }

    if(listen(sd,16)<0){
        perror("Error en listen().");
        return -1;
    }

    buf = malloc(BUFSIZE);

    while(1){

        if((sd_client=accept(sd,(struct sockaddr *) &client, &clientlen))<0){
            perror("Error en accept().");
            return -1;
        }

        

        getnameinfo(&client, clientlen, host, NI_MAXHOST, port, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV );

        freeaddrinfo(result);

        printf("Conexion con %s:%s\n", host, port);

        int c;

        while(1){
            
            if((c=recv(sd_client, buf, BUFSIZE, 0))<0){
                perror("error en recv().");
                return -1;
            }
            buf[c] = '\0';

            printf("Mensaje: %s \n", buf);

            if(send(sd, host, NI_MAXHOST, 0)<0){
                perror("Error en send().");
                return -1;
            }

        }

        close(sd_client);
    }

    free(buf);

    return 0;
}