# 02. Macro (tiền xử lý)

## 1. Mục tiêu

- Hiểu macro là gì và nó được xử lý **trước** khi biên dịch.
- Viết được macro hằng số, macro có tham số, macro biên dịch có điều kiện.
- Biết các bẫy thường gặp (ngoặc, side effect) và cách tránh.
- Biết macro được dùng ở đâu trong lập trình nhúng.

## 2. Khái niệm

- **Preprocessor (bộ tiền xử lý):** bước chạy trước compiler, xử lý các dòng bắt đầu bằng `#`.
- **Macro:** một tên được `#define` để preprocessor **thay thế bằng văn bản** khác.
  - **Object-like macro:** thay một tên bằng một giá trị/biểu thức (hằng số).
  - **Function-like macro:** macro có tham số, trông giống hàm.
- **Biên dịch có điều kiện (conditional compilation):** `#if`, `#ifdef`, `#ifndef`, `#else`, `#elif`, `#endif` – chọn đoạn code nào được đưa vào compiler.
- **Toán tử `#` (stringify)** và **`##` (token pasting)**.
- **Macro định nghĩa sẵn:** `__FILE__`, `__LINE__`, `__DATE__`, `__TIME__`, `__func__` (C99).

## 3. Cú pháp

```c
/* 1. Object-like */
#define SYS_CLOCK_HZ   72000000UL
#define BUFFER_SIZE    64

/* 2. Function-like: LUÔN bọc ngoặc tham số và cả biểu thức */
#define SQUARE(x)      ((x) * (x))
#define MAX(a, b)      (((a) > (b)) ? (a) : (b))
#define ARRAY_SIZE(a)  (sizeof(a) / sizeof((a)[0]))

/* 3. Macro nhiều câu lệnh: dùng do { } while (0) */
#define SWAP(t, a, b)  do { t _tmp = (a); (a) = (b); (b) = _tmp; } while (0)

/* 4. Toán tử # và ## */
#define TO_STR(x)      #x                 /* TO_STR(abc)  -> "abc"     */
#define CONCAT(a, b)   a##b               /* CONCAT(led, 1) -> led1    */

/* 5. Biên dịch có điều kiện */
#define DEBUG 1

#if DEBUG
    #define LOG(msg)  printf("[%s:%d] %s\n", __FILE__, __LINE__, msg)
#else
    #define LOG(msg)  ((void)0)
#endif

#ifdef BOARD_A
    #define LED_PIN 5
#elif defined(BOARD_B)
    #define LED_PIN 13
#else
    #error "Chua chon board"
#endif

/* 6. Hủy định nghĩa */
#undef DEBUG
```

## 4. Cơ chế hoạt động

- Preprocessor chỉ làm việc trên **văn bản (text)**: tìm tên macro rồi thay bằng phần thân, **không kiểm tra kiểu, không tính toán**. Compiler chỉ thấy kết quả sau khi thay.
- Với macro có tham số, đối số được thay nguyên văn vào thân macro. Vì vậy thiếu ngoặc sẽ sai:

```c
#define BAD_SQUARE(x)  x * x
int r = BAD_SQUARE(2 + 3);   /* thành 2 + 3 * 2 + 3 = 11, không phải 25 */

#define SQUARE(x)  ((x) * (x))
int r2 = SQUARE(2 + 3);      /* thành ((2 + 3) * (2 + 3)) = 25 */
```

- **Side effect:** đối số có thể bị tính nhiều lần.

```c
int a = 3;
int m = MAX(a++, 2);   /* thành (((a++) > (2)) ? (a++) : (2)) -> a++ chạy 2 lần */
```

- **Vì sao dùng `do { } while (0)`:** để macro nhiều câu lệnh hoạt động như **một** câu lệnh, dùng an toàn trong `if/else` không ngoặc nhọn và vẫn bắt buộc có dấu `;` khi gọi.
- **Xem kết quả tiền xử lý:** `gcc -E main.c` in ra code sau khi thay macro, rất hữu ích để debug macro.
- **So sánh với hàm:**

| | Macro | Hàm |
|---|---|---|
| Thời điểm xử lý | Tiền xử lý (thay văn bản) | Biên dịch / chạy |
| Kiểm tra kiểu | Không | Có |
| Tốc độ gọi | Không có overhead gọi hàm | Có overhead (có thể `inline`) |
| Kích thước code | Có thể phình ra do lặp | Gọn hơn |
| Debug | Khó | Dễ |

## 5. Ứng dụng trong Embedded C

- **Hằng số cấu hình phần cứng:** tần số clock, baudrate, kích thước buffer, số kênh ADC... đặt bằng `#define` (không tốn RAM, tính được lúc biên dịch, dùng làm kích thước mảng).
- **Định nghĩa địa chỉ thanh ghi:** đây là ứng dụng kinh điển nhất.

```c
#define GPIOA_BASE   0x40020000UL
#define GPIOA_ODR    (*(volatile uint32_t *)(GPIOA_BASE + 0x14))

GPIOA_ODR |= (1U << 5);   /* bật chân PA5 */
```

  Ép địa chỉ thành con trỏ `volatile` rồi dereference, nên `GPIOA_ODR` dùng như một biến nhưng thực chất truy cập thẳng thanh ghi.
- **Biên dịch có điều kiện theo board/chip/chế độ:** một codebase chạy được trên nhiều phần cứng (`#ifdef BOARD_A`), bật/tắt tính năng debug, log. Bản release loại bỏ hoàn toàn code debug nên không tốn flash.
- **Macro thao tác bit:** `SET_BIT`, `CLEAR_BIT`... (xem file bitmask).
- **Macro log/assert:** dùng `__FILE__`, `__LINE__` để biết lỗi ở đâu (xem file assert).
- **Include guard:** chính là `#ifndef / #define / #endif` (xem file chia file).
- **`ARRAY_SIZE`, `MIN`, `MAX`, `UNUSED(x)`:** tiện ích có mặt ở gần như mọi project.
- **Khi không có overhead gọi hàm là quan trọng:** những thao tác cực ngắn trong ISR (đọc/ghi một thanh ghi) hay dùng macro hoặc `static inline` để giảm chi phí gọi hàm và stack.
- **Lưu ý:** MISRA C khuyến khích hạn chế macro có tham số, ưu tiên `static inline` và `const` khi có thể vì an toàn kiểu; nếu dùng macro thì phải bọc ngoặc đầy đủ và tránh truyền biểu thức có side effect.
