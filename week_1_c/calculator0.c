#include <stdio.h>
#include <math.h>

int main(void) {

    /* Declaring variables */
    int x, y, z;
    
    /* Fetch inputs from user */
    printf("x: ");
    scanf("%i", &x);

    printf("y: ");
    scanf("%i", &y);

    z = x + y; /* Addition */

    printf("answer: %i\n", z); /* Print the answer */

}