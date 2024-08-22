#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int convert(char *input);

int main(void)
{
    
    char *input = malloc(8);
    printf("Enter a positive integer: ");
    scanf("%s", input);

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));

    free(input);
}

int convert(char *input)
{
    if(strlen(input)==0) {
        return 0;
    }

    int i = (input[strlen(input) - 1] - '0');

    char *input_new = malloc(8);

    strncpy(input_new, input, strlen(input)-1);
    input_new[strlen(input)-1] = '\0';

    return i + (10 * convert(input_new));

}