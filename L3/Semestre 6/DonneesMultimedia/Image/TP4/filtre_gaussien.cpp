// gaussien.cpp

#include <stdio.h>
#include "image_ppm.h"

int indiceImage(int x, int y, int width, int height){
  if(x >= width){printf("x trop grand");}
  if(x < 0){printf("x trop petit");}
  if(y >= height){printf("y trop grand");}
  if(y < 0){printf("y trop petit");}
  return x * width + y;
}

int filtre(int x,int y, OCTET *ImgIn,int nW,int t[9]) {
  int res=
  t[0]*ImgIn[(x-1)*nW+y-1] +
  t[1]*ImgIn[(x-1)*nW+y] +
  t[2]*ImgIn[(x-1)*nW+y+1] +
  t[3]*ImgIn[x*nW+y-1] +
  t[4]*ImgIn[x*nW+y] +
  t[5]*ImgIn[x*nW+y+1] +
  t[6]*ImgIn[(x+1)*nW+y-1] +
  t[7]*ImgIn[(x+1)*nW+y] +
  t[8]*ImgIn[(x+1)*nW+y+1];
  int sum=0;
  for(int i=0;i<9;i++){sum+=t[i];}
  return res/sum;
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

  int voisin[9] = {1,4,1,4,5,4,1,4,1};
  for (int i=1; i < nH-1; i++)
    for (int j=1; j < nW-1; j++)
      ImgOut[indiceImage(i,j,nW,nH)] = filtre(i,j,ImgIn,nW,voisin);

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
