#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

    FILE *file = fopen("phonebook.csv", "a");
    if(file == NULL) {
        return 1;
    }

    char *number = malloc(4);
    char *name = malloc(4);

    printf("Name: ");
    scanf("%s", name);
    printf("Number: ");
    scanf("%s", number);

    fprintf(file, "%s,%s\n", name, number);
    fclose(file);

    free(number);
    free(name);

}