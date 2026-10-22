# STRUCT: GOM NHIỀU THÔNG TIN CỦA CÙNG MỘT ĐỐI TƯỢNG
> Struct trong C và Embedded C không khác nhau về cách hoạt động, đều là nơi lưu trữ thông tin

## 1. Tại sao lại dùng `struct`

Ví dụ một sensor đo nhiệt độ có 3 thông tin: id, nhiệt độ, trạng thái bật tắt. Nếu có 10,100 cảm biến, ta không thể khai báo từng đấy sensors được, đó là lí do cần dùng struct, để lưu thông của 1 đối tượng mà các đối tượng khác cũng có kiểu thông tin tương tự.

## 2. Cú pháp khai báo `struct`

```c
#include <stdint.h>

typedef struct {
    uint8_t id;
    float temp;
    uint8_t enabled;
} Sensor;

Sensor sensor[2] = { //Tạo mảng sensor số lượng là 2, nhưng khi gọi vẫn gọi theo thứ tự là sensors[0], sensors[1] 
    {.id = 1, .temp = 22.5f, .enabled = 1},
    {.id = 2, .temp = 21f, .enabled = 1}

};
```
Ngoài cách khai báo bằng `typedef`, ta có thể khai báo như sau `struct Sensor {}`

> Trong Embedded C, `struct` dùng để gom cấu hình và trạng thái của thiết bị.