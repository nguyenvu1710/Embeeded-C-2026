# Union trong C

## 1. Mục tiêu

- Hiểu `union` là gì và khác `struct` ở điểm nào.
- Biết cách khai báo và sử dụng `union`.
- Hiểu cơ chế dùng chung vùng nhớ.
- Biết ứng dụng của `union` trong Embedded C.

## 2. Khái niệm

`union` khá giống `struct` ở chỗ nó gom nhiều thành viên vào một kiểu dữ liệu. Nhưng có một điểm khác biệt cực kỳ quan trọng:

- **`struct`**: lưu riêng từng thành viên (mỗi thành viên có vùng nhớ riêng).
- **`union`**: cho các thành viên **dùng chung một vùng nhớ**.

Nghĩa là khi biến sau được ghi, nó **ghi đè** vào biến trước — biến trước không còn giá trị sử dụng nữa.

## 3. Cú pháp

Khai báo giống `struct`:

```c
typedef union {
    float temperature;
    int rpm;
} Engine;
```

Tuy nhiên 2 thành viên này dùng chung một vùng nhớ.

## 4. Cơ chế hoạt động

```c
Engine data;
data.temperature = 100.1;
data.rpm = 1200;
// Lúc này data.temperature KHÔNG còn bằng 100.1 nữa
// vì rpm đã ghi đè lên cùng vùng nhớ
```

Kích thước của `union` = kích thước của thành viên lớn nhất (khác với `struct` = tổng kích thước các thành viên).

## 5. Ví dụ minh họa

```c
#include <stdio.h>

typedef union {
    float temperature;
    int rpm;
    int error_code;
} SensorData;

int main() {
    SensorData data;

    data.temperature = 100.1;
    printf("Temperature: %.1f\n", data.temperature);

    data.rpm = 1200;
    printf("RPM: %d\n", data.rpm);
    // data.temperature lúc này đã bị ghi đè, không còn đúng

    return 0;
}
```

## 6. Ứng dụng thực tế

Ví dụ một bộ điều khiển ô tô cần xử lý dữ liệu theo nhiều dạng khác nhau nhưng tại mỗi thời điểm chỉ cần một dạng:
- Dữ liệu vòng tua động cơ
- Dữ liệu nhiệt độ
- Mã lỗi

Nếu các dữ liệu đó không cần tồn tại đồng thời, `union` có thể giúp **tiết kiệm RAM** — điều rất quan trọng trong Embedded C khi bộ nhớ cực kỳ hạn chế.
