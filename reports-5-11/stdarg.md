# 06. stdarg (hàm có số tham số biến đổi)

## 1. Mục tiêu

- Hiểu hàm **variadic** là gì (như `printf`).
- Dùng đúng bộ macro `va_list`, `va_start`, `va_arg`, `va_end`, `va_copy`.
- Hiểu cơ chế lấy tham số từ stack/thanh ghi và các quy tắc chuyển kiểu ngầm.
- Áp dụng để viết hàm log/debug trong hệ nhúng.

## 2. Khái niệm

- **Hàm variadic:** hàm nhận số lượng tham số không cố định, khai báo bằng dấu `...` ở cuối danh sách tham số.
- **`<stdarg.h>`:** thư viện chuẩn cung cấp công cụ duyệt các tham số biến đổi:

| Thành phần | Vai trò |
|---|---|
| `va_list` | Kiểu dữ liệu "con trỏ" đến danh sách tham số |
| `va_start(ap, last)` | Khởi tạo `ap` để trỏ tới tham số đầu tiên sau `last` |
| `va_arg(ap, type)` | Lấy tham số hiện tại theo kiểu `type`, rồi chuyển sang tham số kế |
| `va_end(ap)` | Dọn dẹp khi xong |
| `va_copy(dst, src)` | Sao chép `va_list` (C99) |

- **Tham số cố định cuối cùng (`last`):** tham số có tên ngay trước `...`. Hàm variadic bắt buộc có ít nhất một tham số cố định.
- **Biến thể `v...`:** `vprintf`, `vsnprintf`... nhận `va_list` thay vì `...`, dùng để viết hàm bọc (wrapper) quanh `printf`.

## 3. Cú pháp

**Ví dụ 1: tính tổng, truyền số lượng trước**

```c
#include <stdarg.h>

int Sum(int count, ...)
{
    va_list ap;
    int total = 0;

    va_start(ap, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(ap, int);
    }
    va_end(ap);

    return total;
}

int s = Sum(4, 10, 20, 30, 40);   /* 100 */
```

**Ví dụ 2: dùng giá trị kết thúc (sentinel)**

```c
int SumUntilZero(int first, ...)
{
    va_list ap;
    int total = 0;
    int v = first;

    va_start(ap, first);
    while (v != 0) {
        total += v;
        v = va_arg(ap, int);
    }
    va_end(ap);
    return total;
}

SumUntilZero(5, 6, 7, 0);   /* 18 */
```

**Ví dụ 3: hàm log kiểu printf (kết hợp `vsnprintf`)**

```c
#include <stdarg.h>
#include <stdio.h>

void Log(const char *fmt, ...)
{
    char buf[128];
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);   /* dùng snprintf bản v: an toàn, giới hạn kích thước */
    va_end(ap);

    Uart_SendString(buf);
}

Log("Nhiet do = %d C, ADC = %u\r\n", temp, adc);
```

**Ví dụ 4: tự phân tích chuỗi định dạng**

```c
void MyPrint(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'd': { int v = va_arg(ap, int);          PrintInt(v);    break; }
                case 's': { const char *s = va_arg(ap, const char *); PrintStr(s); break; }
                case 'c': { int c = va_arg(ap, int);          PrintChar((char)c); break; }  /* char được nâng lên int */
                default:  PrintChar('%'); PrintChar(*fmt);    break;
            }
        } else {
            PrintChar(*fmt);
        }
        fmt++;
    }

    va_end(ap);
}
```

## 4. Cơ chế hoạt động

- Với hàm `...`, compiler **không biết** số lượng và kiểu của các tham số thêm vào. Việc đó hoàn toàn do **hàm** tự suy ra từ tham số cố định (số lượng, chuỗi định dạng hoặc giá trị kết thúc), và **lập trình viên chịu trách nhiệm** để hai bên khớp nhau.
- **Tham số được truyền như thế nào:** theo quy ước gọi hàm (ABI) của từng kiến trúc, tham số được đặt vào các thanh ghi và/hoặc đẩy lên **stack** theo thứ tự nhất định. Các tham số biến đổi nằm nối tiếp nhau ngay sau tham số cố định cuối cùng.
- **`va_start(ap, last)`** tính địa chỉ của vùng tham số ngay sau `last` và lưu vào `ap`. Mỗi lần **`va_arg(ap, type)`** đọc `sizeof(type)` byte (có căn chỉnh) tại vị trí hiện tại, trả về giá trị rồi dịch `ap` tới tham số tiếp theo. Có thể hình dung đơn giản:

