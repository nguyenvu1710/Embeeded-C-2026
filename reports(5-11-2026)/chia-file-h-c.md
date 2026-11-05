# CHIA FILE .H VÀ .C: TÁCH KHAI BÁO VÀ PHẦN XỬ LÍ

## 1. Tại sao cần chia file

Khi chương trình có nhiều chức năng, chia file giúp mã dễ tìm, dễ bảo trì và có thể dùng lại ở nhiều nơi. Thông thường:

- File `.h` chứa phần giao tiếp như khai báo hàm, kiểu dữ liệu và macro để các file khác có thể dùng.
- File `.c` chứa định nghĩa hàm và phần xử lí. File này include `.h` tương ứng để kiểm tra khai báo thống nhất với định nghĩa.

## 2. Ví dụ chia chức năng sensor

File `sensor.h`:

```c
#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

typedef struct {
    uint8_t id;
    float temp;
} Sensor;

void sensor_set_temperature(Sensor *sensor, float value);

#endif
```

File `sensor.c`:

```c
#include "sensor.h"
#include <stddef.h>

void sensor_set_temperature(Sensor *sensor, float value)
{
    if (sensor == NULL) {
        return;
    }
    sensor->temp = value;
}
```

File `main.c`:

```c
#include <stdio.h>
#include "sensor.h"

int main(void)
{
    Sensor sensor = {.id = 1, .temp = 22.5f};
    sensor_set_temperature(&sensor, 25.0f);
    printf("Sensor %u: %.1f C\n", (unsigned int)sensor.id, sensor.temp);
    return 0;
}
```

`#ifndef`, `#define` và `#endif` tạo include guard, giúp tránh khai báo lại khi cùng một header được include nhiều lần trong một file nguồn. Không nên đặt định nghĩa hàm thông thường hoặc định nghĩa biến toàn cục dùng chung trong header, vì có thể gây lỗi trùng định nghĩa khi liên kết.

## 3. Biên dịch các file

Đặt ba file trên trong cùng thư mục, sau đó biên dịch và liên kết các file `.c`:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic main.c sensor.c -o sensor
```

File `.h` được đưa vào qua `#include`, không cần biên dịch riêng. Nếu chỉ biên dịch `main.c` mà không liên kết `sensor.c`, chương trình sẽ thiếu định nghĩa của `sensor_set_temperature`.

> Trong Embedded C, cách chia này giúp tách phần giao tiếp của driver khỏi phần xử lí phần cứng, để các phần khác của chương trình dễ sử dụng lại.
