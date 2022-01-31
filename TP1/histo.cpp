#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], fichierOut[250];
  int nH, nW, nTaille, S;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm HistoOut \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",fichierOut);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }

    int tab[256]={0};

    for (int i=0; i < nH; i++)
        for (int j=0; j < nW; j++)
        {
            tab[ImgIn[i*nW+j]]+=1;
        }

    free(ImgIn);
    std::ofstream myfile;
    myfile.open(fichierOut);
    for(int i=0;i<256;i++){
        myfile<<i<<" "<<tab[i]<<std::endl;
    }
    myfile.close();
   return 1;
}
