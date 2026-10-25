# Union

## 1.Muc tieu

* Hiểu cơ chế chia sẻ bộ nhớ: Nắm rõ bản chất tất cả các thành phần trong union dùng chung một vùng nhớ duy nhất.
* Phân biệt Struct và Union: Hiểu sự khác nhau về dung lượng bộ nhớ và khả năng lưu trữ dữ liệu đồng thời giữa hai kiểu.
* Tối ưu hóa bộ nhớ: Biết cách ứng dụng Union vào các bài toán tiết kiệm RAM/bộ nhớ hoặc phân tích dữ liệu nhị phân.

## 2.Khai niem

* union là một kiểu dữ liệu đặc biệt cho phép lưu trữ các kiểu dữ liệu khác nhau tại cùng một vùng nhớ. Khác với struct, tất cả các thành phần trong union dùng chung bộ nhớ với nhau.

## 3.Cu phap

Cú pháp khai báo: `union union_name { Type1 field1; Type2 field2; ... };`

Cách truy xuất: Sử dụng toán tử dấu chấm (.) giống như struct để truy cập các thành viên.

## 4.Co che hoat dong

* Dùng chung một ô nhớ: Tất cả các thành viên trong một union đều bắt đầu từ cùng một địa chỉ bộ nhớ.
* Lưu trữ một giá trị tại một thời điểm: Do dùng chung vùng nhớ, bạn có thể gán giá trị cho nhiều thành viên, nhưng union chỉ giữ lại giá trị của thành viên được gán gần nhất.
* Kích thước của Union: Kích thước của union bằng kích thước của thành viên lớn nhất trong đó.

## 5.Vi du minh hoa

```c
#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;

    data.i = 10;
    printf("data.i = %d\n", data.i);

    data.f = 220.5;
    printf("data.f = %.1f\n", data.f);

    return 0;
}
```

## 6.Ung dung thuc te

* Tiết kiệm bộ nhớ trong các hệ thống nhúng (Embedded Systems) khi một biến có thể đại diện cho nhiều kiểu dữ liệu khác nhau nhưng không cần dùng đồng thời.
* Chuyển đổi và tách byte dữ liệu (Data Packing/Unpacking) từ các giao thức truyền thông như UART, SPI, CAN.