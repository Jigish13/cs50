// Enlarges a BMP file
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4 || !(atoi(argv[1]) >= 1 && atoi(argv[1]) <= 100))
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and scale up factor
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine infile padding for scanlines
    int infile_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Determine width, height and padding required by outfile.
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    int outfile_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Update outfile image size that includes width, height, and padding.
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + outfile_padding) * abs(bi.biHeight);

    // Update outfile file size.
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, infileHeight = abs(bi.biHeight) / n, infileWidth = bi.biWidth / n; i < infileHeight; i++)
    {
        for (int c = 0; c < n; c++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < infileWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile | Scaling up horizontally
                for (int k = 0; k < n; k++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // reset infile ptr back to the first byte of first pixel of that scanline
            fseek(inptr, -(infileWidth * 3), SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outfile_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // move infile pointer to next scanline
        fseek(inptr, infile_padding + (infileWidth * 3), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
