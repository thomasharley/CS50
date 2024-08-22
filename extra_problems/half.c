#include <stdio.h>
#include <math.h>

int main(void) {

    float bill_value, tax_percent, tip_percent;

    printf("Bill before tax and tip: ");
    scanf("%f", &bill_value);
    
    printf("Sale Tax Percent: ");
    scanf("%f", &tax_percent);

    printf("Tip Percent: ");
    scanf("%f", &tip_percent);

    float total_bill = bill_value * ((tax_percent / 100) + 1);

    float final_bill = total_bill * ((tip_percent / 100) + 1);

    printf("You will owe $%.2f each!", final_bill/2, 2);

    return 0;
}