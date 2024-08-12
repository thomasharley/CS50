#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {

    char *s = malloc(4);
    if(s == NULL) {
        return 1;
    }

    printf("s: ");
    scanf("%s", s);

    char *t = malloc(strlen(s)+1);
    if(t == NULL) {
        return 1;
    }

    strcpy(t,s); /* copy */

    if(strlen(t)>0) {
        t[0] = toupper(t[0]);
    }

    printf("%s\n", s);
    printf("%s\n", t);

    free(s); /* frees the memory */
    free(t);
    return 0;
}