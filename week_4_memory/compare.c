#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    char *s = malloc(4); /* dynamic memory allocation */
    char *t = malloc(4);

    printf("s: ");
    scanf("%s", s);
    printf("t: ");
    scanf("%s", t);

    if(strcmp(s,t)==0) {
        printf("same\n");
    }
    else {
        printf("different\n");
    }
}