#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

/*Ejercicio 2 (1 punto). Escriba un programa que recorra un directorio, cuya ruta recibe como
argumento, y muestre el nombre de los ficheros que contiene, el ​ uid del usuario propietario,
número de i-nodo y tamaño.
Nota: ​ Se recomienda hacer este ejercicio en dos partes: primero nombre, despues el resto*/

int main(int argc, char **argv){

    if(argc < 2){
        perror("Debe introducir el nombre del directorio.");
        return -1;
    }

    DIR *dir;
    struct dirent *dirent;
    struct stat statbuf;

    if((dir = opendir(argv[1]))<0){
        perror("Error en opendir().");
        return -1;
    }

    //al ser do while, sobra una ronda, pero por lo demas funciona bien
    do{
        dirent = readdir(dir);
        printf("------------------------------------------\n");

        if(stat(dirent->d_name, &statbuf)<0){
            perror("Error en stat().");
            return -1;
        }

        printf("Nombre: %s\n", dirent->d_name);
        printf("UID owner: %d\n", statbuf.st_uid);
        printf("Numero de i-nodo: %ld\n", dirent->d_ino);
        printf("Tamanio: %ld\n", statbuf.st_size);

    }while(dirent!=NULL);

    return 0;
}