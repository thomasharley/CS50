#include <stdio.h>
#include <math.h>

int main(void) {

    int x;
    printf("What's x? ");
    scanf("%i", &x);
    
    int y;
    printf("What's y? ");
    scanf("%i", &y);

    if (x < y) {
        printf("x is less than y \n");
    }
    else if (x > y) {
        printf("x is greater than y \n");
    }
    else if (x == y) {
        printf("x is the same as y \n");
    }

    return 0;
}