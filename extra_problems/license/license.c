#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char (*plates)[7] = malloc(8*sizeof(buffer));
    if(plates[7]==NULL) {
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");

    int idx = 0;

    while (fread(&buffer, sizeof(buffer), 1, infile) != 0)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        strcpy(plates[idx], buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    free(plates);
}
