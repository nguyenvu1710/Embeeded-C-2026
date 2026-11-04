# Struct Pointer trong C

## 1. Mục tiêu

- Hiểu con trỏ đến struct là gì.
- Biết cách khai báo và sử dụng struct pointer.
- Phân biệt toán tử `.` và `->`.
- Biết cách sử dụng con trỏ struct trong hàm.

## 2. Khái niệm
  - Struct pointer là con trỏ trỏ tới một struct.
 Cho phép truy cập và thao tác dữ liệu trong struct thông qua con trỏ, rất hữu ích khi làm việc với hàm hoặc embedded systems.

- Mối quan hệ giữa con trỏ và biến struct:
 + Con trỏ struct lưu trữ địa chỉ của biến struct từ đó cho phép truy cập và sửa đổi trực tiếp dữ liệu bên trong biến mà không cần sao chép.

- Truy cập dữ liệu:
   + Dùng toán tử chấm . khi thao tác trực tiếp trên biến struct 
     ví dụ: 
     ```c
     (structa.age = 20).
     ```
   + Dùng toán tử -> hoặc cú pháp giải tham chiếu (*ptr).field khi làm việc với struct pointer
     ví dụ: 
     ```c
     tr->age = 20 tương đương với (*ptr).age = 20
     ```
 
- Cách địa chỉ bộ nhớ được sử dụng khi làm việc với struct pointer:
 Trong C nhúng, struct pointer trỏ đến địa chỉ cơ sở (byte đầu tiên) của cấu trúc trong bộ nhớ. Địa chỉ này dùng để truy xuất/ghi đè trực tiếp các thành phần qua toán tử ->


## 3. Cú pháp
### Khai báo:
 ```c
 struct Ten_Struct *ten_con_tro;
 ```

### Khởi tạo: 
 Gán địa chỉ biến struct (&bien_struct) hoặc cấp phát động (malloc).

### Truy cập thành viên:
 Dùng toán tử mũi tên (->) với cú pháp 
 ```c
 ten_con_tro->ten_thanh_vien hoặc (*ten_con_tro).ten_thanh_vien.
 ```

Ví dụ:
```c
struct sinhvien{
 int mssv;
 float diem;
}; // khai bao kieu struct

struct sinhvien *prt; //khai báo con trỏ prt (là con trỏ tới struct sinhvien)
//khi truy cap thanh vien co the su dung mot trong hai cach duoi day.
ptr-> diem = 8;
(*ptr).ma = 20000;
```

## 4. Cơ chế hoạt động
- Con trỏ struct hoạt động bằng cách sử dụng một địa bộ nhớ để truy cập các thành viên của struct
Thay vì copy toàn bộ dữ liệu, nó truy cập trực tiếp vùng nhớ qua toán tử mũi tên (->), giúp tiết kiệm dung lượng và tối ưu tốc độ xử lý.

## 5. Ví dụ minh họa

```c
#include <stdio.h>

struct sanpham{
 int ma_sp;
 char ten_sp;
};

int main(){
 struct sanpham a = {322, "may tinh"}; //khai bao va khoi tao structure
 struct sanpham *ptr = &a; // tro vao structure

 printf("ma san pham la: %d\n", ptr->ma_sp);
 printf("ten san pham la: %d\n", ptr->ten_sp);
 return 0;
}
```
## 6. Ứng dụng thực tế
 - Điều khiển GPIO bằng địa chỉ thanh ghi.
 - Xây dựng driver UART, SPI, I2C.
 - Quản lý nhiều thiết bị bằng một driver chung.

