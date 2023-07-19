/* using long integers */

#include <stdio.h>
#include <math.h>

int main(void) {

    /* Declaring variables */
    long x, y, z;
    
    /* Fetch inputs from user */
    printf("x: ");
    scanf("%li", &x);

    printf("y: ");
    scanf("%li", &y);

    z = x + y; /* Addition */

    printf("answer: %li\n", z); /* Print the answer */

}