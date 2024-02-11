// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int indiceImage(int x, int y, int width, int height){
  if(x >= width){printf("x trop grand");}
  if(x < 0){printf("x trop petit");}
  if(y >= height){printf("y trop grand");}
  if(y < 0){printf("y trop petit");}
  return x * width + y;
}

bool OuEx(bool P, bool Q){
  if(P || Q){
    if(!(P && Q)){return true;}
    else{return false;}}
  else{return false;}
}

int main(int argc, char* argv[])
{
  char cNomImgLue1[250], cNomImgLue2[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn1.pgm ImageIn2.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue1);
   sscanf (argv[2],"%s",cNomImgLue2);
   sscanf (argv[3],"%s",cNomImgEcrite);

   OCTET *ImgIn1, *ImgIn2, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn1, OCTET, nTaille);
   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(cNomImgLue1, ImgIn1, nH * nW);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }

for(int a=0; a<nTaille; a++){
       ImgOut[a]=abs(ImgIn1[a]-ImgIn2[a])+128;
     }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn1); free(ImgIn2); free(ImgOut);

   return 1;
}
