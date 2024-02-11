// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille;
  int histoRouge[256];
  int histoVert[256];
  int histoBleu[256];
  
  if (argc != 2) {
       printf("Usage: ImageIn.ppm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, 3*nTaille);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }

   for(int i=0; i<256; i++){
    histoRouge[i]=0;
    histoVert[i]=0;
    histoBleu[i]=0;
   }

   for (int i=0; i < 3*nTaille; i+=3)
     {
       histoRouge[ImgIn[i]] += 1; //Histogramme Rouge
       histoVert[ImgIn[i+1]] += 1; //Histogramme Vert
       histoBleu[ImgIn[i+2]] += 1; //Histogramme Bleu
     }

    printf("# Rouge Vert Bleu\n");
    for(int i=0; i<256; i++){
        printf("%i %i %i %i\n",i,histoRouge[i],histoVert[i],histoBleu[i]);
    }

    

   /*ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);*/

   return 1;
}
