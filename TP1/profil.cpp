#include <stdio.h>
#include "image_ppm.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250] ,fichierOut[250];
  int nH, nW, nTaille,num,lc;
  
  if (argc <4) 
     {
       printf("Usage: ImageIn.pgm lig1/col2 num fichierOut\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%d",&lc);
   sscanf (argv[3],"%d",&num);
   if(argc==5) sscanf(argv[4],"%s",fichierOut);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);


    if(argc==4){
    if(lc==1){
        if(num>nW){std::cout<<"num trop grand"<<std::endl;exit(1);}
        int i=num;
        for(int j=0;j<nH;j++){
            std::cout<<j<<" "<<int(ImgIn[i*nW+j])<<std::endl;
        }
    }
    else if(lc==2){
        if(num>nH){std::cout<<"num trop grand"<<std::endl;exit(1);}
        int j=num;
        for(int i=0;i<nW;i++){
            std::cout<<i<<" "<<int(ImgIn[i*nW+j])<<std::endl;
        }
    }
    }



    else{
        std::ofstream myfile;
        myfile.open(fichierOut);

        if(lc==1){
            if(num>nW){std::cout<<"num trop grand"<<std::endl;exit(1);}
            int i=num;
            for(int j=0;j<nW;j++){
                myfile<<j<<" "<<int(ImgIn[i*nW+j])<<std::endl;
            }
        }
        else if(lc==2){
            if(num>nH){std::cout<<"num trop grand"<<std::endl;exit(1);}
            int j=num;
            for(int i=0;i<nH;i++){
                myfile<<i<<" "<<int(ImgIn[i*nW+j])<<std::endl;
            }
        }
        myfile.close();
    }
    free(ImgIn);
   return 1;
}
