// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn ImageOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *Y,*Cb,*Cr, *ImgOut;

    char nomSortieY[250];
    strcpy(nomSortieY,cNomImgLue);
    strcat(nomSortieY,"y.pgm");
    char nomSortieCb[250];
    strcpy(nomSortieCb,cNomImgLue);
    strcat(nomSortieCb,"Cb.pgm");
    char nomSortieCr[250];
    strcpy(nomSortieCr,cNomImgLue);
    strcat(nomSortieCr,"Cr.pgm");


    lire_nb_lignes_colonnes_image_pgm(nomSortieY, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(Y, OCTET, nTaille);
    lire_image_pgm(nomSortieY, Y, nH * nW);
    allocation_tableau(Cb, OCTET, nTaille);
    lire_image_pgm(nomSortieCb, Cb, nH * nW);
    allocation_tableau(Cr, OCTET, nTaille);
    lire_image_pgm(nomSortieCr, Cr, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille3);
    

    for (int i = 0; i < nTaille; i++)
    {
        ImgOut[i*3]=Y[i]+ (1.402)*(Cr[i]-128);
        ImgOut[i*3+2]=Y[i] +(Cb[i]-128)*(-0.34414) +(Cr[i] -128)*(-0.714414);
        ImgOut[i*3+1]=Y[i]+ (1.772)*(Cb[i]-128);
    }
    
    

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);

    free(Y);
    free(Cb);
    free(Cr);
    return 1;
}
