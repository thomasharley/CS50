#include <stdio.h>

int main (void) {

    char a;

    printf("Do you agree? \n");
    scanf("%c", &a);

    if(a == 'y' || a == 'Y') {
        printf("Agreed. \n");
    }
    else if(a == 'n' || a == 'N') {
        printf("Not agreed. \n");
    }
    else {
        printf("Entry invalid. \n");
    }
    return 0;
}

