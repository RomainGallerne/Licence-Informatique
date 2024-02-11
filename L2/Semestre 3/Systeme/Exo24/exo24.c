#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Nombre de paramètres incorrect\n");
        exit(EXIT_FAILURE);
    }
    int compteur = 0;
    char* chemin = argv[2];
    int nbLignes = atoi(argv[1]);
    FILE* f = fopen(chemin, "r");
    if (f==NULL){
        printf("Impossible d'ouvrir le fichier %s\n",chemin);
        exit(EXIT_FAILURE);
    }
    char buf[256];
    while(compteur < nbLignes){
        if (fgets(buf,256,f) != NULL) {
            printf("%s",buf);
        }
        compteur++;
    }
    fclose (f);
    return 0;
}