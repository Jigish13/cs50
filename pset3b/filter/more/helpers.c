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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // TODO:
    // Make a copy of the original img and create a tmp img
    // Add a border of one black pixel around the tmp img
    // Eg: If the original img is of 3*3 size then the tmp img will be 5*5

    int newHeight = height + 2;
    int newWidth = width + 2;
    RGBTRIPLE tmpImage[newHeight][newWidth];

    // Black boundary at the beginning of the tmp img
    for (int first = 0, k = 0; k < newWidth; k++)
    {
        tmpImage[first][k].rgbtBlue = 0;
        tmpImage[first][k].rgbtGreen = 0;
        tmpImage[first][k].rgbtRed = 0;
    }

    for (int i = 0; i < height; i++)
    {
        // Write first black pixel to tmp img each time row is started
        tmpImage[i + 1][0].rgbtBlue = 0;
        tmpImage[i + 1][0].rgbtGreen = 0;
        tmpImage[i + 1][0].rgbtRed = 0;

        for (int j = 0; j < width; j++)
        {
            tmpImage[i + 1][j + 1] = image[i][j];
        }

        // Write last black pixel to tmp img each time row is ended
        tmpImage[i + 1][newWidth - 1].rgbtBlue = 0;
        tmpImage[i + 1][newWidth - 1].rgbtGreen = 0;
        tmpImage[i + 1][newWidth - 1].rgbtRed = 0;
    }

    // Black boundary at the end of the tmp img
    for (int last = newHeight - 1, z = 0; z < newWidth; z++)
    {
        tmpImage[last][z].rgbtBlue = 0;
        tmpImage[last][z].rgbtGreen = 0;
        tmpImage[last][z].rgbtRed = 0;
    }

    // Declare and initialise statically convolved matrices or kernals:
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    int blueGX, blueGY, greenGX, greenGY, redGX, redGY;
    int edgeBlue, edgeGreen, edgeRed;
    RGBTRIPLE neighbouringPixels[3][3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // For each pixel get neighbouring pixels
            for (int x = i, r = 0; x < i + 3; x++, r++)
            {
                for (int y = j, c = 0; y < j + 3; y++, c++)
                {
                    neighbouringPixels[r][c] = tmpImage[x][y];
                }
            }

            // Compute 2 weighted sums for r,g,b color values of pixels
            blueGX = 0, blueGY = 0, greenGX = 0, greenGY = 0, redGX = 0, redGY = 0;
            for (int p = 0; p < 3; p++)
            {
                for (int q = 0; q < 3; q++)
                {
                    blueGX = neighbouringPixels[p][q].rgbtBlue * Gx[p][q] + blueGX;
                    blueGY = neighbouringPixels[p][q].rgbtBlue * Gy[p][q] + blueGY;

                    greenGX = neighbouringPixels[p][q].rgbtGreen * Gx[p][q] + greenGX;
                    greenGY = neighbouringPixels[p][q].rgbtGreen * Gy[p][q] + greenGY;

                    redGX = neighbouringPixels[p][q].rgbtRed * Gx[p][q] + redGX;
                    redGY = neighbouringPixels[p][q].rgbtRed * Gy[p][q] + redGY;
                }
            }

            edgeBlue = round(sqrt((float)(blueGX * blueGX + blueGY * blueGY)));
            edgeGreen = round(sqrt((float)(greenGX * greenGX + greenGY * greenGY)));
            edgeRed = round(sqrt((float)(redGX * redGX + redGY * redGY)));

            if (edgeBlue > 255 || edgeBlue < 0)
            {
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = 0;
                }
            }
            else
            {
                image[i][j].rgbtBlue = edgeBlue;
            }

            if (edgeGreen > 255 || edgeGreen < 0)
            {
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = 0;
                }
            }
            else
            {
                image[i][j].rgbtGreen = edgeGreen;
            }

            if (edgeRed > 255 || edgeRed < 0)
            {
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = 0;
                }
            }
            else
            {
                image[i][j].rgbtRed = edgeRed;
            }
        }
    }

}
