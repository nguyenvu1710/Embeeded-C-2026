# MACRO: ĐỊNH NGHĨA TÊN HOẶC ĐOẠN MÃ ĐƯỢC THAY THẾ TRƯỚC KHI BIÊN DỊCH

## 1. Cú pháp khai báo

Macro được định nghĩa bằng `#define`. Bộ tiền xử lí thay thế macro trước khi chương trình được biên dịch.

```c
#include <stdio.h>

#define MAX_SENSORS 10
#define SQUARE(value) ((value) * (value))
#define DEBUG 1

int main(void)
{
    printf("Max sensors: %d\n", MAX_SENSORS);
    printf("Square: %d\n", SQUARE(2 + 3)); // Kết quả là 25

#if DEBUG
    printf("Debug enabled\n");
#endif

    return 0;
}
```

`MAX_SENSORS` là macro thay cho một giá trị; `SQUARE(value)` là macro có tham số. `#if` và `#endif` cho phép chọn phần mã được biên dịch dựa trên điều kiện.

## 2. Lưu ý khi dùng macro

Nên đặt ngoặc quanh từng tham số và toàn bộ biểu thức để tránh sai thứ tự tính toán. Macro có thể đánh giá một tham số nhiều lần: `SQUARE(i++)` gây hành vi không xác định trong C, vì vậy không truyền biểu thức có tác dụng phụ như `i++` vào macro này.

Khác với hàm thông thường, macro không tự kiểm tra kiểu tham số như một hàm có khai báo đầy đủ. Với phép tính cần kiểm tra kiểu và chỉ đánh giá mỗi đối số một lần, có thể dùng hàm.

> Trong Embedded C, macro thường dùng để đặt tên cho hằng số, bitmask và lựa chọn cấu hình khi biên dịch.
