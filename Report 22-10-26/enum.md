# Enum

## 1.Mục tiêu

* Hiểu cách tạo các tập hợp hằng số có tên đại diện trực quan.
* Tăng tính minh bạch, dễ đọc và dễ bảo trì cho mã nguồn.
* Sử dụng enum kết hợp với câu lệnh điều kiện `switch-case`.

## 2.Khái niệm

* enum (Enumeration) là kiểu dữ liệu liệt kê cho phép gán các tên gợi nhớ cho các giá trị hằng số số nguyên (`int`).

## 3.Cú pháp

Cú pháp khai báo: `enum EnumName { CONSTANT1, CONSTANT2, CONSTANT3 };`

Cách sử dụng: `enum EnumName variable_name = CONSTANT1;`

## 4.Cơ chế hoạt động

* Mặc định, giá trị đầu tiên trong enum gán bằng 0, các giá trị tiếp theo tự động tăng lên 1.
* Người dùng có thể gán giá trị số nguyên cụ thể cho bất kỳ phần tử nào trong enum.
* Trình biên dịch sẽ thay thế các tên hằng số bằng giá trị số nguyên tương ứng khi biên dịch.

## 5.Ví dụ minh họa

```c
#include <stdio.h>

enum State {
    IDLE = 0,
    RUNNING = 1,
    ERROR = -1
};

int main() {
    enum State current_state = RUNNING;

    if (current_state == RUNNING) {
        printf("He thong dang hoat dong...\n");
    }

    return 0;
}
```

## 6.Ứng dụng thực tế

* Xây dựng các máy trạng thái (State Machine) trong lập trình hệ thống và vi điều khiển.
* Quản lý các mã lỗi return từ hàm (Success, Timeout, Fail,...).
