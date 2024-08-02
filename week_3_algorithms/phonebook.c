#include <stdio.h>
#include <string.h>

typedef struct { /* declare structure */
    char *name[100];
    char *number[100];
}
person;

int main(void) {

    person people[3];

    *people[0].name = "Carter";
    *people[0].number = "+1-617-495-1000";

    *people[1].name = "David";
    *people[1].number = "+1-617-495-1000";

    *people[2].name = "John";
    *people[2].number = "+1-617-495-1000";

    const char name[100];
    printf("name: ");
    scanf("%s", &name); /* read in name */

    for(int i=0;i<3;i++) {
        if(strcmp(*people[i].name, name) == 0) {
            printf("number: %s", *people[i].number); /* print out number */
            return 0;
        }
    }
    printf("not found");
    return 1;
}  