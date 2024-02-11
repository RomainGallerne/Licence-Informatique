// EQM.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int indiceImage(int x, int y, int width, int height){
  if(x >= width){printf("x trop grand");}
  if(x < 0){printf("x trop petit");}
  if(y >= height){printf("y trop grand");}
  if(y < 0){printf("y trop petit");}
  return x * width + y;
}

int main(int argc, char* argv[])
{
  char cNomImgLue1[250], cNomImgLue2[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn1.pgm ImageIn2.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue1) ;
   sscanf (argv[2],"%s",cNomImgLue2);

   OCTET *ImgIn1, *ImgIn2;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn1, OCTET, nTaille);
   lire_image_pgm(cNomImgLue1, ImgIn1, nH * nW);
   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

  int EQM = 0;
  int nbDifferent = 0;
  int difference;
  for (int i=0; i < nH; i++)
    for (int j=0; j < nW; j++)
    {
      if(0!=(difference=ImgIn1[indiceImage(i,j,nW,nH)]-ImgIn2[indiceImage(i,j,nW,nH)])){
        EQM += pow(difference,2);
        nbDifferent += 1;
      }
    }
  EQM /= nTaille;
  free(ImgIn1); free(ImgIn2);

  printf("\nNombre total de pixels de l'image : %i\n",nTaille);
  printf("Nombre de pixels différents : %i\n",nbDifferent);
  printf("Erreur quadratique moyenne : %i\n\n",EQM);

  return 0;
}
