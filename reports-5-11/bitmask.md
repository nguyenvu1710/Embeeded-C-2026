# 03. Bitmask

## 1. Mục tiêu

- Thao tác thành thạo từng bit và nhóm bit trong một biến/thanh ghi: set, clear, toggle, kiểm tra, trích xuất.
- Hiểu mask hoạt động như thế nào ở mức bit.
- Biết các lỗi thường gặp (kiểu dữ liệu, độ ưu tiên toán tử).
- Áp dụng vào cấu hình thanh ghi phần cứng.

## 2. Khái niệm

- **Bit mask:** một giá trị số nguyên mà các bit `1` đánh dấu những vị trí bit ta muốn tác động, các bit `0` là vị trí bỏ qua.
- **Toán tử bit** (nền tảng, đã học ở phần bitwise):

| Toán tử | Ý nghĩa |
|---|---|
| `&` | AND – giữ lại bit nơi mask = 1 |
| `\|` | OR – ép bit nơi mask = 1 lên 1 |
| `^` | XOR – đảo bit nơi mask = 1 |
| `~` | NOT – đảo toàn bộ bit |
| `<<` `>>` | Dịch trái / phải |

- **Bit position (vị trí bit):** đánh số từ 0 (LSB, bên phải). Mask cho bit `n` là `(1U << n)`.
- **Bit field / trường bit:** một nhóm bit liền nhau mang một ý nghĩa (ví dụ 2 bit `MODE`).

## 3. Cú pháp

```c
#include <stdint.h>

uint32_t reg = 0;

/* Set bit n lên 1 */
reg |= (1U << n);

/* Clear bit n về 0 */
reg &= ~(1U << n);

/* Toggle bit n */
reg ^= (1U << n);

/* Kiểm tra bit n */
if (reg & (1U << n)) { /* bit n đang là 1 */ }

/* Set/clear nhiều bit cùng lúc */
#define MASK  ((1U << 3) | (1U << 5))     /* bit 3 và bit 5 */
reg |=  MASK;
reg &= ~MASK;

/* Ghi một trường bit (field) rộng 3 bit, bắt đầu ở bit 4 */
#define FIELD_POS   4U
#define FIELD_MASK  (0x7U << FIELD_POS)
reg = (reg & ~FIELD_MASK) | ((value << FIELD_POS) & FIELD_MASK);

/* Đọc trường bit đó */
uint32_t v = (reg & FIELD_MASK) >> FIELD_POS;
```

**Bộ macro thường dùng:**

```c
#define BIT(n)              (1U << (n))
#define SET_BIT(reg, n)     ((reg) |=  BIT(n))
#define CLEAR_BIT(reg, n)   ((reg) &= ~BIT(n))
#define TOGGLE_BIT(reg, n)  ((reg) ^=  BIT(n))
#define READ_BIT(reg, n)    (((reg) >> (n)) & 1U)
```

## 4. Cơ chế hoạt động

Ví dụ với 8 bit, `reg = 0b1010_0101`, thao tác trên bit 1 và bit 4.

**Set bit** (OR với mask có bit đó = 1):

```
reg   = 1010 0101
mask  = 0001 0010     (bit 4 và bit 1)
OR    = 1011 0111     -> bit 4 và bit 1 thành 1, các bit khác giữ nguyên
```

**Clear bit** (AND với đảo mask):

```
reg   = 1010 0101
~mask = 1110 1101
AND   = 1010 0101 & 1110 1101 = 1010 0101  (bit 4 đã = 0, bit 1 đã = 0 nên không đổi)
```

**Toggle** (XOR): bit nào mask = 1 thì bị đảo, còn lại giữ nguyên.

**Ý tưởng chung:** `OR` dùng để bật, `AND` với `~mask` dùng để tắt, `XOR` để đảo, `AND` với mask dùng để đọc.

**Các lỗi thường gặp:**

- **Dùng `1` thay vì `1U`:** `1 << 31` là `int` có dấu, gây hành vi không xác định. Luôn dùng `1U` (hoặc `1UL` cho 32 bit trở lên).
- **Thiếu ngoặc do độ ưu tiên toán tử:** `==` ưu tiên cao hơn `&`.

```c
if (reg & MASK == MASK)     /* SAI: thành reg & (MASK == MASK) */
if ((reg & MASK) == MASK)   /* ĐÚNG */
```

- **Dịch quá độ rộng kiểu:** `uint8_t` dịch trái 8 bit trở lên, hoặc dịch số âm, đều là hành vi không rõ ràng. Phép toán bit nên làm trên kiểu `uintN_t` không dấu.
- **Integer promotion:** `uint8_t` được nâng lên `int` trước khi tính, nên `~reg8` ra kết quả `int` với các bit cao là 1; cần ép kiểu lại `(uint8_t)(~reg8)`.

## 5. Ứng dụng trong Embedded C

- **Cấu hình thanh ghi ngoại vi:** gần như mọi thao tác điều khiển phần cứng đều là thao tác bit.

```c
/* Cấu hình PA5 là output (MODER bits [11:10] = 01) */
GPIOA_MODER &= ~(0x3U << (5 * 2));      /* xóa 2 bit cũ */
GPIOA_MODER |=  (0x1U << (5 * 2));      /* ghi giá trị 01 */

/* Bật LED trên PA5 */
GPIOA_ODR |= (1U << 5);

/* Đọc nút bấm ở PA0 */
if (GPIOA_IDR & (1U << 0)) { /* nút đang được nhấn */ }
```

  Mẫu "xóa trường bằng `& ~mask` rồi ghi giá trị bằng `|=`" là **đọc – sửa – ghi (read-modify-write)**, dùng thường xuyên để chỉ đổi đúng các bit cần đổi mà không phá bit khác.
- **Cờ trạng thái (flag) tiết kiệm RAM:** nhồi 8 cờ boolean vào một `uint8_t` thay vì 8 biến.

```c
#define FLAG_RX_DONE   BIT(0)
#define FLAG_TX_BUSY   BIT(1)
#define FLAG_ERROR     BIT(2)

uint8_t flags = 0;
flags |= FLAG_RX_DONE;
if (flags & FLAG_ERROR) { /* xử lý lỗi */ }
```

- **Phân tích/đóng gói dữ liệu giao thức:** tách byte header thành các trường (loại gói, độ dài, cờ), ghép các giá trị thành một từ 32 bit gửi qua SPI/I2C/CAN.
- **Che bit chưa dùng (mask) khi đọc ADC/cảm biến:** ví dụ ADC 12 bit nằm trong thanh ghi 16 bit: `value = raw & 0x0FFF;`.
- **Tạo cấu hình bằng cách OR nhiều cờ:** `UART_CTRL = UART_EN | UART_TX_EN | UART_RX_EN;`
- **Lưu ý với `volatile` và ngắt:** thanh ghi phần cứng phải khai báo `volatile`. Phép `reg |= mask` là *đọc – sửa – ghi*, **không nguyên tử**; nếu ngắt (ISR) cũng sửa cùng thanh ghi/biến có thể xảy ra mất cập nhật. Cách xử lý: tắt ngắt tạm thời quanh đoạn đó, dùng thanh ghi set/clear riêng của chip (như `BSRR` trên STM32), hoặc bit-banding trên Cortex-M3/M4.
- **Bit field của `struct`** (`unsigned a : 3;`) cũng tồn tại nhưng thứ tự bit và căn chỉnh phụ thuộc compiler nên kém di động; trong code cần chính xác với phần cứng, dùng mask + shift được ưa chuộng hơn.
