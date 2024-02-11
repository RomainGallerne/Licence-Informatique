// hysteresis.cpp

#include <stdio.h>
#include "image_ppm.h"

int indiceImage(int x, int y, int width, int height){
  if(x >= width){printf("x trop grand");}
  if(x < 0){printf("x trop petit");}
  if(y >= height){printf("y trop grand");}
  if(y < 0){printf("y trop petit");}
  return x * width + y;
}

int hysteresis(int x,int y, int t[9], OCTET *ImgIn, int nW) {
 bool res=false;
 if (t[0] && ImgIn[(x-1)*nW+y-1]==255) {res = true;}
 if (t[1] && ImgIn[(x-1)*nW+y]==255) {res = true;}
 if (t[2] && ImgIn[(x-1)*nW+y+1]==255) {res = true;}
 if (t[3] && ImgIn[x*nW+y-1]==255) {res = true;}
 if (t[4] && ImgIn[x*nW+y]==255) {res = true;}
 if (t[5] && ImgIn[x*nW+y+1]==255) {res = true;}
 if (t[6] && ImgIn[(x+1)*nW+y-1]==255) {res = true;}
 if (t[7] && ImgIn[(x+1)*nW+y]==255) {res = true;}
 if (t[8] && ImgIn[(x+1)*nW+y+1]==255) {res = true;}
 return res;
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, SB, SH;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm SeuilBas SeuilHaut \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&SB);
   sscanf (argv[4],"%d",&SH);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

  //Premier traitement
  for (int i=1; i < nH-1; i++)
    for (int j=1; j < nW-1; j++) {
      if ( ImgIn[indiceImage(i,j,nW,nH)] <= SB) ImgOut[indiceImage(i,j,nW,nH)]=0;
      if ( ImgIn[indiceImage(i,j,nW,nH)] >= SH) ImgOut[indiceImage(i,j,nW,nH)]=255;
      else ImgOut[indiceImage(i,j,nW,nH)]=ImgIn[indiceImage(i,j,nW,nH)];
    }

  //Second traitement
  int voisin[9] = {1,1,1,1,1,1,1,1,1};
  for (int i=1; i < nH-1; i++)
    for (int j=1; j < nW-1; j++) {
      if ( SB < ImgOut[indiceImage(i,j,nW,nH)] && ImgOut[indiceImage(i,j,nW,nH)] < SH ){
        if (hysteresis(i,j,voisin,ImgOut,nW)) {ImgOut[indiceImage(i,j,nW,nH)]=255;}
        else {ImgOut[indiceImage(i,j,nW,nH)]=0;}}
      else {ImgOut[indiceImage(i,j,nW,nH)]=0;}
    }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
