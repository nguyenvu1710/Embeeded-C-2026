

# Macro

## 1. Mục tiêu

- Hiểu Macro là gì. 
- Biết chỉ thị của Macro.
- Ví dụ.
- Lưu ý khi dùng Macro
- Ưu điểm & Nhược điểm của macro

## 2. Khái niệm
- Macro là các chỉ thị cho trình tiền xử lý (preprocessor) thực hiện việc thay thế văn bản trước khi mã nguồn được biên dịch.
- Chú ý: Macro không phải là hàm.

## 3. Chỉ thị
- Định nghĩa macro:
```c
#define TEN_MACRO gia_tri
```
- Hủy nghĩa macro:
```c
#undef 
```
- Kiểm tra Macro đã tồn tại:
```c
#ifdef 
```
- Kiểm tra Macro chưa tồn tại
```c
#ifndef 
```
- Kiểm tra điều kiện tiền xử lý
```c
#if
```
- Nhánh ngược lại
```c
#else
```
- Nhánh điều kiện khác
```c
#elif
```
- Kết thúc điều kiện
```c
#endif
```

## 4. Ví dụ
- **Macro trong định nghĩa hằng số**
```c
#inclde <stdio.h>
#define A 15
int main(){
   printf("A = %d”, A );
   return 0;
}
```
OUTPUT 
> A = 15


- **Macro có tham số**
```c
#include <stdio.h>
#define SQUARE(x) ((x) * (x))

int main(){
    int a = 5;
    printf("SQUARE = %d\n", SQUARE(a));
    return 0;
}
```
OUTPUT
> SQUARE = 25

- **Macro dùng trong Bitmask**
```c
#include <stdio.h>

#define SET_BIT(A, BIT)    ((A) |= (1U << (BIT)))
#define CLEAR_BIT(A, BIT)  ((A) &= ~(1U << (BIT)))
#define TOGGLE_BIT(A, BIT) ((A) ^= (1U << (BIT)))
#define CHECK_BIT(A, BIT)  (((A) >> (BIT)) & 1U)

int main(){
    unsigned char A = 0;
    SET_BIT(A, 0);
    SET_BIT(A, 2);

    printf("A = %d\n", A);
    CLEAR_BIT(A, 0);
    printf("Clear bit 0: %d\n", A);
    TOGGLE_BIT(A, 2);
    printf("Toggle bit 2: %d\n", A);
    printf("Bit 0 = %d\n", CHECK_BIT(A, 0));
    return 0;
}
```
OUTPUT
> A = 5
> Clear bit 0: 4
> Toggle bit 2: 0
> Bit 0 = 0

- **Macro biên dịch có điều kiện**
```c
#include <stdio.h>

#define DEBUG 1

int main(){
#if DEBUG
    printf("ON\n");
#else
    printf("OFF\n");
#endif
    return 0;
}
```
OUTPUT
> ON

## 5. Lưu ý khi dùng macro
Macro không có kiểu dữ liệu (type-safe) và không được kiểm tra bởi compiler như hàm bình thường, rất dễ sinh ra lỗi khó debug:
- Thiếu dấu ngoặc đơn (()):
  + Sai: 
```c
 #define SQUARE(x) x * x 
 //-> SQUARE(1 + 2) 
```
sẽ nở ra thành 1 + 2 * 1 + 2 = 5 (sai kết quả mong muốn là 9).

  + Đúng:
```c
 #define SQUARE(x) ((x) * (x))
 ```
- Tác dụng phụ:
  + Truyền hàm có biểu thức thay đổi giá trị vào macro: SQUARE(i++) sẽ biến thành ((i++) * (i++)), làm biến i tăng đến 2 lần.
  + Trong lập trình nhúng, nếu truyền một hàm đọc thanh ghi vào macro gọi lại nhiều lần, phần cứng sẽ bị đọc trạng thái liên tiếp gây lỗi ngoại vi.
- Tốn dung lượng bộ nhớ không kiểm soát:
  + Nếu dùng macro thay cho hàm có nội dung dài và gọi nó ở 50 nơi, mã máy (Assembly) sẽ bị chép phô (inline copy) ra 50 chỗ, làm đầy bộ nhớ Flash của vi điều khiển. 

## 6. Ưu điểm & nhược điểm
- Ưu điểm:
  + Giúp tái sử dụng đoạn mã.
  + Giảm việc viết lặp lại code.
  + Định nghĩa hằng số dễ dàng.
  + Hữu ích khi cấu hình chương trình.
  + Có thể hỗ trợ tối ưu hiệu năng trong một số trường hợp.
- Nhược điểm:
  + Không kiểm tra kiểu dữ liệu.
  + Dễ phát sinh lỗi do thiếu dấu ngoặc.
  + Khó debug.
  + Có thể gây lỗi khi tham số chứa biểu thức có tác dụng phụ.

