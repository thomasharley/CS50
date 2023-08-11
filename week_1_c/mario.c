#include <stdio.h>

int get_size(void);
void print_grid(int size);

int main(void) {

    int n;
    // get size of grid
    n = get_size();
    // print grid of bricks
    print_grid(n);

}

// modularisation or abstraction.S
int get_size(void) {

    int size;
    do { // useful to get input from user with certain criteria.
        printf("Size: ");
        scanf("%i", &size);
    }
    while (size<1);

    return size;
}

void print_grid(int size) {

    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            printf("#");
        }
        printf("\n");
    }
}