#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Nombre de paramètres incorrect");
        return 1;
    }
    char* chemin = argv[1];
    int f = open(chemin,O_RDONLY);
    if (f==-1){
        printf("Impossible d'ouvrir le fichier %s\n",chemin);
        return 2;
    }
    char tmp;
    int compteur = 0;
    while(read(f,&tmp,1)){
        compteur++;
    }
    close(f);
    printf("Le nombre de caractère dans %s est de %i\n",chemin,compteur);
    return 0;
}