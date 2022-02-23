// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
    char imgIn1[250], cNomImgEcrite[250], imgIn2[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Usage: ImageIn.ppm ImageIN2.ppm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", imgIn1);
    sscanf(argv[2], "%s", imgIn2);

    OCTET *ImgIn1,*ImgIn2, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(imgIn1, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn1, OCTET, nTaille);
    allocation_tableau(ImgIn2, OCTET, nTaille);

    lire_image_pgm(imgIn1, ImgIn1, nH * nW);
    lire_image_pgm(imgIn2, ImgIn2, nH * nW);

    int a=0;

    for (int i = 0; i < nTaille; i++)
    {
        a+=pow(ImgIn1[i]-ImgIn2[i],2);
    }
    a=a/nTaille;
    printf("erreur quadra : %i \n",a);
    return 1;
}
