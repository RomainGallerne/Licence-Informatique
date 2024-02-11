// gradient.cpp

#include <stdio.h>
#include "image_ppm.h"

int indiceImage(int x, int y, int width, int height){
  if(x >= width){printf("x trop grand");}
  if(x < 0){printf("x trop petit");}
  if(y >= height){printf("y trop grand");}
  if(y < 0){printf("y trop petit");}
  return x * width + y;
}

int Aj(int i, int j, OCTET *ImgIn, int nW, int nH){
  if(j+1 <= nW) return ImgIn[indiceImage(i,j+1,nW,nH)]-ImgIn[indiceImage(i,j,nW,nH)];
  else return ImgIn[indiceImage(i,j,nW,nH)];
}

int Ai(int i, int j, OCTET *ImgIn, int nW, int nH){
  if(i+1 <= nH) return ImgIn[indiceImage(i+1,j,nW,nH)]-ImgIn[indiceImage(i,j,nW,nH)];
  else return ImgIn[indiceImage(i,j,nW,nH)];
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
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

 for (int i=1; i < nH-1; i++)
   for (int j=1; j < nW-1; j++)
     {
      ImgOut[indiceImage(i,j,nW,nH)]= 
      sqrt(
        pow(Ai(i,j,ImgIn,nW,nH),2) +
        pow(Aj(i,j,ImgIn,nW,nH),2)
      );
     }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
