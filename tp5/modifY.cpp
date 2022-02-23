// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille,k;

    if (argc != 4)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm k \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%i", &k);

    OCTET *Y,*ImgOut;


    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(Y, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, Y, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);
    

    for (int i = 0; i < nTaille; i++)
    {   
        ImgOut[i]=Y[i]+k;
        if(ImgOut[i]>255) ImgOut[i]=255;
        if(ImgOut[i]<0) ImgOut[i]=0;
    }
    
    

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(Y);
    return 1;
}
