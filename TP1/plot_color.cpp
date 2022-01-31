// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	
    std::ofstream color;
    color.open("color.dat");
    int tabR[256]={0};
    int tabG[256]={0};
    int tabB[256]={0};

   for (int i=0; i < nTaille3; i+=3)
    {
        tabR[ImgIn[i]]+=1;
        tabG[ImgIn[i+1]]+=1;
        tabB[ImgIn[i+2]]+=1;
    }
    for(int i=0;i<256;i++){
        color<<i<<" "<<tabR[i]<<" "<<tabG[i]<<" "<<tabB[i]<<std::endl;
    }
    
    color.close();
   free(ImgIn);
   return 1;
}
