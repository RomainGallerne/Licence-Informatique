// RGBtoYCbCr.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgRGB[250];
  char cNomImgY[250];
  char cNomImgCb[250];
  char cNomImgCr[250];
  char premier[10];
  char second[10];
  char dernier[10];
  int nH, nW, nTaille;
  OCTET *n1, *n2, *n3;
  
  if (argc != 8) 
     {
       printf("Usage: ImageY.pgm ImageCb.pgm ImageCr.pgm ImageCouleur.ppm Premier Second Dernier\n"); 
       exit (1) ;
     }
   
  sscanf (argv[1],"%s",cNomImgY);
  sscanf (argv[2],"%s",cNomImgCb);
  sscanf (argv[3],"%s",cNomImgCr);
  sscanf (argv[4],"%s",cNomImgRGB);
  sscanf (argv[5],"%s",premier);
  sscanf (argv[6],"%s",second);
  sscanf (argv[7],"%s",dernier);

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
    if(strcmp(premier,"R")==0){n1 = &ImgRGB[i]; //Première composante Rouge
      if(strcmp(second,"G")==0) {n2 = &ImgRGB[i+1];n3 = &ImgRGB[i+2];} //RGB
      else {n2 = &ImgRGB[i+2];n3 = &ImgRGB[i+1];} //RBG
    }
    else if(strcmp(premier,"G")==0){n2 = &ImgRGB[i]; //Première composante Verte
      if(strcmp(second,"R")==0) {n1 = &ImgRGB[i+1];n3 = &ImgRGB[i+2];} //GRB
      else {n1 = &ImgRGB[i+2];n3 = &ImgRGB[i+1];} //GBR
    }
    else { n3 = &ImgRGB[i];  //Première composante Bleue
      if(strcmp(second,"G")==0) {n2 = &ImgRGB[i+1];n1 = &ImgRGB[i+2];} //BGR
      else {n2 = &ImgRGB[i+2];n1 = &ImgRGB[i+1];} //BRG
    }
    *n1 = ImgY[i/3] + 1.402*(ImgCr[i/3]-128);
    *n2 = ImgY[i/3] - 0.34414*(ImgCb[i/3]-128) - 0.714414*(ImgCr[i/3]-128);
    *n3 = ImgY[i/3] + 1.772*(ImgCb[i/3]-128);
  }

   ecrire_image_ppm(cNomImgRGB, ImgRGB,  nH, nW);
   free(ImgRGB);free(ImgY);free(ImgCr);free(ImgCb);
   return 0;
}
