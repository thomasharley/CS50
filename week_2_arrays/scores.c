#include <stdio.h>

const int n = 3; // number of test scores

float average(int array[]);

int main(void) {

    int scores[n];

    for(int count = 0; count < n; count++) {
        printf("Enter Score %i: ", count + 1);
        scanf("%i", &scores[count]);
    }

    printf("Average: %f\n", average(scores));

    return 0;
}

float average(int array[]) {

    int sum = 0;

    for(int count = 0; count < n; count++) {
        sum += array[count];
    }

    return (sum / 3.0);
}