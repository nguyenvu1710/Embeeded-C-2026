# BITMASK: DÙNG CÁC BIT ĐỂ LƯU TRỮ TRẠNG THÁI

## 1. Bitmask là gì

Bitmask là một giá trị có các bit được chọn để biểu diễn hoặc kiểm tra trạng thái. Mỗi bit có thể dùng cho một trạng thái bật/tắt, nên nhiều trạng thái có thể được lưu trong cùng một biến.

Ví dụ `1u << 0` tạo giá trị `0001`, còn `1u << 1` tạo giá trị `0010`. Các bit được đánh số từ 0, tính từ phải sang trái.

## 2. Các thao tác với bitmask

```c
#include <stdio.h>

#define MOTOR_ENABLE (1u << 0) // Bit 0: động cơ được bật
#define MOTOR_ERROR  (1u << 1) // Bit 1: động cơ có lỗi

int main(void)
{
    unsigned int status = 0u;

    status |= MOTOR_ENABLE; // Đặt bit MOTOR_ENABLE thành 1
    status |= MOTOR_ERROR;  // Đặt bit MOTOR_ERROR thành 1

    if ((status & MOTOR_ERROR) != 0u) { // Kiểm tra bit có bằng 1 không
        printf("Motor error\n");
    }

    status &= ~MOTOR_ERROR; // Xóa bit MOTOR_ERROR về 0
    status ^= MOTOR_ENABLE; // Đảo bit MOTOR_ENABLE từ 1 thành 0

    return 0;
}
```

`|` dùng để đặt bit, `&` dùng để kiểm tra hoặc xóa bit, `~` đảo các bit của mask và `^` dùng để đảo bit được chọn. Sử dụng kiểu số nguyên không dấu và chỉ dịch trong phạm vi số bit của kiểu đó.
| giúp chọn đúng bit cần thay đổi vì một biến có thể chứa nhiều trạng thái cùng lúc.

> Trong Embedded C, bitmask thường dùng để kiểm tra trạng thái và cấu hình thanh ghi. Bitmask giúp chọn bit cần sửa mà không can thiệp vào các bit khác
> 
