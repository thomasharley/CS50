#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

bool valid(char *password);

int main(void) {

    char *password = malloc(4);

    printf("Enter your password: ");
    scanf("%s", password);

    if(valid(password)) {
        printf("Your password is valid!\n");
    }
    else {
        printf("You password needs at least one uppercase letter, lowercase letter, number and symbol!\n");
    }

    free(password);

    return 0;
}

bool valid(char *password) {

    bool upper = false; bool lower = false; bool digit = false; bool punct = false;

    for (int i = 0; i<strlen(password); i++) {

        if(isupper(password[i])) {
            upper = true;
        } 
        else if(islower(password[i])) {
            lower = true;
        }
        else if(isdigit(password[i])) {
            digit = true;
        }
        else if(ispunct(password[i])) {
            punct = true;
        }
    }

    if(upper && lower && digit && punct) {
        return true;
    }
    else {
        return false;
    }



}