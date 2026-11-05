# CẤP PHÁT ĐỘNG: XIN VÙNG NHỚ KHI CHƯƠNG TRÌNH ĐANG CHẠY

## 1. Các hàm cấp phát và giải phóng

Cấp phát động cho phép xin vùng nhớ khi chạy chương trình và sử dụng thông qua con trỏ. Các hàm sau nằm trong `<stdlib.h>`:

| Hàm | Công dụng |
| --- | --- |
| `malloc` | Cấp phát số byte yêu cầu; nội dung ban đầu chưa được khởi tạo |
| `calloc` | Cấp phát cho nhiều phần tử và đặt các byte ban đầu bằng 0 |
| `realloc` | Thay đổi kích thước vùng nhớ đã cấp phát |
| `free` | Giải phóng vùng nhớ đã cấp phát |

## 2. Ví dụ dùng `malloc`

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *number = malloc(sizeof(int)); // Cấp phát bộ nhớ cho 1 số int
    
    *number = 10;
    printf("%d\n", *number); // Kết quả: 10

    free(number); // Giải phóng vùng nhớ
    return 0;
}
```

`malloc(sizeof(int))` xin vùng nhớ đủ để chứa một số nguyên. Vì vùng nhớ chưa được khởi tạo, ta gán `10` trước khi đọc.

## 3. Ví dụ dùng `calloc`

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *numbers = calloc(3, sizeof(int)); // Cấp phát cho 3 số int

    printf("%d %d %d\n", numbers[0], numbers[1], numbers[2]); // 0 0 0

    free(numbers); // Giải phóng vùng nhớ
    return 0;
}
```

`calloc(3, sizeof(int))` xin vùng nhớ cho 3 số nguyên và đặt các byte ban đầu bằng 0. Vì vậy, trong ví dụ này, cả 3 số đều có giá trị `0`.

## 4. Ví dụ dùng `realloc`

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *numbers = malloc(sizeof(int)); // Cấp phát cho 1 số int
    numbers[0] = 10;

    int *temp = realloc(numbers, 2 * sizeof(int)); // Đổi thành 2 số int
    numbers = temp;

    numbers[1] = 20;
    printf("%d %d\n", numbers[0], numbers[1]); // Kết quả: 10 20

    free(numbers);
    return 0;
}
```

`realloc` thay đổi kích thước vùng nhớ và giữ lại dữ liệu cũ trong phạm vi kích thước mới. Vùng nhớ có thể được chuyển sang địa chỉ khác, nên sau khi thành công ta gán `temp` cho `numbers`. Nếu thất bại, `temp` là `NULL` và vùng nhớ cũ vẫn còn để giải phóng.

## 5. Lưu ý khi sử dụng

Nếu cấp phát thất bại, `malloc` hoặc `calloc` trả về `NULL`. Cần kiểm tra trước khi dùng con trỏ, gọi `free` khi không còn dùng và không truy cập vùng nhớ sau `free`.

Với `realloc` có kích thước mới lớn hơn 0, nên dùng con trỏ tạm để không làm mất địa chỉ cũ nếu cấp phát thất bại. Khi kích thước được nhập hoặc tính lúc chạy, cần kiểm tra phép nhân số lượng với kích thước phần tử không bị tràn.

> Trong Embedded C, bộ nhớ thường hạn chế; cấp phát động có thể gây phân mảnh và khó dự đoán thời gian. Tùy hệ thống, có thể ưu tiên vùng nhớ tĩnh khi cần hành vi dễ dự đoán.
