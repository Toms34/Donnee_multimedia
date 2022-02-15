// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageOut.ppm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;
    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    for (int i = 0; i < nTaille3; i+=3)
    {
        int R = i;
        int G = i+1;
        int B = i+2;
        ImgOut[R] = (ImgIn[R]+ImgIn[R+3]+ImgIn[R-3]+ImgIn[R+nW*3]+ImgIn[R-nW*3])/5;
        ImgOut[G] = (ImgIn[G]+ImgIn[G+3]+ImgIn[G-3]+ImgIn[G+nW*3]+ImgIn[G-nW*3])/5;
        ImgOut[B] = (ImgIn[B]+ImgIn[B+3]+ImgIn[B-3]+ImgIn[B+nW*3]+ImgIn[B-nW*3])/5;
    }
    

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    return 1;
}
