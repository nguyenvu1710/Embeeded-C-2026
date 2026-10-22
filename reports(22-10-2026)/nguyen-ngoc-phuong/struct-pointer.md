# STRUCT POINTER: XỬ LÍ DỮ LIỆU STRUCT THÔNG QUA ĐỊA CHỈ

## 1. Cách khai báo và sửa dữ liệu

```c
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t id;
    float temp;
    uint8_t enabled;
} Sensor;

Sensor sensor[2] = {  
    {.id = 1, .temp = 22.5f, .enabled = 1},
    {.id = 2, .temp = 21.0f, .enabled = 1}

};
Sensor *p = &sensors[0]
p -> temp = 25.0f; //Lệnh sửa temp từ 22.5 thành 25. Lệnh (*p).temp <=> p -> temp
```
## 2.Truyền struct vào hàm  

Nếu không dùng pointer, ta có ví dụ sau:
```c
void sensor_set_temperature(Sensor sensor, float value)
{

    sensor.temp = value;
}
int main(){
    sensor_set_temperature(sensor[0], 40.0f);
}
```
Giá trị temp trả về vẫn là 25.0, bởi vậy nếu muốn sửa temp ta cần phải dùng con trỏ
```c
void sensor_set_temperature(Sensor *sensor, float value)
{
    if (sensor == NULL) {
        return;
    }

    sensor->temp = value;
}

int main() {
    sensor_set_temperature(&sensor[0], 40.0f);
}
```
> Trong Embedded C, struct pointer thường dùng để gom các dữ liệu bên trong thanh ghi phần cứng