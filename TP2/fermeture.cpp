// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

OCTET* dilatation(OCTET* ImgIn,int nTaille,int nW){
    OCTET* ImgTemp;
    allocation_tableau(ImgTemp, OCTET, nTaille);
    for (int i = 0; i < nTaille; i++)
    {
    if(ImgIn[i]==0){
        if(ImgIn[i+1]==255 || ImgIn[i-1]==255) ImgTemp[i]=255;
        else if (i>nW && (ImgIn[i+1 -nW]==255 || ImgIn[i-nW]==255 || ImgIn[i-1-nW]==255)) ImgTemp[i]=255;  // ligne du dessus
        else if (i<nTaille-nW && ( ImgIn[i+1 +nW]==255 || ImgIn[i+nW]==255 || ImgIn[i-1+nW]==255)) ImgTemp[i]=255; //ligne du dessous
        else ImgTemp[i]=0;
    }
    else ImgTemp[i]=255;
    }
    return ImgTemp;
}

OCTET* erosion(OCTET* ImgIn,int nTaille,int nW){
    OCTET* ImgTemp;
    allocation_tableau(ImgTemp, OCTET, nTaille);
    for (int i = 0; i < nTaille; i++)
    {
    if(ImgIn[i]==255){
        if(ImgIn[i+1]==0 || ImgIn[i-1]==0) ImgTemp[i]=0;
        else if (i>nW && (ImgIn[i+1 -nW]==0 || ImgIn[i-nW]==0 || ImgIn[i-1-nW]==0)) ImgTemp[i]=0;
        else if (i<nTaille-nW && ( ImgIn[i+1 +nW]==0 || ImgIn[i+nW]==0 || ImgIn[i-1+nW]==0)) ImgTemp[i]=0;
        else ImgTemp[i]=255;
    }
    else ImgTemp[i]=0;    
    }
    return ImgTemp;
}
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm nb \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	

for (int i = 0; i < 3; i++)//dilatation 3 fois
{
    memcpy(ImgIn,dilatation(ImgIn,nTaille,nW),nTaille);
}



for (int j = 0; j< 6; j++)//Erosion 6 fois
{
    memcpy(ImgIn,erosion(ImgIn,nTaille,nW),nTaille);
}

for (int i = 0; i < 3; i++)//dilatation 3 fois
{
    memcpy(ImgIn,dilatation(ImgIn,nTaille,nW),nTaille);
}



   ecrire_image_pgm(cNomImgEcrite, ImgIn,  nH, nW);
   free(ImgIn);

   return 1;
}
