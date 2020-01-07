#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 256

int main(int argc, char **argv){

    if(argc < 3){
        printf("Error: Debes introducir una dirección y un puerto.");

        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *result;
    struct sockaddr *client;
    socklen_t clientlen = sizeof(struct sockaddr *);

    char *buf, host[BUFSIZE], port[BUFSIZE], datatime[BUFSIZE];
    
    memset(&hints, 0, sizeof(struct addrinfo));
    
    //inicializamos el filtro, a 0 o null salvo el family
    hints.ai_family = AF_UNSPEC; 
    hints.ai_flags = AI_PASSIVE; 
    hints.ai_socktype = SOCK_DGRAM;

    if(getaddrinfo(argv[1], argv[2], &hints, &result)!=0){
        printf("No se ha podido traducir la direccion y puerto");
        return -1;
    }

    int udp_sd;
    if((udp_sd = socket(result->ai_family, result->ai_socktype, 0))<0){
        printf("Error en socket()");
        return -1;
    }

    if(bind(udp_sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen)<0){
        printf("Error en bind()");
        return -1;
    }

    while(1){

        buf = malloc(BUFSIZE);
        int c;

        if((c = recvfrom(udp_sd, buf, BUFSIZE,0, client, &clientlen)) < 0){
            perror("Problema en recvfrom()\n");
            return -1;
        }

        buf[c] = '\0';

        if(getnameinfo(client, clientlen, host, BUFSIZE, port, BUFSIZE, NI_NUMERICHOST) < 0){
            
            perror("Problema en getnameinfo()\n");
            return -1;
        }

        time_t t = time(NULL);
        struct tm *tm;
        tm = localtime(&t);

        

                       
        sprintf(datatime, "%d:%d:%d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
        printf("Mensaje recibido de %s, por el puerto %s: %s", host, port, buf);

        if(sendto(udp_sd, datatime, strlen(datatime),0,client, clientlen)!= 0){
            printf("Error en sendto()");
            return -1;
        }

        free(buf);
    }

    return 0;


}