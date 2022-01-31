// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc <4) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm seuil1 seuil2 ... \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

    //tableau de la taille du nombre de Seuil = argc - nom_prog - imageIN - imageOUT
    int nbSeuil=argc-3;
    int Seuil[nbSeuil];
    for(int i=0;i<nbSeuil;i++) {
        Seuil[i]=atoi(argv[3+i]);
    }
    
   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
    //valeur a mettre si<Seuil
    int tab[nbSeuil];
    for(int i=0;i<nbSeuil;i++) tab[i]=i*floor(255/(nbSeuil-1));

    for (int x=0; x < nH; x++){
        for (int y=0; y < nW; y++)
        {
            for(int i=0;i<nbSeuil;i++) 
            {
                if ( ImgIn[x*nW+y] < Seuil[i]) {
                    ImgOut[x*nW+y]=tab[i];
                    i=nbSeuil;
                }
            }
        }
    }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}