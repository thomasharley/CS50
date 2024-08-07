#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

char* encode(char text[], char cipher[]); /* instantiate function */

int main(int argc, char *argv[]) {

    char plaintext[100];
    int charCount[100] = {0};

    if (argc != 2) { /* check number of arguments inputted*/
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if(strlen(argv[1]) != 26) { /* check number of characters */
        printf("Key must contain 26 alphabetic characters, non-repeating.");
        return 1;
    }
    for (int i=0; i<26; i++) {
        if(isalpha(argv[1][i])!=1) { /* detect if input is all alphabetic characters */
            printf("Key must contain 26 alphabetic characters, non-repeating.");
            return 1;
        } 
        charCount[(char)argv[1][i]]++; /* check for repeats */
        if(charCount[(char)argv[1][i]] > 1) {
            printf("Key must contain 26 alphabetic characters, non-repeating.");
            return 1;
        }
    }
        
    printf("plaintext: ");
    scanf("%s", &plaintext); /* prompt for plaintext entry */

    char *ciphertext = encode(plaintext, argv[1]); /* pass to encoding function */
    printf("ciphertext: %s\n", ciphertext); /* print encoded output */
}


char* encode(char text[], char cipher[]) {

    static char output[100]; /* static to ensure it persists after function return */

    for (int i = 0, len = strlen(text); i<len; i++) {
        if(isalpha(text[i])) { /* check text is alphabetic */
            if(isupper(text[i])) { /* if uppercase */
                output[i] = toupper(cipher[text[i] - 'A']);
            }
            else if(islower(text[i])) { /* if lowercase */
                output[i] = tolower(cipher[text[i] - 'a']);
            }
        }
        else {
            output[i] = text[i]; /* if text is not alphabetic, print as is */
        }
    }
    return output;
}


