// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, N,histo[256]={0};
    int treshold,var_max,sum,sumb,q1,q2,y1,y2;
    treshold=0;
    var_max=0;
    sum=0;
    sumb=0;
    q1=0;
    q2=0;
    y1=0;
    y2=0;
    if (argc !=3) 
        {
        printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
        exit (1) ;
        }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    N = nH * nW;
        
    allocation_tableau(ImgIn, OCTET, N);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, N);
        
    for (int i = 0; i < N; i++)
    {
        histo[ImgIn[i]]++;
    }
    for (int i = 0; i < 256; i++)
    {
        sum+=i * histo[i];
    }
    for (int i = 0; i < 256; i++)
    {
        q1+=histo[i];
        if(q1==0) continue;
        q2=N-q1;

        sumb+=i*histo[i];
        y1=sumb/q1;
        y2=(sum-sumb)/q2;
        int var=q1 * q2 * (y1 - y2) * (y1 - y2);
        
        if(var>var_max){
            var_max=var;
            treshold=i;
        }

    }
    for(int i=0;i<N;i++){
        if(ImgIn[i]>treshold) ImgOut[i]=255;
        else ImgOut[i]=0;
    }
    

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}