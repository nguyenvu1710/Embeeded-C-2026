# STDARG: XỬ LÍ HÀM CÓ SỐ LƯỢNG ĐỐI SỐ THAY ĐỔI

## 1. Mục đích của `stdarg`

`stdarg` cung cấp các công cụ để một hàm xử lí **số lượng đối số thay đổi**. Ví dụ, cùng một hàm `sum` có thể cộng 2 số hoặc 3 số:

- `sum(2, 10, 20)`: cộng 2 số `10` và `20`.
- `sum(3, 10, 20, 30)`: cộng 3 số `10`, `20` và `30`.

Trong ví dụ này, số đầu tiên cho biết có bao nhiêu số cần cộng; các số phía sau là dữ liệu cần xử lí. Để dùng các công cụ của `stdarg`, ta include `<stdarg.h>`.

## 2. Các thành phần trong `stdarg`

| Thành phần | Công dụng |
| --- | --- |
| `va_list args` | Khai báo biến `args` để theo dõi vị trí đang đọc các đối số |
| `va_start(args, count)` | Bắt đầu đọc các đối số sau tham số cố định `count` |
| `va_arg(args, int)` | Lấy đối số tiếp theo với kiểu `int`, rồi chuyển đến đối số tiếp theo |
| `va_end(args)` | Kết thúc việc sử dụng `args` sau khi đọc xong |

Trong ví dụ này, `count` là tham số cố định cuối cùng, còn `...` biểu thị phần đối số có số lượng thay đổi.

## 3. Ví dụ dùng `stdarg`

```c
#include <stdarg.h>
#include <stdio.h>

int sum(int count, ...) // count là số lượng đối số phía sau
{
    va_list args;          // Khai báo biến để đọc các đối số
    va_start(args, count); // Bắt đầu đọc sau tham số count

    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int); // Đọc đối số tiếp theo kiểu int
    }

    va_end(args); // Kết thúc sử dụng danh sách đối số
    return total;
}

int main(void)
{
    printf("%d\n", sum(2, 10, 20));     // Kết quả: 30
    printf("%d\n", sum(3, 10, 20, 30)); // Kết quả: 60
    return 0;
}
```

Khi gọi `sum(3, 10, 20, 30)`, `count` bằng `3`. Mỗi lần `va_arg(args, int)` chạy, nó lần lượt lấy `10`, `20`, rồi `30` để cộng vào `total`.

`stdarg` không tự biết số lượng hoặc kiểu của các đối số sau `...`. Người gọi phải truyền đúng số lượng và kiểu mà hàm chờ; truyền sai có thể gây hành vi không xác định.

## 4. Lưu ý về kiểu dữ liệu

Với đối số nằm sau `...`, `float` được chuyển thành `double`; các kiểu nguyên nhỏ như `char` hoặc `short` thường được chuyển thành `int` (hoặc `unsigned int` tùy kiểu và hệ thống). Khi dùng `va_arg`, phải đọc đúng kiểu sau khi chuyển.

> Trong Embedded C, `stdarg` có thể dùng để viết hàm log nhận số lượng dữ liệu khác nhau.
