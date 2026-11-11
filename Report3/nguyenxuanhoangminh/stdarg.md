
## 1. `stdarg.h` là gì?

Trong C, có những hàm cần nhận **số lượng đối số không cố định**. Ví dụ, hàm `printf()` có thể nhận một chuỗi định dạng và nhiều giá trị khác nhau:

```c
printf("Temperature: %d, Voltage: %.2f\n", temperature, voltage);
```

Để xây dựng những hàm linh hoạt như vậy, C cung cấp **variadic function** (hàm có danh sách đối số thay đổi) và thư viện **`<stdarg.h>`**.

`stdarg.h` cung cấp các macro giúp chương trình truy cập lần lượt những đối số nằm sau phần tham số cố định của hàm.

Ví dụ về khai báo hàm có số lượng đối số thay đổi:

```c
int sum(int count, ...);
```

Trong đó:

- `count` là tham số cố định, cho biết có bao nhiêu số cần cộng.
- `...` (ellipsis) đại diện cho danh sách đối số có số lượng thay đổi.

**Mục đích:** Cho phép một hàm nhận nhiều đối số mà không cần viết nhiều phiên bản hàm cho từng trường hợp.

## 2. Tại sao cần dùng `stdarg.h`?

Nếu không dùng `stdarg.h`, ta thường phải truyền dữ liệu qua mảng, cấu trúc hoặc viết nhiều hàm riêng. Với các hàm cần nhận số lượng tham số linh hoạt, cách này có thể khiến giao diện sử dụng phức tạp hơn.

`stdarg.h` đặc biệt hữu ích trong các trường hợp:

- **Logging và Debug:** Tạo hàm ghi nhật ký có thể nhận nhiều kiểu dữ liệu, tương tự `printf()`.
- **Giao tiếp UART:** Tạo hàm gửi thông báo có định dạng ra Serial/UART.
- **Hàm xử lý dữ liệu linh hoạt:** Ví dụ hàm tính tổng nhận số lượng số nguyên tùy ý.

Trong Embedded C, cách dùng này giúp tạo một giao diện log thống nhất thay vì phải viết riêng hàm cho từng số lượng tham số.

## 3. Các thành phần chính của `stdarg.h`

Thư viện cung cấp một kiểu dữ liệu và bốn macro thường dùng:

| Thành phần | Chức năng dễ hiểu |
|---|---|
| `va_list` | Khai báo biến dùng để quản lý danh sách đối số thay đổi. |
| `va_start(args, last)` | Khởi tạo `args` để bắt đầu đọc các đối số nằm sau tham số cố định cuối cùng `last`. |
| `va_arg(args, type)` | Lấy đối số tiếp theo theo kiểu dữ liệu được chỉ định. Sau đó, danh sách chuyển sang đối số kế tiếp. |
| `va_end(args)` | Kết thúc việc truy cập danh sách đối số. |
| `va_copy(dest, src)` | Sao chép trạng thái của một danh sách đối số sang danh sách khác. |

Có thể nhớ quy trình cơ bản như sau:

1. Dùng `va_list` để khai báo danh sách.
2. Dùng `va_start()` để bắt đầu đọc.
3. Dùng `va_arg()` để lấy từng đối số.
4. Dùng `va_end()` khi đọc xong.

## 4. Ví dụ: Hàm tính tổng nhiều số nguyên

```c
#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...)
{
    va_list args;
    int total = 0;

    // Bắt đầu đọc các đối số sau count
    va_start(args, count);

    // Đọc lần lượt count số nguyên
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }

    // Kết thúc việc đọc danh sách
    va_end(args);

    return total;
}

int main(void)
{
    printf("Sum = %d\n", sum(3, 10, 20, 30));
    printf("Sum = %d\n", sum(4, 1, 2, 3, 4));

    return 0;
}
```

**Kết quả:**

```text
Sum = 60
Sum = 10
```

Giải thích lời gọi `sum(3, 10, 20, 30)`:

- `count = 3`: hàm biết cần đọc ba đối số thay đổi.
- `va_start(args, count)`: bắt đầu truy cập danh sách sau `count`.
- Lần gọi `va_arg(args, int)` thứ nhất lấy `10`.
- Lần thứ hai lấy `20`.
- Lần thứ ba lấy `30`.
- `va_end(args)`: kết thúc danh sách.
- Hàm trả về `10 + 20 + 30 = 60`.

## 5. Ứng dụng trong Embedded C: Hàm ghi log UART

Một ứng dụng phổ biến là tạo hàm log có thể nhận nhiều giá trị:

```c
#include <stdio.h>
#include <stdarg.h>

void UART_Log(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    // Xử lý danh sách đối số theo chuỗi format
    vprintf(format, args);

    va_end(args);
}

int main(void)
{
    int temperature = 25;
    float voltage = 3.3f;

    UART_Log("System started\n");
    UART_Log("Temperature: %d C\n", temperature);
    UART_Log("Voltage: %.1f V\n", (double)voltage);

    return 0;
}
```

Trong ví dụ:

- `format` là tham số cố định, chứa chuỗi định dạng.
- `...` nhận các giá trị cần in.
- `va_list` quản lý danh sách giá trị.
- `vprintf()` xử lý chuỗi định dạng cùng danh sách đối số.

