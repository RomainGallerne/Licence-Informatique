// erosion.cpp

#include <stdio.h>
#include "image_ppm.h"

int nH, nW, nTaille;

OCTET * dilatation(OCTET *ImgIn,OCTET *ImgOut){
   //Traitement de l'image

  for (int y=1; y < nH-1; y++){ //Pour chaque ligne
    for (int x=1; x < nW-1; x++){ //Pour chaque colonne
      OCTET VoisinGauche = ImgIn[(y*nW)+x-1];
      OCTET VoisinDroite = ImgIn[(y*nW)+x+1];
      OCTET VoisinHaut = ImgIn[(y*nW)+x-nW];
      OCTET VoisinBas = ImgIn[(y*nW)+x+nW];

      if(VoisinDroite==0 || VoisinGauche==0 || VoisinHaut==0 || VoisinBas==0){ImgOut[(y*nW)+x]=0;}
      else {ImgOut[(y*nW)+x]=ImgIn[(y*nW)+x];}
      }
    }

   free(ImgIn);
   return ImgOut;
}

OCTET * erosion(OCTET *ImgIn,OCTET *ImgOut){
   //Traitement de l'image

  for (int y=1; y < nH-1; y++){ //Pour chaque ligne
    for (int x=1; x < nW-1; x++){ //Pour chaque colonne
      OCTET VoisinGauche = ImgIn[(y*nW)+x-1];
      OCTET VoisinDroite = ImgIn[(y*nW)+x+1];
      OCTET VoisinHaut = ImgIn[(y*nW)+x-nW];
      OCTET VoisinBas = ImgIn[(y*nW)+x+nW];

      if(VoisinDroite==255 || VoisinGauche==255 || VoisinHaut==255 || VoisinBas==255){ImgOut[(y*nW)+x]=255;}
      else {ImgOut[(y*nW)+x]=ImgIn[(y*nW)+x];}
      }
    }

   free(ImgIn);
   return ImgOut;
}

int main(int argc, char* argv[])
{
  OCTET *ImgIn, *ImgOut, *ImgInte;
  char cNomImgLue[250], cNomImgEcrite[250], cNomImgIntermediaire[250];
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   allocation_tableau(ImgInte, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

   dilatation(ImgIn,ImgInte);
   erosion(ImgInte,ImgOut);

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   return 1;
}
