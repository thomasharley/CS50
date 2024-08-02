#include <stdio.h>
#include <string.h>

int main(void) {
    
    const char *strings[6] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    const char string[100];

    printf("string: ");
    scanf("%s", &string);

    for (int i=0;i<6;i++) {
        if(strcmp(strings[i], string) == 0) {
            printf("found\n");
            return 0;
        }   
    }
    printf("not found");
    return 1;

}