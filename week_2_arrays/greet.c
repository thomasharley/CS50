#include <stdio.h>

int main(int argc, char *argv[argc + 1]) {

    printf("hello, %s\n", argv[1]);
    printf("%i arguments were specified.\n", argc);

    return 0;
} 