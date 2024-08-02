#include <stdio.h>

int main(void) {

    int numbers[] = {1, 50, 100, 200, 210, 5, 85};
    int num;
    printf("number: ");
    scanf("%d", &num); /* prompt user for number to search for*/

    for (int i=0; i<7; i++) {
        if(num == numbers[i]) {
            printf("found");
            return 0;
        }
    }
    printf("not found");
    return 1;

}