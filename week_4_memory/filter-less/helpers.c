#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double avgcolour;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            avgcolour = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = round(avgcolour);

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double sepiaRed, sepiaGreen, sepiaBlue;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            sepiaRed = (image[i][j].rgbtRed*0.393) + (image[i][j].rgbtBlue*0.189) + (image[i][j].rgbtGreen*0.769);
            sepiaGreen = (image[i][j].rgbtRed*0.349) + (image[i][j].rgbtBlue*0.168) + (image[i][j].rgbtGreen*0.686);
            sepiaBlue = (image[i][j].rgbtRed*0.272) + (image[i][j].rgbtBlue*0.131) + (image[i][j].rgbtGreen*0.534);

            if(round(sepiaRed)>255) {
                sepiaRed = 255;
            }
            if(round(sepiaGreen)>255) {
                sepiaGreen = 255;
            }
            if(round(sepiaBlue)>255) {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++) { /* going down columns */
        for(int j = 0; j < width/2; j++) { /* going across rows*/

            int tmpBlue = image[i][j].rgbtBlue;
            int tmpGreen = image[i][j].rgbtGreen;
            int tmpRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width-1-j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width-1-j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width-1-j].rgbtRed;

            image[i][width-1-j].rgbtBlue = tmpBlue;
            image[i][width-1-j].rgbtGreen = tmpGreen;
            image[i][width-1-j].rgbtRed = tmpRed;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* first we should create a copy of the image. */
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++) { /* going down columns */
        for(int j = 0; j < width; j++) { /* going across rows*/

            copy[i][j] = image[i][j];
        }
    }
    /* now we blur using the copied image as our reference */
    for(int i = 0; i < height; i++) { /* going down columns */
        for(int j = 0; j < width; j++) { /* going across rows*/

            double totalred = 0, totalgreen = 0, totalblue = 0;
            double avgred = 0, avggreen = 0, avgblue = 0;
            int count = 0;
            for(int y = i-1; y <= i+1; y++) {
                for(int z = j-1; z <= j+1; z++) {
                    if(z<0 || z>=width || y<0 || y>=height) {
                        /* represents an invalid pixel that we can't average value of */
                    }
                    else {
                        totalred = totalred + copy[y][z].rgbtRed;
                        totalgreen = totalgreen + copy[y][z].rgbtGreen;
                        totalblue = totalblue + copy[y][z].rgbtBlue;
                        count++; /* so we know how much to divide total by for average. */
                    }          
                }
            }
            /* average value to be assigned to pixel for each colour */
            avgred = totalred / (double)count;
            avggreen = totalgreen / (double)count;
            avgblue = totalblue / (double)count;

            /* assigning calculated values to pixel */
            image[i][j].rgbtRed = round(avgred);
            image[i][j].rgbtGreen = round(avggreen);
            image[i][j].rgbtBlue = round(avgblue);

            /* loop to next pixel */
        }
    }
    

    return;
}
