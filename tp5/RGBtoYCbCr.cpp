// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut,*ImgOut1,*ImgOut2;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgOut1, OCTET, nTaille);
    allocation_tableau(ImgOut2, OCTET, nTaille);


    for (int i = 0; i < nTaille; i++)
    {
        ImgOut[i]=ImgIn[i*3]*0.299 + ImgIn[i*3 +1]*0.587 + ImgIn[i*3+2]*0.114 ;
        ImgOut1[i]=ImgIn[i*3]*(-0.1687) + ImgIn[i*3 +1]*(-0.3313) + ImgIn[i*3+2]*0.5 + 128;
        ImgOut2[i]=ImgIn[i*3]*0.5 + ImgIn[i*3 +1]*(-0.4187) + ImgIn[i*3+2]*(-0.0813) +128 ;
    }
    
    char nomSortieY[250];
    strcpy(nomSortieY,cNomImgEcrite);
    strcat(nomSortieY,"y.pgm");
    char nomSortieCb[250];
    strcpy(nomSortieCb,cNomImgEcrite);
    strcat(nomSortieCb,"Cb.pgm");
    char nomSortieCr[250];
    strcpy(nomSortieCr,cNomImgEcrite);
    strcat(nomSortieCr,"Cr.pgm");

    ecrire_image_pgm(nomSortieY, ImgOut, nH, nW);
    ecrire_image_pgm(nomSortieCb, ImgOut1, nH, nW);
    ecrire_image_pgm(nomSortieCr, ImgOut2, nH, nW);

    free(ImgIn);
    return 1;
}
