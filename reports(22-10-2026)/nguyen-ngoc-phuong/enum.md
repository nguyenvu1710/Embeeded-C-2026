# ENUM: GÁN CÁC TÊN GỌI CHO TẬP HỢP CÁC SỐ NGUYÊN

## 1. Cú pháp khai báo
```c
typedef enum {
    sensor_idle, 
    sensor_ready,
    sensor_error
} sensor_state;
sensor_state state = sensor_ready;
```
Trong trường hợp không có giá trị đại diện, enum xác định số từ 0 -> n-1 với n trạng thái

## 2. Khi nào nên dùng enum

Khi cần mô tả các lựa chọn có tên như: trạng thái, chế độ, mã lệnh, `switch case`,...

> Trong Embedded C, `enum` dùng để điều khiển luồng hoạt động, ví dụ động cơ có các luồng như `MOTOR-IDLE`, `MOTOR-RUNNING`, `MOTOR-ERROR`