Trong một dự án vi điều khiển thực tế, đầu ra của `printf`/`vprintf` cần được cấu hình để chuyển tới UART. Không phải môi trường Embedded nào cũng hỗ trợ sẵn đầy đủ các hàm này.

## 6. Nguyên lý hoạt động của `stdarg.h`

Khi gọi một hàm có `...`, các đối số được truyền theo quy ước gọi hàm của nền tảng. Tùy kiến trúc và trình biên dịch, chúng có thể được truyền qua thanh ghi, Stack hoặc kết hợp cả hai.

Quy trình khái quát:

1. **Khi gọi hàm:** chương trình truyền các tham số cố định và các đối số thay đổi vào hàm.
2. **Khởi tạo:** `va_start()` thiết lập trạng thái để truy cập đối số đầu tiên sau tham số cố định cuối cùng.
3. **Đọc dữ liệu:** mỗi lần gọi `va_arg()` lấy đối số tiếp theo theo kiểu được yêu cầu.
4. **Kết thúc:** `va_end()` kết thúc quá trình truy cập danh sách.

Lưu ý: Không nên hiểu `va_list` luôn là một con trỏ RAM đơn giản, hoặc `va_arg()` luôn chỉ cộng thêm `sizeof(type)` vào địa chỉ. Cách quản lý thực tế phụ thuộc vào kiến trúc CPU và quy ước truyền tham số của hệ thống.

### Những quy tắc cần nhớ

- Hàm variadic trong C phải có ít nhất một tham số cố định trước `...`.
- `va_arg()` phải đọc đúng kiểu tương ứng với đối số đã truyền. Đọc sai kiểu có thể gây hành vi không xác định.
- Khi truyền qua `...`, `char` và `short` thường được nâng cấp thành `int`; `float` được nâng cấp thành `double`. Vì vậy, cần đọc chúng bằng kiểu đã được nâng cấp, chẳng hạn `va_arg(args, int)` hoặc `va_arg(args, double)`.
- Hàm thường cần một cách để biết có bao nhiêu đối số hoặc biết kiểu của từng đối số. Ví dụ `sum()` dùng `count`, còn `printf()` dùng chuỗi định dạng.

## 7. Mối quan hệ giữa `stdarg.h` và `assert.h`

Hai thư viện này thường xuất hiện trong quá trình debug, nhưng **chúng có chức năng khác nhau và không phụ thuộc trực tiếp vào nhau**.

| Tiêu chí | `stdarg.h` | `assert.h` |
|---|---|---|
| Mục đích | Truy cập danh sách đối số có số lượng thay đổi. | Kiểm tra một điều kiện logic được kỳ vọng là đúng. |
| Thành phần chính | `va_list`, `va_start()`, `va_arg()`, `va_end()`, `va_copy()`. | Macro `assert(condition)`. |
| Giải quyết vấn đề | Làm cho hàm linh hoạt hơn khi nhận dữ liệu. | Phát hiện giả định logic bị vi phạm khi debug. |
| Ví dụ | Hàm `UART_Log()` nhận nhiều giá trị để in. | Kiểm tra `duty` nằm trong khoảng 0–100. |

### Có thể sử dụng chúng cùng nhau không?

Có. Ví dụ, `UART_Log()` dùng `stdarg.h` để ghi thông tin lỗi, còn `assert()` dùng để kiểm tra điều kiện:

```c
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

void UART_Log(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void PWM_SetDutyCycle(int duty)
{
    if (duty < 0 || duty > 100) {
        UART_Log("ERROR: Invalid PWM duty = %d\n", duty);
    }

    // Kiểm tra giả định trước khi tiếp tục
    assert(duty >= 0 && duty <= 100);

    printf("PWM set to %d%%\n", duty);
}

int main(void)
{
    PWM_SetDutyCycle(50);   // Hợp lệ
    PWM_SetDutyCycle(150);  // Ghi log, sau đó assert được kích hoạt

    return 0;
}
```

Trong ví dụ này:

- `stdarg.h` giúp `UART_Log()` nhận chuỗi định dạng và các giá trị cần ghi.
- `assert.h` kiểm tra điều kiện `duty >= 0 && duty <= 100`.
- Khi `duty = 150`, hàm ghi thông tin lỗi rồi `assert` phát hiện điều kiện sai và dừng chương trình theo cơ chế của thư viện C.

**Điểm quan trọng:** `assert` không cần `stdarg.h` để hoạt động. `stdarg.h` cũng không cần `assert.h`. Chúng chỉ có thể phối hợp trong một chương trình debug: một bên hỗ trợ ghi thông tin, bên còn lại kiểm tra giả định logic.

## 8. Kết luận

`stdarg.h` là thư viện hỗ trợ xây dựng các hàm có số lượng đối số thay đổi. Nó đặc biệt hữu ích khi tạo hệ thống logging, debug và giao tiếp UART trong Embedded C.

Trong khi đó, `assert.h` giúp kiểm tra các giả định logic và phát hiện lỗi trong quá trình phát triển. Có thể kết hợp hai thư viện để vừa ghi lại thông tin lỗi, vừa kiểm tra điều kiện, nhưng cần nhớ rằng chúng có hai vai trò riêng biệt.
