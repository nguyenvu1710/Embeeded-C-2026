# Kiểu dữ liệu Uniom

## 1. Mục tiêu

- Hiểu kiểu dữ liệu union là gì.
- Biết cách khai báo và sử dụng union.
- Biết cách truy cập các phần tử của union.
- Biết khi nào nên sử dụng union.
- Biết ưu/nhược điểm của union.

## 2. Khái niệm
  - Union là một kiểu dữ liệu người dùng tự định nghĩa (User-Defined Data Type).
  - Nó cho phép lưu trữ các thành viên khác nhau tại cùng một vị trí bộ nhớ.
  - Tại bất kỳ thời điểm nào, chỉ có duy nhất một thành viên của Union được sử dụng hoặc có giá trị hợp lệ.
  - Kích thước của Union sẽ bằng kích thước của thành viên lớn nhất trong nó.

## 3. Cú pháp
### Khai báo:
```c
union Ten_Union {
 ten_kieu_du_lieu_1 thanh_vien_1;
 ten_kieu_du_lieu_2 thanh_vien_2;
//...
};
```
* trong đó kiểu dữ liệu có thể là int, float,char, v.v

- Ngoài ra cũng có thể dùng typedef giống struct:
```c
typedef union {
  ten_kieu_du_lieu_1 thanh_vien_1;
  ten_kieu_du_lieu_2 thanh_vien_2;
} Ten_Union;
```

### Truy cập các phần tử của Union:
 Ta cũng sử dụng toán tử dấu chấm (.) hoặc toán tử mũi tên (->) để truy cập các phần tử của Union tương tự như với Struct.

Ví dụ:
```c
#include <stdio.h>

union Data {
    int a;
    char str[50];
}; // khoi tao union

int main() {
    union Data A1; // khai bao bien A1 cua union Data
    A1.a = 5;
    printf("so nguyen: %d\n", A1.a);

    snprintf(A1.str, sizeof(A1.str), "fish");
    printf("Chuoi: %s\n", A1.str);
    return 0;
}
```
### Chú ý: Khi ghi dữ liệu vào một thành viên của union, dữ liệu của các thành viên khác sẽ bị ghi đè. Do đó, cần tự quản lý để luôn biết thành viên nào đang chứa dữ liệu hợp lệ.

## 4. Ưu và nhược điểm khi sử dụng union.
### Ưu điểm: 
- Tiết kiệm bộ nhớ: Đặc biệt quan trọng trong các hệ thống nhúng có RAM và ROM hạn chế.
- Linh hoạt trong truy cập dữ liệu: Cho phép xem cùng một dữ liệu dưới nhiều kiểu khác nhau, hữu ích cho việc parsing dữ liệu nhị phân hoặc giao tiếp phần cứng.
- Đôi khi cải thiện hiệu suất: Trong một số trường hợp, việc truy cập toàn bộ word thay vì từng byte riêng lẻ có thể nhanh hơn.
### Nhược điểm:
- Rủi ro về dữ liệu: Yêu cầu người lập trình phải tự quản lý và biết thành viên nào đang hợp lệ. Nếu ghi vào một thành viên rồi đọc từ một thành viên khác mà không hiểu rõ, sẽ dẫn đến dữ liệu không chính xác hoặc lỗi khó gỡ lỗi (undefined behavior).
- Tính rõ ràng giảm: Mã nguồn có thể khó đọc và khó hiểu hơn nếu Union được sử dụng không cẩn thận.
- Vấn đề Endianness: Khi Union được dùng để chuyển đổi giữa byte array và các kiểu dữ liệu lớn hơn (như int hay short), thứ tự byte của hệ thống có thể gây ra kết quả không mong muốn.

## 5. Khi nào nên sử dụng union.
- Khi có nhiều loại dữ liệu khác nhau nhưng tại một thời điểm chỉ cần sử dụng một trong số chúng.
- Khi cần truy cập dữ liệu theo nhiều cách khác nhau (Type Punning)
