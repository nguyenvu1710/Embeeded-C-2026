#include "sequence.h"
#include <stdio.h>

int main() {
    double numerator = Sum(4, 1.5, 2.5, 3.0, 1.0);
    double denominator = Sum(3, 2.0, 1.0, 0.5);
    double result;

    if (!DivideSums(numerator, denominator, &result)) {
        printf("Unable to divide: denominator must not be zero.\n");
        return 1;
    }

    printf("Total numerator is: %f\n", numerator);
    printf("Total denominator is: %f\n", denominator);
    printf("Result is %f\n", result);
    
    return 0;
}


/* HOW TO COMPILE

cd "C:\BK-AUTO\NguyenNgocPhuong---202613415\reports(12-11-2026)"
gcc -std=c11 -Wall -Wextra -Wpedantic main.c sequence.c -o sequence.exe
.\sequence.exe

*/