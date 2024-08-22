#include <stdio.h>
#include <stdbool.h>

int main(void) {

    int min, max;
    bool prime = true; /* prime true be default */

    printf("Minimum: ");
    scanf("%d", &min);

    printf("Maximum: ");
    scanf("%d", &max);

    for (int i=min; i<max; i++) {

        for (int j=2; j<i; j++) {

            if (i % j == 0) {

                prime = false; /* prime boolean set to false if divisor found */
                break;
            }
        }

        if(prime && i != 1) {
            printf("%d\n", i);
        }
        prime = true; /* set default to true */

    }

}