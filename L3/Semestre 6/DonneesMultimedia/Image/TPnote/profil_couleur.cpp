#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {
    char cNomImgLue[250];
    int nH, nW, nTaille;
    if (argc != 4) {
        printf("Usage : ImageIn.pgm ligne_ou_colonne Indice\n");
        exit(1);
    }
    int Indice;int LiCol; //0 = ligne, 1 = colonne
    sscanf (argv[3],"%i",&Indice);
    sscanf (argv[2],"%i",&LiCol);
    sscanf (argv[1],"%s",cNomImgLue);
    OCTET *ImgIn;
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    if (LiCol==0 && Indice>=nH) {
        printf("L'indice de la ligne doit être strictement inférieur au nombre de ligne de l'image.\n");
        exit(1);
    }
    if (LiCol==1 && Indice>=nW) {
        printf("Lindice de la colonne doit être strictement inférieur au nombre de colonne de l'image.\n");
        exit(1);
    }
    int tailleProfil;
    if (LiCol) {tailleProfil=nH;} else {tailleProfil=nW;}
    int profil [tailleProfil];
    for (int i=0;i<tailleProfil;i++) {
        profil[i]=0;
    }
    if (LiCol==0) { //ligne   
        for (int j=0; j < nW; j++) {
            profil[j]=ImgIn[Indice*nW+j];
        }
    }
    else { //colonne
        for (int i=0; i<nH; i++) {
            profil[i]=ImgIn[i*nW+Indice];
        }
    }
    for (int i=0;i<tailleProfil;i++) {
        printf("%i %i\n",i,profil[i]);
    }
    return 1;
}