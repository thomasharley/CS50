#include <stdio.h>
#include <string.h>
#include <math.h>

float compute_grade(char test[]);

int main(void) {

    char TEXT[1000];

    printf("Text: ");
    scanf("%[^\n]s", TEXT);

    float index = compute_grade(TEXT);
    //printf("%f\n", index);
    int rounded_index = round(index);

    if (rounded_index <= 0) {
        printf("Before Grade 1");
    }
    else if (rounded_index >= 16) {
        printf("Grade 16+");
    }
    else {
        printf("Grade %i", rounded_index);
    }
}

float compute_grade(char text[]) {

    float index = 0; 
    float letter_count = 0, sentence_count = 0, word_count = 0;

    for (int i = 0, len = strlen(text); i<=len; i++) {
        if(text[i] == '.' || text[i] == '?' || text[i] == '!') {
            sentence_count++;
        }
        if(90 >= text[i] && text[i] >= 65) {
            letter_count++;
        }
        if(122 >= text[i] && text[i] >= 97) {
            letter_count++;
        }
        if(text[i] == ' ' || text[i] == '\0') {
            word_count++;
        }
    }

    //printf("%f\n", sentence_count);
    //printf("%f\n", letter_count);
    //printf("%f\n", word_count);

    float L = (letter_count/word_count)*100;
    float S = (sentence_count/word_count)*100;

    index = 0.0588 * L - 0.296 * S - 15.8;

    return index;
}