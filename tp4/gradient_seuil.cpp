#include <stdio.h>
#include "image_ppm.h"

int main(int argc,char * argv[]){

    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille,seuil;

    if(argc!=4){
        printf("%s ImageIN ImageOUT seuil",argv[0]);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &seuil);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i = 0; i < nH; i++){
        for (int j = 0; j < nW; j++)
        {
            if(i==nH-1 || j==nW-1){
                ImgOut[i*nW+j] = ImgIn[i*nW+j];
            } 
            else {
                int gx= ImgIn[i*nW+j]*(-1) + ImgIn[i*nW+j+1];
                int gy=ImgIn[i*nW+j]*(-1) + ImgIn[(i+1)*nW+j];
                int gcarre= gx*gx + gy*gy;
                if((int)sqrt(gcarre)<seuil)ImgOut[i*nW+j]=0;
                else ImgOut[i*nW+j]=255;
            }
        }
    }
    
    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    return 1;

}