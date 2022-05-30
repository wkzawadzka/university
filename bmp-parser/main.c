#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/* Weronika Zawadzka 151943 & Eliza Czaplicka 151963 */
// ANNOTADED

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;
unsigned char *bitmap = 0;
float blue[16] = {0}; // initializing a list of length 16 with all 0: [0,0,0,0,0...0]
float red[16] = {0};
float green[16] = {0};
float blue_c = 0;
float green_c = 0;
float red_c = 0;
// all floats so we can multiply divide etc. them (needed with percentges later)

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
    printf("   bfSize：               %d\n", fileHeader.bfSize);
    printf("   bfReserved1：          0x%x\n", fileHeader.bfReserved1);
    printf("   bfReserved2：          0x%x\n", fileHeader.bfReserved2);
    printf("   bfOffBits:             %d\n", fileHeader.bfOffBits);
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

int get_value(int value) // serach for correct place in list (connected with percentages)
{
    int i;
    int iteration = 0;
    for (i = 0; i <= 240; i += 16)
    {
        if ((i <= value) && (value <= i + 15))
        {
            return iteration;
        }
        iteration++;
    }
}

void histogram(int B, int G, int R)
{
    red[get_value(R)]++;
    green[get_value(G)]++;
    blue[get_value(B)]++;
    red_c++;
    green_c++;
    blue_c++;
}

void RGB_reader(FILE *file)
{
    int size = ((infoHeader.biWidth * infoHeader.biBitCount + 31) / 32) * 4 * infoHeader.biHeight; 
    // first part is from exercise pdf * height to get the size
    int padding = infoHeader.biWidth % 4; // actually here it gives nothing as width is always mutiple of four for given bmp files
    bitmap = malloc(size);
    fread(bitmap, 1, size, file); // read one by one to the end of RGB section of size size

    for (int row = infoHeader.biHeight - 1; row >= 0; row--)
    {
        for (int col = 0; col < infoHeader.biWidth; col++)
        {
            int pos = (row * infoHeader.biWidth + col) * 3 + row * padding;
            histogram(bitmap[pos], bitmap[pos + 1], bitmap[pos + 2]);
        }
    }
}

void print_histogram()
{
    printf("\nBlue:\n");
    int i = 0;
    int j;
    float percentage;
    for (j = 0; j < 16; j++)
    {
        percentage = (blue[j] / blue_c) * 100;
        printf("   %d-%d: %.2f%%\n", i, i + 15, percentage);
        i += 16;
    }
    i = 0;
    printf("\nGreen:\n");
    for (j = 0; j < 16; j++)
    {
        percentage = (green[j] / green_c) * 100;
        printf("   %d-%d: %.2f%%\n", i, i + 15, percentage);
        i += 16;
    }
    i = 0;
    printf("\nRed:\n");
    for (j = 0; j < 16; j++)
    {
        percentage = (red[j] / red_c) * 100;
        printf("   %d-%d: %.2f%%\n", i, i + 15, percentage);
        i += 16;
    }
}

int main(int argc, char *argv[])
{
    FILE *file;
    file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        printf("Error: File cannot be opened.\n");
        return 1;
    }
    // 3.0 header
    header_reader(file);
    if (fileHeader.bfType != 0x4D42) // 0x4D42 means bitmap
    {
        printf("Not a BMP file.");
        return 1;
    }
    BMP_header_print(fileHeader);

    // 3.5 info header
    info_reader(file);
    BMP_info_print(infoHeader);

    // 4.0 histogram
    if (!(infoHeader.biCompression == 0 && infoHeader.biBitCount == 24))
    {
        printf("Unsuported type for RGB histogram.\n");
        return 1;
    }
    RGB_reader(file);
    print_histogram();

    fclose(file);
    free(bitmap);
}
// oh i forgot about return 0; at the end but it works :O
