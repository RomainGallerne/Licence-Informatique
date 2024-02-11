#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Nombre de paramètres incorrect");
        exit(EXIT_FAILURE);
    }
    int compteur = 0;
    char* chemin = argv[1];
    FILE* f = fopen(chemin, "r");
    if (f==NULL){
        printf("Impossible d'ouvrir le fichier %s\n",chemin);
        exit(EXIT_FAILURE);
    }
    while(fgetc(f) != EOF){
        compteur++;
    }
    fclose(f);
    printf("Le nombre de caractère dans %s est de %i\n",chemin,compteur);
    return 0;
}