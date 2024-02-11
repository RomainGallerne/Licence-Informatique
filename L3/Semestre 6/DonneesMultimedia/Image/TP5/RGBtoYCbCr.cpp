// RGBtoYCbCr.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  char cNomImgY[250];
  char cNomImgCb[250];
  char cNomImgCr[250];
  int nH, nW, nTaille, nR, nG, nB;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.ppm ImageY.pgm ImageCb.pgm ImageCr.pgm\n"); 
       exit (1) ;
     }
   
  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgY);
  sscanf (argv[3],"%s",cNomImgCb);
  sscanf (argv[4],"%s",cNomImgCr);

   OCTET *ImgIn, *ImgY, *ImgCb, *ImgCr;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

   allocation_tableau(ImgY, OCTET, nTaille);
   allocation_tableau(ImgCb, OCTET, nTaille);
   allocation_tableau(ImgCr, OCTET, nTaille);
	
   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       ImgY[i/3] = 0.299*nR + 0.587*nG + 0.114*nB;
       ImgCb[i/3] = -0.1687*nR - 0.3313*nG + 0.5*nB + 128;
       ImgCr[i/3] = 0.5*nR - 0.4187*nG - 0.0813*nB + 128;
     }

   ecrire_image_pgm(cNomImgY, ImgY,  nH, nW);
   ecrire_image_pgm(cNomImgCb, ImgCb,  nH, nW);
   ecrire_image_pgm(cNomImgCr, ImgCr,  nH, nW);
   free(ImgIn);free(ImgY);free(ImgCr);free(ImgCb);
   return 0;
}
