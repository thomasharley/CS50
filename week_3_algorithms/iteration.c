#include <stdio.h>

void draw(int n);

int main(void) {

    int height = 0;

    printf("Height: ");
    scanf("%i", &height);

    draw(height);
}

void draw(int n) {
    
    if(n<=0) { /* if nothing to draw */
        return;
    }

    draw(n-1); /* print pyramid of height n */
    for(int i=0; i<n; i++) { /* print one more row */
        printf("#");
    }
    printf("\n");
}