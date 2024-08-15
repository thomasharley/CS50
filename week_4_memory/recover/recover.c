#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
 
int main(int argc, char *argv[])
{
    /* check number of arguments correct*/
    if(argc != 2) {
        printf("Usage: ./recover infile");
        return 1;
    }

    /* check if we can read file */
    FILE *infile = fopen(argv[1], "rb");
    if (infile == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    FILE *currentFile = NULL;

    int jpgcount = 0; /* start the count */

    /* declare the filename variable */
    char *filename = malloc(8*sizeof(char)); /* 256 bits */
    if(filename == NULL) {
        fclose(infile);
        printf("Error allocating memory.\n");
        return 1;
    }

    /* buffer for the data */
    uint8_t buffer[512];

    while(fread(buffer, 1, 512, infile) == 512) {
        
        /* check for the matching 4 bytes */
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            
            /* if file already exists, close it */
            if(currentFile != NULL) {
                fclose(currentFile);
            }

            sprintf(filename, "images/%03i.jpg", jpgcount); /* name the file */

            currentFile = fopen(filename, "wb"); /* create file */
            if(currentFile == NULL) {
                free(filename);
                fclose(infile);
                printf("Could not create file %s.\n, filename");
                return 1;
            }

            jpgcount++; /* iterate counter */
        }
        /* if file exists, write to it */
        if(currentFile != NULL) {
            fwrite(buffer, sizeof(uint8_t), 512, currentFile); /* write 512 bytes (size of jpg) */
        }

    }
    
    /* tidy up, free memory, close files */
    if(currentFile != NULL) {
        fclose(currentFile);
    }

    fclose(infile);
    free(filename);

    return 0;
    

}