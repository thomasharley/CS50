#include <stdio.h>
#include <math.h>

int main(void) {

    long x, y;

    printf("Enter x: ");
    scanf("%li", &x);

    printf("Enter y: ");
    scanf("%li", &y);

    double z = (double) x / (double) y;
    printf("%.20f\n", z); 

    return 0; 
}