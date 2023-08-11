#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {

    long num = 0; // store long credit card number

    int c; // character written from keyboard

    int count = 0; // count to track length of entry

    printf("Enter a credit card number: ");

    // Read characters until newline or end of input
    while ((c = getchar()) != '\n' && c != EOF) {
        // Check if the character is a digit
        count++;
        if (isdigit(c)) {
            num = num * 10 + (c - '0'); // Convert character to integer
        } else {
            // If non-digit character is encountered, input is not numerical
            printf("INVALID\n");

            // Clear the input buffer
            while ((c = getchar()) != '\n' && c != EOF) {}

            return 0; // program terminates
        }
    }

    int i = count; // assign another value to count
    char str[i+1]; // declare string of appropriate length
    str[i+1]='\0'; // set last digit

    // Write long stored in 'num' to a string
    while(i>=0) {
        str[i-1] = num % 10 + 48;
        num = num / 10;
        i--;
    }

    i = count - 2; // reassign i

    int digits1 = 0; 

    int num1 = 0;

    while(i>=0) {
        
        int num1 = str[i] - '0'; // change to int
        num1 = num1 * 2; // multiply by 2

        // catch any values greater than 9 + correct for algorithm
        if(num1==10) { num1 = 1; }
        else if(num1==12) { num1 = 3; }
        else if(num1==14) { num1 = 5; }
        else if(num1==16) { num1 = 7; }
        else if(num1==18) { num1 = 9; }

        digits1 = digits1 + num1; // add latest number

        i=i-2; // decrement 
    }

    i = count - 1; // reassign i

    int digits2 = 0;

    int num2 = 0;

    while(i>=0) {
        int num2 = str[i] - '0'; // change to int
        
        digits2 = digits2 + num2; // add latest number

        i=i-2; // decrement
    }

    int digits3 = digits1 + digits2; // combine

    if(digits3 % 10 != 0) {
        printf("INVALID\n"); // print invalid if last digit in digits3 is not 0.

        return 0;
    }

    // Final number checks to ascertain type of credit card
    if(str[0] == '3' && (str[1] == '4' || '7') && count == 15) {
        printf("AMEX\n");
    }
    else if(str[0] == '4' && (count == 13 || 16)) {
        printf("VISA\n");
    }
    else if(str[0] == '5' && (str[1] == '1' || '2' || '3' || '4' || '5') && count == 16) {
        printf("MASTERCARD\n");
    }
    else {
        printf("INVALID\n");
    }
    
    return 0; // program terminates
}



