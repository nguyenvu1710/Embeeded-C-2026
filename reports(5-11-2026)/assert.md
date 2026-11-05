# ASSERT: KIỂM TRA GIẢ ĐỊNH KHI CHƯƠNG TRÌNH CHẠY

## 1. Cú pháp và cách hoạt động

`assert` được khai báo trong thư viện `<assert.h>`, dùng để kiểm tra một điều kiện mà lập trình viên cho rằng phải đúng tại vị trí đó.

```c
#include <assert.h>
#include <stdio.h>

float sensor_average(float total, int count)
{
    assert(count > 0); // count phải lớn hơn 0 trước khi chia
    return total / count;
}

int main(void)
{
    printf("Average: %.1f\n", sensor_average(75.0f, 3));
    return 0;
}
```

Nếu điều kiện đúng, chương trình tiếp tục chạy. Nếu điều kiện sai, `assert` thông báo vị trí lỗi và dừng chương trình bằng `abort()`.
Assert tương đương với dùng if.

## 2. Khi nào nên dùng `assert`

Dùng để phát hiện lỗi lập trình, ví dụ kiểm tra giả định về con trỏ hoặc dữ liệu nội bộ. Với dữ liệu người dùng nhập hoặc lỗi có thể xảy ra khi chạy, cần xử lí bằng `if` và trả về lỗi phù hợp.

Khi định nghĩa `NDEBUG` trước khi include `<assert.h>` hoặc biên dịch với `-DNDEBUG`, `assert` bị vô hiệu hóa và biểu thức bên trong không được tính. Vì vậy không đặt thao tác cần thiết như `i++` bên trong `assert`.

> Trong Embedded C, `assert` có thể hỗ trợ tìm lỗi khi phát triển; cách hiển thị thông báo và dừng chương trình phụ thuộc vào môi trường chạy.
