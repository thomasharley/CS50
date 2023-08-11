#include <stdio.h>

#define MAXLENGTH 100   /* Maximum length of string */

int main(void) {
    /* Define variable to store answer */
    char answer[MAXLENGTH];

    /* Get input from the user */
    printf("What's your name?\n");
    scanf("%s", answer);

    /* Print Name, %s is placeholder for string "answer" */
    printf("hello, %s\n", answer);    
}

/*  This program crudely implements a solution to our problem. The CS50 header file
    performs this task better as it can handle spaces, etc. So this could do with
    some work.
        */