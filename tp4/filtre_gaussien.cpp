#include <stdio.h>
#include "image_ppm.h"
#include "gauss.h"

int main(int argc,char * argv[]){

    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille,seuil,seuilB,seuilH;

    if(argc<3){
        printf("%s ImageIN ImageOUT mode(0 for normal ,1 for single seuil , 2 for double Seuil) \n",argv[0]);
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    if(argc==5) sscanf(argv[4], "%d", &seuil);
    if(argc==6){
        sscanf(argv[4], "%d", &seuilB);
        sscanf(argv[5], "%d", &seuilH);
    }
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    double kernel[5][5];
    calc_filter(kernel);
        for (int i = 0; i < nH; i++)
        for (int j = 0; j < nW; j++)
        {
            if(i<=1 || j<=1 || i>=nH-2 || j>=nW-2){
                ImgOut[i*nW+j] = ImgIn[i*nW+j];
            } else {
                double somme=0;
                for(int a=-2;a<3;a++){
                    for(int b=-2;b<3;b++){
                        somme+=((double)ImgIn[(i+a)*nW+j +b])*kernel[a+2][b+2];
                    }
                }
                ImgOut[i*nW+j] = (int) somme;
            }
        }

    
    for(int i=0;i<nTaille;i++) ImgIn[i]=ImgOut[i];

    if(argc==4){
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
                    ImgOut[i*nW+j]=(int)sqrt(gcarre);
                }
            }
        }
    }

    if(argc==5){
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
    }

    if(argc==6){
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
                    if((int)sqrt(gcarre)<=seuilB)ImgOut[i*nW+j]=0;
                    if((int)sqrt(gcarre)>=seuilH)ImgOut[i*nW+j]=255;
                    else ImgOut[i*nW+j]=ImgIn[i*nW+j];
                }
            }
        }
        for(int i=0;i<nTaille;i++) ImgIn[i]=ImgOut[i];

        for(int i = 0; i < nH; i++){
            for (int j = 0; j < nW; j++)
            {
                if(i==nH-1 || j==nW-1 || i==0 || j==0  || ImgIn[i*nW+j]==0 || ImgIn[i*nW+j]==255 ){
                    ImgOut[i*nW+j] = ImgIn[i*nW+j];
                }
                else{
                    if(ImgIn[i*nW+j -1]==255 || ImgIn[i*nW+j +1]==255 || ImgIn[(i+1)*nW+j -1]==255 || ImgIn[(i+1)*nW+j]==255 || ImgIn[(i+1)*nW+j +1]==255 ||
                    ImgIn[(i-1)*nW+j-1]==255 || ImgIn[(i-1)*nW+j]==255 || ImgIn[(i-1)*nW+j+1]==255) ImgOut[i*nW+j] =255;
                    else ImgOut[i*nW+j] = 0;

                }
            }
        }
    }
    

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    return 1;

}