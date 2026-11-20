#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include "ham.h"
// dãy số
void nhap_dayso(int a[], int n){
    assert(a != NULL);// kiểm tra con trỏ mảng không phải con trỏ NULL
    assert(n > 0); //kiểm tra số lượng phần tử > 0

    for (int i = 0; i < n; i++){
        printf("Nhap phan tu [%d]: ", i + 1);
        scanf("%d", &a[i]);
    }
}

//phép toán
  //tổng các phần tử trong mảng
int TongPhanTu(int a[], int n){
    assert(a != NULL);
    assert(n > 0);

    int tong = 0;
    for (int i = 0; i < n; i++){
        tong += a[i];
    }
    return tong;
}

  //kiểm tra mẫu số
int KiemTraMauSo(int mau){
    return mau != 0;
}

  //chia tổng 2 dãy số
double thuong(double tu, double mau){
    assert(KiemTraMauSo(mau));
    return tu/mau;
}
