# 04. Assert

## 1. Mục tiêu

- Hiểu assert dùng để kiểm tra **giả định của lập trình viên** trong lúc phát triển.
- Dùng được `assert()` chuẩn và `static_assert`.
- Tự viết được macro assert phù hợp với hệ nhúng (không có màn hình/console).
- Phân biệt assert với xử lý lỗi runtime thông thường.

## 2. Khái niệm

- **Assertion (khẳng định):** một biểu thức mà lập trình viên cho rằng **luôn đúng** tại điểm đó của chương trình. Nếu sai nghĩa là có **bug**, chương trình dừng/báo lỗi ngay.
- **`assert()`:** macro chuẩn trong `<assert.h>`, kiểm tra tại **thời điểm chạy (runtime)**.
- **`static_assert` (C11, `_Static_assert`):** kiểm tra tại **thời điểm biên dịch**, biểu thức phải là hằng số.
- **`NDEBUG`:** macro dùng để vô hiệu hóa toàn bộ `assert()` (bản release).
- **Phân biệt:**
  - *Assert:* bắt lỗi lập trình (bug) – "việc này không bao giờ được xảy ra".
  - *Xử lý lỗi (if/else, mã lỗi):* bắt tình huống có thể xảy ra thật khi chạy (timeout, dữ liệu sai từ bên ngoài, cảm biến hỏng).

## 3. Cú pháp

```c
#include <assert.h>

void Uart_Send(const uint8_t *buf, uint16_t len)
{
    assert(buf != NULL);       /* con trỏ không được NULL */
    assert(len > 0 && len <= 256);
    /* ... */
}
```

```c
/* Kiểm tra lúc biên dịch (C11) */
#include <assert.h>
#include <stdint.h>

typedef struct {
    uint8_t  id;
    uint32_t value;
} Packet_t;

static_assert(sizeof(uint32_t) == 4, "uint32_t phai la 4 byte");
static_assert(sizeof(Packet_t) == 8, "Packet_t bi padding ngoai du kien");
```

**Tự viết macro assert cho embedded:**

```c
#ifdef USE_ASSERT
    void Assert_Failed(const char *file, int line);   /* định nghĩa ở 1 file .c */

    #define ASSERT(expr) \
        ((expr) ? (void)0 : Assert_Failed(__FILE__, __LINE__))
#else
    #define ASSERT(expr) ((void)0)
#endif
```

```c
void Assert_Failed(const char *file, int line)
{
    __disable_irq();                 /* dừng ngắt */
    /* ghi file/line ra UART, bật LED báo lỗi, hoặc để breakpoint ở đây */
    while (1) { }                    /* treo để debug */
}
```

**Tắt assert khi build release:**

```bash
gcc -DNDEBUG main.c -o app
```

## 4. Cơ chế hoạt động

- `assert(expr)` thực chất là một macro, mở rộng gần giống:

```c
/* khi KHÔNG định nghĩa NDEBUG */
((expr) ? (void)0 : __assert_fail(#expr, __FILE__, __LINE__, __func__))

/* khi có NDEBUG */
((void)0)
```

- Nếu `expr` đúng: không làm gì, chương trình tiếp tục. Nếu sai: gọi hàm báo lỗi (in `file:line: biểu thức` ra `stderr`) rồi `abort()` chương trình.
- Nhờ `#expr` (stringify) mà thông báo hiển thị đúng nguyên văn biểu thức bị sai; `__FILE__`, `__LINE__` do preprocessor điền sẵn vị trí gọi.
- **Hệ quả quan trọng khi có `NDEBUG`:** cả biểu thức bên trong **biến mất**, không được tính. Vì vậy **không được đặt câu lệnh có side effect trong assert**:

```c
assert(Uart_Init() == OK);   /* SAI: ở bản release Uart_Init() không bao giờ được gọi */

Status_t st = Uart_Init();   /* ĐÚNG */
assert(st == OK);
```

- `static_assert` được compiler đánh giá khi biên dịch; nếu sai thì **không biên dịch được**, không tốn byte code hay thời gian chạy nào.

## 5. Ứng dụng trong Embedded C

- **Hệ nhúng thường không có `stderr`/`abort()` đúng nghĩa:** `assert()` chuẩn cần thư viện, console và hệ điều hành. Vì vậy thực tế hay **tự định nghĩa** macro `ASSERT` và hàm `Assert_Failed()` để quyết định hành vi: dừng bằng vòng lặp vô hạn (gắn debugger xem call stack), ghi lỗi vào flash/RAM không bị xóa, in qua UART, bật LED lỗi, hoặc reset chip. Thư viện STM32 HAL dùng đúng mô hình này với `assert_param()` và `assert_failed(file, line)`.
- **Kiểm tra tham số đầu vào của hàm driver:** con trỏ khác `NULL`, chỉ số kênh/chân nằm trong phạm vi, độ dài buffer hợp lệ, trạng thái module đã khởi tạo chưa. Lỗi cấu hình sai sẽ lộ ra ngay lúc phát triển thay vì gây hỏng ngầm khó dò.
- **Kiểm tra bất biến (invariant):** chỉ số buffer vòng không vượt kích thước, state machine không ở trạng thái không hợp lệ (`default:` của `switch` gọi `ASSERT(0)`).
- **`static_assert` rất hữu ích cho phần cứng:** xác nhận `sizeof` kiểu dữ liệu và `struct` (đặc biệt khi `struct` ánh xạ vào thanh ghi hoặc gói tin), kiểm tra kích thước buffer là lũy thừa 2, kiểm tra cấu hình `#define` hợp lệ. Lỗi bị chặn từ lúc biên dịch, không tốn flash/RAM.
- **Cân nhắc tài nguyên:** mỗi assert tốn flash (chuỗi `__FILE__`, hàm gọi) và thời gian chạy. Chiến lược thông dụng: bật trong bản debug, tắt trong bản release; hoặc giữ ở mức nhẹ (chỉ lưu số dòng, không lưu chuỗi tên file).
- **Không dùng assert cho lỗi runtime có thể xảy ra thật:** timeout giao tiếp, checksum sai, cảm biến mất kết nối… phải dùng mã trả về/xử lý lỗi, vì ở bản release assert đã bị tắt. Trong sản phẩm an toàn, hành vi khi lỗi thường là đưa hệ thống về trạng thái an toàn rồi reset (kết hợp watchdog), không nên treo vô thời hạn.
