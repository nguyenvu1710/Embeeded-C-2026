#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include "ham.h"

int main(){
    int a[100], b[100];
    int n,m;

    printf("Nhap so luong phan tu thu nhat: ");
    scanf("%d", &n);

    printf("Nhap so luong phan tu thu hai: ");
    scanf("%d", &m);

    assert(n > 0 && n <= 100);
    assert(n > 0 && m <= 100);// kiểm tra điều kiện 0<m,n<= 100

    printf("\nNhap day thu nhat: \n");
    nhap_dayso(a,n);

    printf("\nNhap day thu hai: \n");
    nhap_dayso(b,m);

    int S1 = TongPhanTu(a,n);
    int S2 = TongPhanTu(b,m);

    if (KiemTraMauSo(S2)){
        double ketqua = thuong(S1,S2);

        printf("\n Thuong cua tong day thu nhat va tong day thu hai la = %.2lf", ketqua);
    }
    else{
        printf("\n Mau so bang 0, khong the thuc hien!");
    }
    return 0;
}
