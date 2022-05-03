#include <stdio.h>
#include <stdlib.h>
#include "main.h"

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

void header_reader(FILE *file)
{
    fread(&fileHeader.bfType, 1, sizeof(WORD), file);
    fread(&fileHeader.bfSize, 1, sizeof(DWORD), file);
    fread(&fileHeader.bfReserved1, 1, sizeof(WORD), file);
    fread(&fileHeader.bfReserved2, 1, sizeof(WORD), file);
    fread(&fileHeader.bfOffBits, 1, sizeof(DWORD), file);
}

void info_reader(FILE *file)
{
    fread(&infoHeader.biSize, 1, sizeof(DWORD), file);
    fread(&infoHeader.biWidth, 1, sizeof(LONG), file);
    fread(&infoHeader.biHeight, 1, sizeof(LONG), file);
    fread(&infoHeader.biPlanes, 1, sizeof(WORD), file);
    fread(&infoHeader.biBitCount, 1, sizeof(WORD), file);
    fread(&infoHeader.biCompression, 1, sizeof(DWORD), file);
    fread(&infoHeader.biSizeImage, 1, sizeof(DWORD), file);
    fread(&infoHeader.biXPelsPerMeter, 1, sizeof(LONG), file);
    fread(&infoHeader.biYPelsPerMeter, 1, sizeof(LONG), file);
    fread(&infoHeader.biClrUsed, 1, sizeof(DWORD), file);
    fread(&infoHeader.biClrImportant, 1, sizeof(DWORD), file);
}

void BMP_header_print()
{
    printf("\nBITMAPFILEHEADER:\n");
    printf("   bfType：               0x%x (BM)\n", fileHeader.bfType);
    printf("   bfSize：               %d\n", fileHeader.bfSize);        // 4 byte
    printf("   bfReserved1：          0x%x\n", fileHeader.bfReserved1); // 2 byte
    printf("   bfReserved2：          0x%x\n", fileHeader.bfReserved2); // 2 byte
    printf("   bfOffBits:             %d\n", fileHeader.bfOffBits);     // 4 bytes
}

void BMP_info_print()
{
    printf("\nBITMAPINFOHEADER:\n");
    printf("   biSize:                %d\n", infoHeader.biSize);
    printf("   biWidth:               %d\n", infoHeader.biWidth);
    printf("   biHeight:              %d\n", infoHeader.biHeight);
    printf("   biPlanes:              %d\n", infoHeader.biPlanes);
    printf("   biBitCount:            %d\n", infoHeader.biBitCount);
    printf("   biCompression:         %d\n", infoHeader.biCompression);
    printf("   biSizeImage:           %d\n", infoHeader.biSizeImage);
    printf("   biXPelsPerMeter:       %d\n", infoHeader.biXPelsPerMeter);
    printf("   biYPelsPerMeter:       %d\n", infoHeader.biYPelsPerMeter);
    printf("   biClrUsed:             %d\n", infoHeader.biClrUsed);
    printf("   biClrImportant:        %d\n", infoHeader.biClrImportant);
}

void RGB_histogram() // for grade 4 -> to complete
{
    // Pixel array is stored as a sequence of rows. Each row has length equal to:
    int pixel_array_len = (((infoHeader.biBitCount * infoHeader.biWidth) + 31) / 32) * 4;
}

// $ ./program PATH-TO-INPUT-BMP-FILE PATH-TO-OUTPUT-BMP-FILE
int main(int argc, char *argv[])
{
    FILE *file;
    uint16_t bfType;
    file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Error: File cannot be opened.\n");
        return 1;
    }
    header_reader(file);
    BMP_header_print(fileHeader);
    info_reader(file);
    BMP_info_print(infoHeader);

    if (!(infoHeader.biCompression == 0 && infoHeader.biBitCount == 24))
    {
        printf("Unsuported type for RGB hisotgram.\n");
        return 1;
    }

    // closing bmp file
    fclose(file);
}
