#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


int main(int argc, char **argv){


    if(argc < 2){
        printf("Error: Falta la dirección!");

        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *it;
    
    char host[NI_MAXHOST];

    //inicializamos el filtro, a 0 o null salvo el family
    hints.ai_family = AF_UNSPEC; //unspec para que acepte ipv4 e ipv6
    hints.ai_protocol = 0;
    hints.ai_socktype = 0;
    hints.ai_flags = AI_PASSIVE; //ignora los flags
    hints.ai_addr = NULL;
    hints.ai_canonname = NULL;
    hints.ai_next = NULL; //todos los demás a 0 o NULL porque queremos toda la información
    
    if(getaddrinfo(argv[1], NULL, &hints, &result)!=0){
        printf("No se ha podido recuperar la información de la dirección correctamente.");
        return -1;
    };

    for(it=result; it != NULL; it = it->ai_next){ //recorremos todas la entradas de la estruct
        int family = it->ai_family;
        
        switch(family){
            case AF_INET:
                
                //int getnameinfo(const struct sockaddr *sa, socklen_t salen,char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags)
                getnameinfo(it->ai_addr, it->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

                printf("Direccion IPv4:\n");
                printf("%s ", host);
		        printf("%i ", it->ai_family);
		        printf("%i\n", it->ai_socktype);
            break;

            case AF_INET6:
                
                //int getnameinfo(const struct sockaddr *sa, socklen_t salen,char *host, socklen_t hostlen, char *serv, socklen_t servlen, int flags)
                getnameinfo(it->ai_addr, it->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

                printf("Direccion IPv6:\n");
                printf("%s ", host);
		        printf("%i ", it->ai_family);
		        printf("%i\n", it->ai_socktype);
            break;

            default:
                
                printf("No se ha podido conseguir la información para esa direccion.");
                
                return -1;

            break;
        }
    }

    freeaddrinfo(result);

    return 0;

}
