// Program to recover JPEG's from a forensic image.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // open input file
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // Intializing buffer of size 512 B to store a block
    BYTE *buffer = malloc(sizeof(BYTE) * 512);

    // array to store name of newly found JPEG file
    char fna[8];

    // It keeps track of how many images have been recovered from raw file
    int total_images = 0;

    // keeps the reference of the newly found JPEG to write a block of size 512 B
    FILE *img = NULL;

    // flag var to keep reference of newly found JPEG file
    int found = 0;

    // read block by block data into buffer from raw file
    while (fread(buffer, 512, 1, raw_file))
    {
        if (found)
        {
            // to make sure it's not a new img
            if (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0))
            {
                fwrite(buffer, 512, 1, img);
            }
        }

        // found a new JPEG with distinct header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close any open img file
            if (img)
            {
                fclose(img);
            }

            // it stores name of newly found JPEG in xxx.jpg fmt
            sprintf(fna, "%03i.jpg", total_images++);

            img = fopen(fna, "w");

            fwrite(buffer, 512, 1, img);

            found = 1;
        }
    }

    // close input file
    fclose(raw_file);

    // close outfile pointer
    fclose(img);

    // to avoid memory leak
    free(buffer);

    // success
    return 0;
}