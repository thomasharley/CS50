#include <stdio.h>
#include <stdlib.h>

/* resizing arrays exercise */
int main(void) {

    int *list = malloc(3 * sizeof(int));
    if(list == NULL) {
        printf("failure to allocate memory");
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    int *tmp = malloc(4 *sizeof(int));
    if(tmp == NULL) {
        printf("failure to allocate memory");
        free(list);
        return 1;
    }

    for(int i=0; i<3; i++) {
        tmp[i] = list[i];
    }
    tmp[3] = 4;

    free(list);
    list = tmp;

    for (int i = 0; i < 3; i++) {
        printf("%i\n", list[i]);
    }

    free(tmp);
    return 0;
}