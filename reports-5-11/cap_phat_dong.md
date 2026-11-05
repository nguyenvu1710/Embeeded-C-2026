# 05. Cấp phát động (Dynamic Memory Allocation)

## 1. Mục tiêu

- Hiểu sự khác nhau giữa bộ nhớ tĩnh, stack và heap.
- Dùng đúng `malloc`, `calloc`, `realloc`, `free`.
- Nhận biết các lỗi bộ nhớ phổ biến (leak, dangling pointer, double free, tràn).
- Hiểu **vì sao hệ nhúng thường hạn chế cấp phát động** và có những giải pháp thay thế nào.

## 2. Khái niệm

- **Cấp phát tĩnh:** biến toàn cục / `static`, kích thước và vị trí cố định ngay lúc biên dịch, tồn tại suốt chương trình (vùng `.data`, `.bss`).
- **Stack:** biến cục bộ, tự cấp phát khi vào hàm và tự giải phóng khi thoát hàm.
- **Heap:** vùng nhớ lập trình viên **tự xin và tự trả** lúc chạy, kích thước quyết định tại runtime, tồn tại đến khi `free`.
- **Các hàm trong `<stdlib.h>`:**

| Hàm | Chức năng |
|---|---|
| `malloc(size)` | Xin `size` byte, nội dung **chưa khởi tạo** |
| `calloc(n, size)` | Xin `n * size` byte, **khởi tạo toàn bộ về 0** |
| `realloc(ptr, size)` | Đổi kích thước vùng nhớ đã cấp |
| `free(ptr)` | Trả vùng nhớ về heap |

- **Memory leak:** xin mà không trả. **Dangling pointer:** con trỏ vẫn giữ địa chỉ vùng đã `free`. **Double free:** `free` hai lần cùng một vùng. **Phân mảnh (fragmentation):** heap còn tổng dung lượng trống đủ nhưng bị chia lẻ, không có khối liền mạch đủ lớn.

## 3. Cú pháp

```c
#include <stdlib.h>
#include <string.h>

/* Cấp phát mảng 10 phần tử */
int *arr = (int *)malloc(10 * sizeof(int));
if (arr == NULL) {
    /* hết bộ nhớ: PHẢI xử lý */
    return;
}

/* calloc: tự xóa về 0 */
int *zeros = (int *)calloc(10, sizeof(int));

/* Thay đổi kích thước */
int *tmp = (int *)realloc(arr, 20 * sizeof(int));
if (tmp == NULL) {
    free(arr);          /* realloc thất bại thì vùng cũ vẫn còn, phải tự free */
    return;
}
arr = tmp;              /* dùng biến tạm để không mất con trỏ cũ */

/* Giải phóng */
free(arr);
arr = NULL;             /* tránh dangling pointer / double free */
free(zeros);
zeros = NULL;
```

**Cấp phát cho struct:**

```c
typedef struct {
    uint8_t *data;
    uint16_t len;
} Buffer_t;

Buffer_t *Buffer_Create(uint16_t len)
{
    Buffer_t *b = (Buffer_t *)malloc(sizeof(Buffer_t));
    if (b == NULL) return NULL;
    b->data = (uint8_t *)malloc(len);
    if (b->data == NULL) { free(b); return NULL; }
    b->len = len;
    return b;
}

void Buffer_Destroy(Buffer_t *b)
{
    if (b != NULL) {
        free(b->data);
        free(b);
    }
}
```

## 4. Cơ chế hoạt động

**Bố cục bộ nhớ của một chương trình:**

```
Địa chỉ cao   +------------------+
              |      Stack       |  <- lớn dần xuống (biến cục bộ, địa chỉ trả về)
              |        |         |
              |        v         |
              |   (vùng trống)   |
              |        ^         |
              |        |         |
              |       Heap       |  <- lớn dần lên (malloc/free)
              +------------------+
              |  .bss  (biến toàn cục chưa khởi tạo = 0)
              |  .data (biến toàn cục có giá trị khởi tạo)
              |  .text (code, hằng số - nằm trong Flash trên MCU)
Địa chỉ thấp  +------------------+
```

