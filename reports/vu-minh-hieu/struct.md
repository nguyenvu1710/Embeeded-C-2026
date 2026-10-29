# Struct trong C

## 1. Mục tiêu

- Hiểu `struct` là gì và tại sao cần dùng.
- Biết cách khai báo, khởi tạo và truy cập thành viên struct.
- Biết cách kết hợp `struct` với `typedef`.
- Hiểu struct lồng struct.
- Biết ứng dụng trong Embedded C.

## 2. Khái niệm

`struct` là kiểu dữ liệu cho phép gom nhiều biến, có thể thuộc các kiểu dữ liệu khác nhau, vào chung một nhóm.

Nếu không dùng `struct`, phải quản lý từng biến riêng lẻ. Khi có nhiều thiết bị, việc quản lý sẽ rối hơn.

Ví dụ: quản lý cảm biến — thay vì `cb1_ten`, `cb1_ma_so`, `cb1_status` rồi lặp lại cho 100 cảm biến, có thể gom lại thành 1 đối tượng đại diện.

## 3. Cú pháp

### Khai báo cơ bản:

```c
struct Sensor {
    int id;
    float temperature;    // 3 thành viên
    int status;
};

int main() {
    struct Sensor s1;              // struct Sensor: kiểu cấu trúc, s1: tên biến
    s1.id = 101;
    s1.temperature = 85.5;        // s1.tên_thành_viên: truy cập thành viên
    s1.status = 1;

    return 0;
}
```

### Kết hợp với typedef:

```c
typedef struct {
    float temperature;
    int rpm;
} Engine;

// Không cần viết "struct Engine e1", chỉ cần:
Engine e1;
```

## 4. Struct lồng struct

Với những dữ liệu phân tầng phức tạp, có thể lồng struct trong struct:

```c
typedef struct {
    float temperature;
    int rpm;
} Engine;

typedef struct {
    char name[30];
    int age;
} Driver;

typedef struct {
    Engine engine;    // thành viên tên engine, có kiểu Engine
    Driver driver;    // thành viên tên driver, có kiểu Driver
    int speed;
} Car;
```

### Truy cập:

```c
Car myCar;
myCar.speed = 60;
myCar.engine.rpm = 2500;    // truy cập thành viên của struct lồng
```

## 5. Ví dụ minh họa

```c
#include <stdio.h>

typedef struct {
    int id;
    float temperature;
    int status;
} Sensor;

int main() {
    Sensor s1;
    s1.id = 101;
    s1.temperature = 85.5;
    s1.status = 1;

    printf("Sensor %d: %.1f°C, status=%d\n", s1.id, s1.temperature, s1.status);
    return 0;
}
```

## 6. Ứng dụng thực tế

- Quản lý thông tin nhiều cảm biến trên vi điều khiển.
- Biểu diễn các đối tượng phần cứng (động cơ, driver, xe...).
- Tổ chức dữ liệu phức tạp có cấu trúc phân tầng.
