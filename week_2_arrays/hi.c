#include <stdio.h>
#include <string.h>

int main(void) {

    char s[3] = "Hi!";

    printf("%s\n", s);
    printf("%i %i %i %i\n", s[0], s[1], s[2], s[3]); // prints integer version of ASCII chars.

    return 0;
}