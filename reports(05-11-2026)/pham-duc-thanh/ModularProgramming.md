# Cấp phát động (Dynamic Memory Allocation)
## 1.Muc tieu
- Hiểu bản chất: Tách biệt phần Giao diện (Interface - cái gì module cung cấp) và phần Thực thi (Implementation - module hoạt động thế nào).
- Cách chia file & quy tắc: Phân định rõ thành phần nào đặt trong .h, thành phần nào đặt trong .c, sử dụng Include Guards và từ khóa static, extern.
- Ứng dụng thực tế: Xây dựng dự án phần mềm lớn nhiều module, tái sử dụng code và làm việc nhóm hiệu quả.

## 2.Khai niem
- Chia file .h (Header file) và .c (Source file) là phương pháp lập trình hướng module (Modular Programming) trong C, giúp chia nhỏ một chương trình lớn thành các khối chức năng độc lập, dễ quản lý, bảo trì và biên dịch riêng rẽ.

## 3.Cach chia va ly do chia
### A. Lý do phải chia file .h và .c
- Tính đóng gói và ẩn giấu thông tin (Encapsulation): Người sử dụng thư viện chỉ cần đọc file .h để biết cách gọi hàm mà không cần quan tâm (hoặc không được phép can thiệp) vào thuật toán chi tiết bên trong file .c.
- Tái sử dụng mã nguồn (Reusability): Dễ dàng copy cặp file math_utils.h và math_utils.c sang bất kỳ dự án nào khác mà không phải cắt dán từng đoạn code.
- Tăng tốc độ biên dịch (Faster Incremental Build): Khi sửa code trong một file .c, trình biên dịch chỉ cần dịch lại duy nhất file .c đó thành file .o rồi liên kết (Link) lại, thay vì phải dịch lại hàng chục nghìn dòng code của toàn dự án.
- Tránh xung đột khi làm việc nhóm: Nhiều kỹ sư có thể lập trình song song trên các module .c khác nhau sau khi đã thống nhất thiết kế giao diện trên file .h.

### B. Quy tắc phân bổ nội dung vào .h và .c
**1. Đặt ở file `.h` (Header - Public Interface / Giao diện công khai):**
- Include Guard (Bắt buộc): Sử dụng `#ifndef ... #define ... #endif` (hoặc `#pragma once`) ở đầu và cuối file để chống lỗi khai báo trùng lặp khi file `.h` được `#include` nhiều lần.
- Nguyên mẫu hàm (Function Prototypes): Chỉ khai báo tên hàm, kiểu trả về và danh sách tham số của các hàm công khai (Public APIs) để các file `.c` khác gọi tới.
- Kiểu dữ liệu & Macro dùng chung: Khai báo các `typedef`, `struct`, `enum`, `#define` hằng số cần chia sẻ cho nhiều module khác cùng sử dụng.
- Khai báo biến chia sẻ (`extern`): Tuyệt đối không định nghĩa và cấp phát biến trong file `.h` (tránh lỗi *Multiple Definition*). Chỉ dùng từ khóa `extern` (ví dụ: `extern int g_count;`) nếu bắt buộc phải chia sẻ biến toàn cục giữa các file.

**2. Đặt ở file `.c` (Source - Private Implementation / Thực thi chi tiết):**
- Không dùng Include Guard: Chỉ dùng `#include` để gọi file `.h` tương ứng của chính nó và các thư viện cần thiết.
- Định nghĩa thân hàm (Function Definitions):** Viết toàn bộ code xử lý thuật toán chi tiết cho các hàm đã khai báo bên file `.h`.
- Hàm nội bộ (`static` functions): Các hàm phụ trợ chỉ phục vụ tính toán bên trong file `.c` đó phải thêm từ khóa `static` ở đầu để ẩn hoàn toàn với các file bên ngoài.
- Biến toàn cục và biến nội bộ (`static` global variables): Định nghĩa các biến toàn cục thực tế và dùng từ khóa `static` cho các biến chỉ được phép truy cập nội bộ trong phạm vi file `.c` đó.
- Macro & Struct nội bộ: Các `#define` hoặc cấu trúc dữ liệu tạm thời chỉ dùng riêng cho thuật toán bên trong file `.c`.

## 4.Co che hoat dong
- Mỗi file .c được trình biên dịch coi là một Translation Unit (Đơn vị dịch) độc lập:
    + Bước Preprocessing: Chỉ thị #include "module.h" sẽ sao chép toàn bộ nội dung của module.h dán vào các file .c có gọi nó. Nhờ Include Guard, nếu module.h vô tình được gọi lồng nhau nhiều lần trong cùng một file .c, nội dung của nó cũng chỉ được dán đúng 1 lần.
    + Bước Compilation: Trình biên dịch dịch từng file main.c và module.c độc lập nhau thành các file mã máy trung gian main.o và module.o. Lúc dịch main.c, nhờ có khai báo nguyên mẫu hàm từ module.h, trình biên dịch biết hàm đó hợp lệ dù chưa thấy thân hàm.
    + Bước Linking (Liên kết): Trình liên kết (Linker) gom main.o và module.o lại, nối lời gọi hàm bên main.o tới đúng địa chỉ thân hàm nằm trong module.o để tạo ra file thực thi cuối cùng.

## 5.Vi du minh hoa:

Giả sử ta xây dựng một module quản lý bộ đếm người dùng gồm 3 file: counter.h, counter.c và main.c.

### File 1: counter.h (Giao diện công khai)
```c
#ifndef COUNTER_H
#define COUNTER_H

// Khai báo kiểu dữ liệu dùng chung
typedef enum {
    COUNTER_OK = 0,
    COUNTER_ERR_LIMIT
} CounterStatus;

// Khai báo nguyên mẫu hàm (Public APIs)
void counter_init(int initial_val);
CounterStatus counter_increment(void);
int counter_get_value(void);

#endif // COUNTER_H
```
### File 2: counter.c (Thực thi chi tiết - Ẩn giấu dữ liệu nội bộ)
```c
#include "counter.h"

#define MAX_LIMIT 100

// Biến static: Chỉ file counter.c mới truy cập được, file bên ngoài không thể sửa bừa bãi
static int s_current_count = 0;

// Hàm static: Hàm phụ trợ nội bộ, ẩn hoàn toàn với bên ngoài
static int is_valid_limit(int val) {
    return (val < MAX_LIMIT);
}

void counter_init(int initial_val) {
    s_current_count = initial_val;
}

CounterStatus counter_increment(void) {
    if (!is_valid_limit(s_current_count)) {
        return COUNTER_ERR_LIMIT;
    }
    s_current_count++;
    return COUNTER_OK;
}

int counter_get_value(void) {
    return s_current_count;
}
```
### File 3: main.c (Chương trình chính sử dụng module)
```c
#include <stdio.h>
#include "counter.h"

int main(void) {
    counter_init(10);
    counter_increment();
    counter_increment();

    printf("Gia tri bo dem hien tai: %d\n", counter_get_value());
    return 0;
}
```

## 6.Ung dung:
- Kiến trúc phần mềm phân lớp (Layered Architecture): Tách bạch tầng ứng dụng (Application Layer), tầng dịch vụ/thuật toán (Middleware/Service Layer) và tầng giao tiếp dữ liệu.