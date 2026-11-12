#include <stdio.h>
#include "project1.h" 

int main() {
    printf("TEST CASE 1: TRUONG HOP MAU KHAC 0\n");
    int sum1 = sum(4, 10, 20, 30, 40);
    int sum2 = sum(3, 5, 10, 10);

    printf("Tong day 1 la: %d\n", sum1);
    printf("Tong day 2 la: %d\n", sum2);

    float ans1 = divide(sum1, sum2);
    printf("Ket qua: %.2f\n", ans1);


    printf("TEST CASE 2: TRUONG HOP MAU BANG 0\n");
    int sum3 = sum(2, 15, 25);
    int sum4 = sum(3, 10, -5, -5);

    printf("Tong day 3 la: %d\n", sum3);
    printf("Tong day 4 la: %d\n", sum4);

    float ans2 = divide(sum3, sum4); 
    printf("Ket qua: %.2f\n", ans2);

    return 0;
}