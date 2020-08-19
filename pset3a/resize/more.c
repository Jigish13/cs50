// Enlarges & Shrinks a BMP file by a floating point scale-up factor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp.h"

/*
TODO:
1. Enlarge if f > 1
2. Shrink if f < 1
- if iteration mod N == 0 then skip that pixel nd row acc
*/

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // remember scale up factor
    float f;

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if ((argv[1][i] >= '0' && argv[1][i] <= '9') || (argv[1][i] == '.'))
        {
            // %*s is used to skip a word
            sscanf(argv[1], "%f", &f);

            printf("F = %f\n", f);

            // ensure proper usage
            if (!(f > 0.0 && f <= 100.0))
            {
                fprintf(stderr, "Usage: ./resize n infile outfile\n");
                return 1;
            }
        }
        else
        {
            fprintf(stderr, "Usage: ./resize f infile outfile\n");
            return 1;
        }
    }

    if (f < 1.0)
    {
        // Shrink the given image by factor f or skip every nth pixel and nth row to downsize image
        int n = round(1 / f);
        printf("N = %d\n", n);

        // remember filenames
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

        //printf("BEFORE:\n PADDING = %d\n WIDTH = %d\n HEIGHT = %d\n IMG SIZE = %d\n FILE SIZE = %d\n", infile_padding, bi.biWidth, bi.biHeight, bi.biSizeImage, bf.bfSize);

        // Determine width, height and padding required by outfile.
        bi.biWidth = bi.biWidth / n;
        bi.biHeight = bi.biHeight / n;
        int outfile_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        // Update outfile image size that includes width, height, and padding.
        bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + outfile_padding) * abs(bi.biHeight);

        // Update outfile file size.
        bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;

        //printf("AFTER:\n PADDING = %d\n WIDTH = %d\n HEIGHT = %d\n IMG SIZE = %d\n FILE SIZE = %d\n", outfile_padding, bi.biWidth, bi.biHeight, bi.biSizeImage, bf.bfSize);

        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        // iterate over infile's scanlines
        // infileHeight = 12, infileWidth = 12, n = 4

        for (int i = 0, infileHeight = abs(bi.biHeight) * n, infileWidth = bi.biWidth * n; i < infileHeight; i++)
        {
            if (i % n == 0)
            {
                printf("\n\nI = %d\n", i);

                // Printing position of pointer
                printf("%ld\n", ftell(inptr));

                // move forward inptr to the next required scanline in infile from starting position
                if (i != 0)
                {
                    fseek(inptr, i * (infileWidth * 3 + infile_padding) + 54, SEEK_SET);
                }

                printf("%ld\n", ftell(inptr));

                // iterate over pixels in scanline
                for (int j = 0; j < infileWidth; j++)
                {
                    if (j % n == 0)
                    {
                        // temporary storage
                        RGBTRIPLE triple;

                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                        printf("TRIPLE: B = %hhu G = %hhu R = %hhu\n", triple.rgbtBlue, triple.rgbtGreen, triple.rgbtRed);

                        // write RGB triple into outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                        // move forward inptr by n - 1 pixels
                        fseek(inptr, (n - 1) * 3, SEEK_CUR);

                        printf("J = %d, INPTR = %ld\n", j, ftell(inptr));
                    }
                }

                // then add it back (to demonstrate how)
                for (int k = 0; k < outfile_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }

        // move forward inptr by n - 1 pixels
        //fseek(inptr, 54, SEEK_SET);
        //printf("LAST pOS = %ld\n\n", ftell(inptr));

        // close infile
        fclose(inptr);

        // close outfile
        fclose(outptr);

        // success
        return 0;
    }
    else
    {
        // Enlarge the given image
        int n = round(f);
        printf("N = %i\n", n);

        // remember filenames
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
}