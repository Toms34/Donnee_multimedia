// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
int eq(int x,int S1,int S2,int number){
    printf("here \n");
    int t=floor((x-S1)/(S2-S1));
    if (number==1) return (int) pow(t,3)*255;
    if (number==2) return ((3*t*t) - (2*t*t*t))*255;
    else return (int) floor(sin(t*M_PI/2)*255);
}   
int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S1, S2, number;
    
    if (argc <5) 
        {
        printf("Usage: ImageIn.pgm ImageOut.pgm Seuil1 Seuil2 1-3 \n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);
    sscanf (argv[3],"%d",&S1);
    sscanf (argv[4],"%d",&S2);
    sscanf (argv[5],"%d",&number);
    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
        
    //   for (int i=0; i < nTaille; i++)
    // {
    //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
    //  }

    for (int i = 0; i < nTaille; i++)
    {
        ImgOut[i]=eq(ImgIn[i],S1,S2,number);
    }
    



   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}