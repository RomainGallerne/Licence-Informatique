// modifY.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int clamp (int val){
  if(val<0){return 0;}
  else if(val>255){return 255;}
  else return val;
}

int main(int argc, char* argv[])
{
  char cNomImgYIn[250];
  char cNomImgYOut[250];
  int nH, nW, nTaille, k;
  
  if (argc != 4) 
     {
       printf("Usage: ImageYIn.pgm ImageYOut.pgm modif\n"); 
       exit (1) ;
     }
   
  sscanf (argv[1],"%s",cNomImgYIn);
  sscanf (argv[2],"%s",cNomImgYOut);
  sscanf (argv[3],"%i",&k);

   OCTET *ImgYIn, *ImgYOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgYIn, &nH, &nW);
   nTaille = nH * nW;

   allocation_tableau(ImgYIn, OCTET, nTaille);
   lire_image_pgm(cNomImgYIn, ImgYIn, nH * nW);
   allocation_tableau(ImgYOut, OCTET, nTaille);
	
  for (int i=0; i < nTaille; i+=1)
  {
    ImgYOut[i] = clamp(ImgYIn[i]+k);
  }

   ecrire_image_pgm(cNomImgYOut, ImgYOut,  nH, nW);
   free(ImgYIn);free(ImgYOut);
   return 0;
}
