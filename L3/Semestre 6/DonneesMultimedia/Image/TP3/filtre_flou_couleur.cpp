// filtre_flou1.cpp

#include <stdio.h>
#include "image_ppm.h"

int indiceImage(int x, int y, int width, int height){
  /*if(x > width){printf("x trop grand");}
  if(x < 0){printf("x trop petit");}
  if(y > height){printf("y trop grand");}
  if(y < 0){printf("y trop petit");}*/
  return x * width + y;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
  int nTaille3 = nTaille * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille3);

  for (int i=3; i < 3*nH-3; i++)
   for (int j=3; j < 3*nW-3; j++)
     {
      ImgOut[indiceImage(i,j,nW,nH)]=(
        ImgIn[indiceImage(i,j,nW,nH)] +
        ImgIn[indiceImage(i-3,j,nW,nH)] +
        ImgIn[indiceImage(i+3,j,nW,nH)] +
        ImgIn[indiceImage(i,j-3,nW,nH)] +
        ImgIn[indiceImage(i,j+3,nW,nH)] +
        ImgIn[indiceImage(i+3,j+3,nW,nH)] +
        ImgIn[indiceImage(i+3,j-3,nW,nH)] +
        ImgIn[indiceImage(i-3,j+3,nW,nH)] +
        ImgIn[indiceImage(i-3,j-3,nW,nH)]
      )/9;
     }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
