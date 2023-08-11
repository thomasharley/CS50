#include <stdio.h>
#include <math.h>

// program to calculate population of llamas, every year n / 3 new llamas are born.
// n / 4 llamas pass way. n is the population size

int main(void) {

    int pop_start = 0; 
    int pop_end = 0;

    do {
        printf("Enter the starting population: ");
        scanf("%i", &pop_start);
    }
    while(pop_start < 9);

    do {
        printf("Enter the ending population: ");
        scanf("%i", &pop_end);
    }
    while(pop_end < pop_start);

    int years = 0; // keep track of years

    while(pop_start < pop_end) {
        pop_start = pop_start + (pop_start / 3) - (pop_start / 4); // combination of plus n/3 and minus n/4.
        years++;
    }

    printf("Years: %i\n", years);

    return 0;

    // problem was stupid - for some reason in the actual solution the population
    // was stored as an int throughout, which meant truncation occurred. I was being more accurate,
    // using a float.

}