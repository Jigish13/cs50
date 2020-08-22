#include <math.h>
#include <stdio.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int newImgPixelVal;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newImgPixelVal = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = newImgPixelVal;
            image[i][j].rgbtGreen = newImgPixelVal;
            image[i][j].rgbtRed = newImgPixelVal;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255 || sepiaRed < 0)
            {
                if (sepiaRed > 255)
                {
                    sepiaRed = 255;
                }
                else
                {
                    sepiaRed = 0;
                }
            }

            if (sepiaGreen > 255 || sepiaGreen < 0)
            {
                if (sepiaGreen > 255)
                {
                    sepiaGreen = 255;
                }
                else
                {
                    sepiaGreen = 0;
                }
            }

            if (sepiaBlue > 255 || sepiaBlue < 0)
            {
                if (sepiaBlue > 255)
                {
                    sepiaBlue = 255;
                }
                else
                {
                    sepiaBlue = 0;
                }
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE rowPixels[width];
    for (int i = 0, c; i < height; i++)
    {
        // Read pixels in array in reverse order row wise
        c = 0;
        for (int j = width - 1; j >= 0; j--)
        {
            rowPixels[c++] = image[i][j];
        }

        // Write pixels of array in original 2D image array
        for (int k = 0; k < width; k++)
        {
            image[i][k] = rowPixels[k];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int neighboringPixels, dist;
    int blurRed, blurGreen, blurBlue;

    // TODO:
    // Create a copy of original img
    // Take neighbouring pixels of tmp img and modify them
    // Write the resulting values to original img

    RGBTRIPLE tmpImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmpImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            neighboringPixels = 0;
            blurRed = 0, blurGreen = 0, blurBlue = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = 0; y <= j + 1; y++)
                {
                    if (x != height && y != width && x >= 0)
                    {
                        dist = (i - x) * (i - x) + (j - y) * (j - y);
                        if (dist == 0 || dist == 1 || dist == 2)
                        {
                            blurBlue = tmpImage[x][y].rgbtBlue + blurBlue;
                            blurRed = tmpImage[x][y].rgbtRed + blurRed;
                            blurGreen = tmpImage[x][y].rgbtGreen + blurGreen;
                            neighboringPixels++;
                        }
                    }
                }
            }
            image[i][j].rgbtBlue = round((float)blurBlue / neighboringPixels);
            image[i][j].rgbtGreen = round((float)blurGreen / neighboringPixels);
            image[i][j].rgbtRed = round((float)blurRed / neighboringPixels);
        }
    }
}