```
stack:  [ count ][ 10 ][ 20 ][ 30 ][ 40 ] ...
          ^last   ^ap sau va_start
                  va_arg -> 10, ap dịch sang 20
                  va_arg -> 20, ap dịch sang 30 ...
```

  (Cách cài đặt thật phụ thuộc compiler/kiến trúc; trên ARM/x86-64 có thể có một phần tham số nằm trong thanh ghi nên `va_start` còn lưu thanh ghi vào một vùng đệm. Không nên tự suy đoán địa chỉ, hãy luôn dùng các macro.)
- **Quy tắc nâng kiểu mặc định (default argument promotions):** với phần `...`, compiler tự động
  - `char`, `short` → **`int`** (`unsigned char/short` → `int` hoặc `unsigned int`)
  - `float` → **`double`**

  Vì thế phải lấy ra bằng `va_arg(ap, int)` và `va_arg(ap, double)`, **không** bao giờ `va_arg(ap, char)` hay `va_arg(ap, float)` (hành vi không xác định).
- **Không có kiểm tra kiểu:** truyền sai kiểu hoặc lấy nhiều hơn số truyền vào → đọc rác trong stack, hành vi không xác định (crash, giá trị sai).

```c
printf("%d\n");              /* thiếu tham số: in giá trị rác */
printf("%s\n", 123);         /* sai kiểu: có thể crash */
```

- **Vì sao phải có `va_end`:** trên một số kiến trúc `va_start` cấp tài nguyên tạm; quy tắc là cứ `va_start` thì phải có `va_end` trước khi hàm trả về.

## 5. Ứng dụng trong Embedded C

- **Hàm log/debug in ra UART/SWO/semihosting:** đây là ứng dụng phổ biến nhất. Hệ nhúng không có màn hình nên cần hàm giống `printf` đẩy chuỗi qua UART. Mẫu chuẩn: `va_start` → `vsnprintf` vào buffer → gửi buffer đi bằng driver UART (xem ví dụ 3). Thường bọc thêm bằng macro:

```c
#ifdef DEBUG
    #define LOG(fmt, ...)  Log("[%s:%d] " fmt "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)  ((void)0)
#endif
```

  (`__VA_ARGS__` là phiên bản macro của `...`; `##__VA_ARGS__` là cách mở rộng của GCC/Clang để bỏ dấu phẩy thừa khi không có tham số.)
- **Hàm bọc cho nhiều đầu ra:** một hàm `Log()` chung, bên trong chọn gửi UART, ghi flash hay đẩy vào ring buffer, nên phần còn lại của chương trình không cần biết.
- **Tự viết `printf` rút gọn (`my_printf`):** thư viện `printf` đầy đủ trong newlib/glibc rất nặng (tốn nhiều KB flash, dùng nhiều stack, đôi khi dùng heap, hỗ trợ `float`). Trên MCU nhỏ, người ta tự viết bản gọn chỉ hỗ trợ `%d %u %x %s %c` bằng `stdarg` (như ví dụ 4), hoặc dùng bản `printf` nhúng (`nanolibc`, `tiny printf`).
- **Đóng gói/gửi lệnh có số tham số thay đổi:** hàm gửi lệnh AT cho module (SIM, ESP8266...) kiểu `AT_Send("AT+CIPSTART=\"TCP\",\"%s\",%d", host, port);`.
- **Lưu ý khi dùng trong hệ nhúng:**
  - **Tốn stack:** `vsnprintf` + buffer cục bộ có thể tốn vài trăm byte stack; cẩn thận với task RTOS có stack nhỏ.
  - **Không dùng trong ISR:** thời gian chạy dài và không cố định. Trong ISR chỉ nên đặt cờ/đẩy dữ liệu vào buffer, để vòng lặp chính in ra.
  - **Luôn dùng `vsnprintf` (có giới hạn kích thước)** thay vì `vsprintf` để tránh tràn buffer.
  - **Không an toàn kiểu:** MISRA C hạn chế dùng hàm variadic vì lý do này. Chỉ dùng cho mục đích log/debug có kiểm soát, hạn chế dùng trong logic điều khiển chính.
  - **Số thực:** `%f` thường bị tắt mặc định trong newlib-nano để tiết kiệm flash; cần bật cờ liên kết riêng (`-u _printf_float`) nếu muốn in `float`.
