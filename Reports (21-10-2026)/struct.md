# Kiểu dữ liệu Struct

## 1. Mục tiêu

- Hiểu kiểu dữ liệu struct là gì.
- Biết cách khai báo và sử dụng struct.
- Biết khi nào nên sử dụng struct.

## 2. Khái niệm
  - Struct (structure - cấu trúc) là một kiểu dữ liệu người dùng tự định nghĩa (User-Defined Data Type)
  - Nó cho phép gộp nhiều biến có kiểu dữ liệu khác nhau vào chung một khối duy nhất để mô tả một đối tượng.
  - Kích thước của struct có thể lớn hơn hoặc bằng tổng kích thước các thành viên.
  - Trong hệ thống nhúng, struct giúp sắp xếp và quản lý dữ liệu hiệu quả hơn đặc biệt là trong những hệ thống phức tạp.

## 3. Cú pháp
### Khai báo:
```c
struct Ten_Struct{
 ten_kieu_du_lieu_1 ten_bien_1;
 ten_kieu_du_lieu_2 ten_bien_2;
//...
};
```
* Trong đó kiểu dữ liệu có thể là int, float,char hoặc có thể là những struct khác.

Ví dụ:
```c
#include <stdio.h>

struct Data {
    int ma_sp;
    float trong_luong;
}; // khoi tao struct

void displayData(struct Data A) 
{
    printf("Ma san pham: %d\n", A.ma_sp);
    printf("Trong luong: %.1fkg\n", A.trong_luong);
}//khoi tao ham

int main() {
    struct Data A1 = {525, 24.4};//goi ham
    displayData(A1);
    return 0;
}
```
### Truy cập dữ liệu:
Dùng toán tử chấm . khi thao tác trực tiếp trên biến struct 
     ví dụ: (structa.age = 20).

## 4. Lợi ích
- Tổ chức dữ liệu: struct cho phép nhóm các dữ liệu có liên quan lại với nhau, giúp mã nguồn trở nên ngăn nắp và dễ hiểu hơn.
- Cải thiện khả năng đọc: Việc sử dụng struct giúp mã nguồn dễ đọc hơn vì các thông tin liên quan được lưu trữ trong một đơn vị logic duy nhất, thay vì nằm rải rác ở các biến riêng lẻ.
- Xử lý dữ liệu hiệu quả: Struct cho phép truyền nhiều biến có liên quan dưới dạng một đơn vị duy nhất vào các hàm hoặc giữa các phần khác nhau của chương trình.
- Hiệu quả về bộ nhớ: Trong các hệ thống nhúng, struct có thể được sử dụng để quản lý bộ nhớ hiệu quả hơn bằng cách tổ chức các kiểu dữ liệu khác nhau lại với nhau, giúp việc truy cập và thao tác với chúng trở nên thuận tiện hơn.

## 5. Khi nào nên sử dụng struct
- Sử dụng struct cho các dữ liệu có liên quan.
- Tránh các cấu trúc quá lớn: Mặc dù một struct có thể chứa nhiều thành phần, nhưng nên tránh tạo ra các struct quá lớn trong những môi trường bị hạn chế về bộ nhớ. Các struct lớn có thể gây lãng phí bộ nhớ và làm giảm hiệu năng.
- Sử dụng typedef để đơn giản hóa cú pháp khi làm việc với các struct, đặc biệt là trong các hệ thống nhúng – nơi có thể cần khởi tạo nhiều struct khác nhau. Điều này cho phép khai báo một struct mà không cần phải viết lại từ khóa struct trước tên của nó.
      ví dụ: 
```c      
typedef struct {
    int ma_sp;
    float trong_luong;
} Data;
```
- Khởi tạo struct đúng cách: Khi khai báo và khởi tạo các cấu trúc, cần đảm bảo rằng tất cả các thành phần đều được khởi tạo. Giúp ngăn các vấn đề liên quan đến biến chưa được khởi tạo và các hành vi không xác định.


