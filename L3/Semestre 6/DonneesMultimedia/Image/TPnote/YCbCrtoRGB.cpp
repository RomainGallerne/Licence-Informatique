// RGBtoYCbCr.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int clamp (int val){
  if(val<0){return 0;}
  else if(val>255){return 255;}
  else return val;
}

int main(int argc, char* argv[])
{
  char cNomImgRGB[250];
  char cNomImgY[250];
  char cNomImgCb[250];
  char cNomImgCr[250];
  int nH, nW, nTaille, nR, nG, nB;
  
  if (argc != 5) 
     {
       printf("Usage: ImageY.pgm ImageCb.pgm ImageCr.pgm ImageIn.ppm\n"); 
       exit (1) ;
     }
   
  sscanf (argv[1],"%s",cNomImgY);
  sscanf (argv[2],"%s",cNomImgCb);
  sscanf (argv[3],"%s",cNomImgCr);
  sscanf (argv[4],"%s",cNomImgRGB);

   OCTET *ImgRGB, *ImgY, *ImgCb, *ImgCr;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgY, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgRGB, OCTET, nTaille3);

   allocation_tableau(ImgY, OCTET, nTaille);
   lire_image_pgm(cNomImgY, ImgY, nH * nW);

   allocation_tableau(ImgCb, OCTET, nTaille);
   lire_image_pgm(cNomImgCb, ImgCb, nH * nW);

   allocation_tableau(ImgCr, OCTET, nTaille);
   lire_image_pgm(cNomImgCr, ImgCr, nH * nW);
	
  for (int i=0; i < nTaille3; i+=3)
  {
    /*nR*/ ImgRGB[i] = clamp(ImgY[i/3] + 1.402*(ImgCr[i/3]-128));
    /*nG*/ ImgRGB[i+1] = clamp(ImgY[i/3] - 0.34414*(ImgCb[i/3]-128) - 0.714414*(ImgCr[i/3]-128));
    /*nB*/ ImgRGB[i+2] = clamp(ImgY[i/3] + 1.772*(ImgCb[i/3]-128));
  }

   ecrire_image_ppm(cNomImgRGB, ImgRGB,  nH, nW);
   free(ImgRGB);free(ImgY);free(ImgCr);free(ImgCb);
   return 0;
}
