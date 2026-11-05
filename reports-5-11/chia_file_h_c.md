# 01. Chia file .h / .c

## 1. Mục tiêu

- Hiểu vì sao phải tách một chương trình lớn thành nhiều file.
- Phân biệt được **khai báo (declaration)** và **định nghĩa (definition)**, biết cái nào đặt trong `.h`, cái nào trong `.c`.
- Biết dùng **include guard**, `extern`, `static` để tổ chức module đúng cách.
- Hiểu quá trình biên dịch và liên kết nhiều file.

## 2. Khái niệm

- **File `.c` (source file):** chứa phần *định nghĩa* – code thực thi của hàm, biến toàn cục.
- **File `.h` (header file):** chứa phần *giao diện (interface)* – khai báo hàm, kiểu dữ liệu (`struct`, `enum`, `typedef`), macro mà module công khai cho bên ngoài dùng.
- **Khai báo:** nói cho compiler biết "có tồn tại" một hàm/biến (kiểu gì, tên gì). Có thể khai báo nhiều lần.
- **Định nghĩa:** thực sự tạo ra hàm/biến (cấp phát bộ nhớ). Chỉ được định nghĩa **một lần** trong toàn chương trình.
- **Translation unit:** một file `.c` sau khi preprocessor đã chèn hết các `#include` vào. Mỗi translation unit được biên dịch độc lập.
- **Include guard:** cơ chế chống include một header nhiều lần.
- **Module:** một cặp `xxx.h` + `xxx.c` đảm nhiệm một chức năng (ví dụ `led.h`/`led.c`).

## 3. Cú pháp

**led.h** (giao diện)

```c
#ifndef LED_H          /* include guard */
#define LED_H

#include <stdint.h>

#define LED_PIN_COUNT 4

typedef enum {
    LED_OFF = 0,
    LED_ON
} LedState_t;

void       Led_Init(void);
void       Led_Set(uint8_t index, LedState_t state);
LedState_t Led_Get(uint8_t index);

extern uint32_t g_led_toggle_count;   /* khai báo biến toàn cục, định nghĩa ở led.c */

#endif /* LED_H */
```

**led.c** (cài đặt)

```c
#include "led.h"

uint32_t g_led_toggle_count = 0;       /* định nghĩa biến */

static LedState_t s_led[LED_PIN_COUNT]; /* static: chỉ dùng trong file này */

static void prv_hw_write(uint8_t index, LedState_t state)  /* hàm nội bộ */
{
    /* ghi thanh ghi phần cứng ... */
}

void Led_Init(void)
{
    for (uint8_t i = 0; i < LED_PIN_COUNT; i++) {
        s_led[i] = LED_OFF;
        prv_hw_write(i, LED_OFF);
    }
}

void Led_Set(uint8_t index, LedState_t state)
{
    s_led[index] = state;
    prv_hw_write(index, state);
    g_led_toggle_count++;
}

LedState_t Led_Get(uint8_t index)
{
    return s_led[index];
}
```

**main.c** (nơi sử dụng)

```c
#include "led.h"

int main(void)
{
    Led_Init();
    Led_Set(0, LED_ON);
    while (1) { }
}
```

**Biên dịch bằng gcc:**

```bash
gcc -c led.c -o led.o
gcc -c main.c -o main.o
gcc led.o main.o -o app
```

## 4. Cơ chế hoạt động

Quá trình từ source đến file chạy gồm 4 giai đoạn:

```
.c --(1. Preprocessor)--> .i --(2. Compiler)--> .s --(3. Assembler)--> .o --(4. Linker)--> file thực thi
```

1. **Preprocessor:** xử lý `#include`, `#define`, `#if...`. `#include "led.h"` đơn giản là **copy nguyên nội dung** `led.h` dán vào vị trí đó.
2. **Compiler:** dịch từng translation unit riêng lẻ ra assembly. Khi gặp lời gọi `Led_Set(...)` trong `main.c`, compiler chỉ cần *khai báo* (từ `led.h`) để kiểm tra kiểu, chưa cần biết code bên trong.
3. **Assembler:** tạo file object `.o` (mã máy, kèm bảng symbol).
4. **Linker:** ghép các `.o`, tìm *định nghĩa* thật cho mọi symbol đã được dùng, gán địa chỉ cuối cùng.

**Include guard hoạt động ra sao:** lần include đầu tiên, `LED_H` chưa được định nghĩa nên nội dung header được giữ lại và `LED_H` được `#define`. Các lần include sau, `LED_H` đã tồn tại nên toàn bộ nội dung bị bỏ qua, tránh lỗi định nghĩa lặp (`redefinition`).

**`static` ở mức file:** làm symbol có *internal linkage*, linker không thấy nó từ file khác, nên hai file có thể có hàm `static` trùng tên mà không xung đột.

**Lỗi thường gặp:**

| Lỗi | Nguyên nhân |
|---|---|
| `undefined reference to 'Led_Set'` | Quên biên dịch/link `led.c`, hoặc chỉ khai báo mà chưa định nghĩa |
| `multiple definition of 'x'` | Định nghĩa biến/hàm (không `static`) trong `.h` rồi include ở nhiều `.c` |
| `redefinition of ...` | Thiếu include guard |

## 5. Ứng dụng trong Embedded C

- **Mỗi ngoại vi một module:** `gpio.h/.c`, `uart.h/.c`, `spi.h/.c`, `timer.h/.c`... Tầng ứng dụng chỉ `#include` header, không cần biết thanh ghi bên trong.
- **Phân tầng phần mềm:** `main.c` (ứng dụng) → driver/HAL (`uart.c`) → file định nghĩa thanh ghi (`stm32xx.h`). Khi đổi chip chỉ sửa tầng dưới.
- **Che giấu dữ liệu (encapsulation):** biến trạng thái nội bộ khai báo `static` trong `.c`; bên ngoài chỉ truy cập qua hàm `Get/Set`. Tránh việc code khác vô tình ghi đè biến quan trọng.
- **File cấu hình `config.h`:** gom mọi `#define` như tần số clock, baudrate, số phần tử buffer, bật/tắt tính năng vào một nơi, dễ chỉnh theo board.
- **Header định nghĩa thanh ghi:** vendor cung cấp `.h` chứa `#define` địa chỉ thanh ghi, `struct` ánh xạ ngoại vi (`GPIOA->ODR`). Đây chính là cách viết điển hình của CMSIS.
- **Dễ làm việc nhóm và kiểm thử:** mỗi người một module, có thể test riêng từng `.c`; biên dịch lại chỉ file thay đổi nên build nhanh hơn (quan trọng với project lớn dùng Makefile/IDE).
- **Quy ước nên theo:** header không chứa định nghĩa biến/hàm (trừ `static inline`); hàm/biến chỉ dùng nội bộ luôn thêm `static`; đặt tên có tiền tố module (`Led_`, `Uart_`) để tránh trùng tên.
