#include <stdio.h>
#include "main.h"
#include <stdlib.h>
// 2 bites, 4 bites at a time -> as memory 4 bytes on multiples of 4 etc. so too much unused memory >>???

int main(int argc, char *argv[])
{
    // loadfile
    if (argc == 1)
    {
        printf("Warning: No BMP filename entered\n");
        return 1;
    }
    FILE *image = fopen(argv[1], "rb");
    if (image == NULL)
    {
        printf("Warning: No such file or directory\n");
        return 1;
    }

    // obtain file l_size:
    long l_size;
    fseek(image, 0, SEEK_END);
    l_size = ftell(image);
    rewind(image);

    // allocating memory for buffer
    char *buffer = (char *)malloc(sizeof(char) * l_size);
    if (buffer == NULL)
    {
        printf("Memory allocation failed");
        fclose(image);
        return 1;
    }

    // reading file
    fread(buffer, sizeof(*buffer), l_size, image);
    puts("Array read successfully, contents: ");
    for (int n = 0; n < 4; ++n)
    {
        printf("%p\n", buffer[n]);
    }
    putchar('\n');

    // closing file & deallocating memory
    fclose(image);
    free(buffer);
    return 0;
}