#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[]){
    //Checking for exact paramters
    if (argc != 4){
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    int multiplier = atoi(argv[1]);

    if (multiplier > 100 || multiplier <= 0){
        printf("Number must be positive and less than 100");
    }

    char* infile = argv[2];
    char* outfile = argv[3];
    //Opening file to process
    FILE* oldimg = fopen(infile, "r");

    if (oldimg == NULL){
        printf("Cannot open %s.\n", infile);
        return 2;
    }

    FILE* newimg = fopen(outfile, "w");
    if (newimg == NULL){
        fclose(oldimg);
        fprintf(stderr, "Cannot create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, oldimg);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, oldimg);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0){
        fclose(newimg);
        fclose(oldimg);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    int old_w, old_h, padding_old, padding_new;
    old_w = bi.biWidth;
    old_h = bi.biHeight;
    bi.biWidth = old_w * multiplier;
    bi.biHeight = old_h * multiplier;

    padding_old = (4 - (old_w * sizeof(RGBTRIPLE)) % 4) % 4;
    padding_new =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding_new) * abs(bi.biHeight);
    bf.bfSize = (bi.biSizeImage) + 54;

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, newimg);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, newimg);

    int old_h2 = abs(old_h);

    for (int i = 0; i < old_h2; i++){
        for (int l = 0; l < multiplier; l++){
            fseek(oldimg, (54 + ((old_w*3 + padding_old) * i)), SEEK_SET);
            for (int j = 0; j < old_w; j++){
                RGBTRIPLE temp;

                fread(&temp, sizeof(RGBTRIPLE), 1, oldimg);

                for (int m = 0; m < multiplier; m++)
                    fwrite(&temp, sizeof(RGBTRIPLE), 1, newimg);
            }
            for (int i1 = 0; i1 < padding_new; i1++)
                fputc(0x00, newimg);
        }
    }
    //Close both the files
    fclose(oldimg);
    fclose(newimg);
    return 0;
}