- **`malloc`** hỏi bộ quản lý heap (allocator). Allocator duy trì **danh sách các khối trống (free list)**, tìm khối đủ lớn (first-fit, best-fit...), cắt ra phần cần dùng, ghi **thông tin quản lý (header: kích thước khối)** ngay trước vùng trả về, rồi trả con trỏ cho người dùng. Khi hết chỗ, allocator xin thêm từ hệ điều hành (trên PC dùng `brk/sbrk` hoặc `mmap`).
- **`free`** đánh dấu khối đó là trống, đưa lại vào free list và có thể gộp (coalesce) với khối trống kề bên.
- **Phân mảnh xảy ra như thế nào:** cấp phát và giải phóng các khối kích thước khác nhau xen kẽ sẽ để lại nhiều "lỗ hổng" nhỏ. Về sau xin khối lớn có thể thất bại dù tổng bộ nhớ trống vẫn nhiều.
- **Trên vi điều khiển bare-metal:** không có hệ điều hành cấp thêm bộ nhớ. Vùng heap thường được xác định trong **linker script** (ví dụ `_Min_Heap_Size`), và hàm `_sbrk()` của newlib dịch con trỏ "đỉnh heap" trong phạm vi RAM còn dư (giữa `.bss` và stack). Nếu heap và stack lớn dần chạm nhau, chương trình hỏng một cách khó đoán.
- **Các lỗi phổ biến:**

```c
int *p = malloc(sizeof(int));
free(p);
*p = 5;          /* dangling pointer: truy cập sau khi free */
free(p);         /* double free */

int *q = malloc(100);
q = malloc(200); /* mất con trỏ vùng 100 byte đầu: memory leak */

char *s = malloc(5);
strcpy(s, "hello");  /* cần 6 byte (kể cả '\0'): tràn buffer */
```

## 5. Ứng dụng trong Embedded C

- **Tư duy chung: tránh dùng cấp phát động nếu có thể.** Nhiều tiêu chuẩn (ví dụ MISRA C) cấm hoặc hạn chế `malloc/free` vì các lý do sau:
  - **RAM rất ít** (vài KB đến vài trăm KB), không có chỗ cho phí tổn quản lý heap.
  - **Phân mảnh heap** làm hệ thống chạy lâu ngày bị hết bộ nhớ dù lúc đầu vẫn ổn (nguy hiểm với thiết bị chạy liên tục nhiều tháng).
  - **Thời gian cấp phát không xác định (non-deterministic):** vi phạm yêu cầu thời gian thực, đặc biệt trong ISR (không bao giờ gọi `malloc` trong ngắt).
  - **Khó phát hiện lỗi:** leak/dangling pointer chỉ lộ ra sau thời gian dài; MCU không có MMU nên truy cập sai có thể ghi đè bộ nhớ khác mà không báo lỗi.
- **Giải pháp thay thế:**
  - **Mảng/buffer tĩnh** với kích thước tối đa biết trước: đơn giản, an toàn, biết chính xác lượng RAM dùng ngay lúc biên dịch.

    ```c
    static uint8_t rx_buffer[256];
    ```

  - **Memory pool (khối cố định):** cấp sẵn một mảng gồm N khối cùng kích thước; cấp/trả khối bằng danh sách liên kết. Thời gian cấp phát cố định, không phân mảnh.
  - **Ring buffer** cho dữ liệu UART/ADC streaming.
  - **Cấp phát một lần lúc khởi động** rồi không bao giờ `free` (chấp nhận được vì không gây phân mảnh).
- **Khi vẫn dùng cấp phát động:**
  - Trong **RTOS** (FreeRTOS) dùng `pvPortMalloc` / `vPortFree` với các chiến lược heap (heap_1…heap_5); heap_1 chỉ cấp, không free nên không phân mảnh. FreeRTOS cũng hỗ trợ tạo task/queue bằng bộ nhớ tĩnh (`xTaskCreateStatic`).
  - Hệ nhúng lớn hơn (Linux nhúng, SoC nhiều RAM) cấp phát động bình thường.
  - Luôn **kiểm tra giá trị trả về `NULL`**, đặt con trỏ về `NULL` sau `free`, đảm bảo mỗi `malloc` có `free` tương ứng.
- **Cần biết khi viết thư viện/driver:** `printf`, `sprintf` kiểu đầy đủ trong newlib có thể ngầm dùng heap; đây là lý do nhiều dự án dùng bản `nano` hoặc tự viết hàm in.
- **Công cụ kiểm tra:** xem file `.map` (kích thước `.data`, `.bss`, heap, stack), theo dõi mức dùng stack tối đa, bật cảnh báo khi gọi `malloc`.
