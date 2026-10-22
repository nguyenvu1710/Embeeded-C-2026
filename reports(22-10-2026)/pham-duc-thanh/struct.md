# Struct
## 1.Muc tieu
- Hiểu được bản chất: Hiểu cấu trúc bộ nhớ của struct, cơ chế căn chỉnh dữ liệu (Data Alignment) và hiện tượng chèn byte đệm (Memory Padding).
- Nắm vững cú pháp & kỹ năng: Khai báo, khởi tạo, truy xuất thành phần struct bằng toán tử chấm (.)
- Hiểu được ứng dụng của Struct trong lập trình nhúng.

## 2.Khai niem
- struct (Structure) là kiểu dữ liệu do người dùng tự định nghĩa (user-defined data type), cho phép gom nhóm nhiều biến thuộc các kiểu dữ liệu khác nhau vào chung một thực thể quản lý duy nhất. Các biến bên trong struct được gọi là các thành phần (members hoặc fields).
## 3.Cu phap
- Để khai báo cấu trúc ta dùng cú pháp:
        struct struct_name{
            type1 field1;
            type2 field2;
            ...
        } [bien_co_kieu_struct_name];
- Để truy cập đến các thuộc tính của struct ta sử dụng toán tử “.”
- Ta có thể khởi tạo giá trị cho một biến struct giống như đối với mảng , đặt các giá trị trong cặp dấu { } phân cách giá trị bằng dấu “,”
## 4.Co che hoat dong
Phân bổ liên tục: Các thành phần trong struct được lưu trữ theo thứ tự khai báo trong một vùng nhớ liên tục.

Căn chỉnh dữ liệu (Data Alignment): Trình biên dịch căn chỉnh địa chỉ của từng thành phần dựa trên kích thước kiểu dữ liệu của nó (ví dụ: biến 4-byte thường bắt đầu ở địa chỉ chia hết cho 4).

Byte đệm (Memory Padding): Để đảm bảo quá trình truy xuất bộ nhớ của CPU đạt hiệu năng tối ưu, trình biên dịch tự động chèn các "byte đệm" trống vào giữa các thành phần.
 
Ví dụ minh họa Memory Padding:
    struct Example {
        char a;      // 1 byte
        // 3 bytes padding (được tự động chèn vào)
        int b;       // 4 bytes
        short c;     // 2 bytes
        // 2 bytes padding ở cuối để kích thước tổng là bội số của 4
    }; // Kích thước thực tế = 12 bytes (thay vì 1 + 4 + 2 = 7 bytes)

## 5.Vi du minh hoa:

#include <stdio.h>
#include <string.h>

// Định nghĩa struct kết hợp typedef để rút ngắn tên kiểu
typedef struct {
    int id;
    char name[50];
    double salary;
} Employee;

int main(void) {
    // Khởi tạo biến struct
    Employee emp1 = {101, "Nguyen Van A", 1500.50};

    // Truy xuất bằng toán tử chấm (.)
    printf("ID: %d, Name: %s, Salary: %.2f\n", emp1.id, emp1.name, emp1.salary);

    return 0;
}

Terminal: ID: 101, Name: Nguyen Van A, Salary: 1500,50

## 6.Ung dung:
- Đóng gói dữ liệu cảm biến (Sensor Data): Gộp các thông số đo được từ một thiết bị (như nhiệt độ, độ ẩm, áp suất, thời gian) vào một cấu trúc duy nhất để dễ dàng truyền qua các giao thức truyền thông (I2C, SPI, UART) hoặc lưu vào bộ nhớ
- Định dạng gói tin truyền thông (Packet Framing): Tạo cấu trúc khớp với các giao thức mạng hoặc gói tin Serial (gồm byte mở đầu, mã lệnh, dữ liệu độ dài biến thiên, mã kiểm tra CRC) để đóng gói và giải gói dữ liệu dễ dàng.

### Nguồn tham khảo
- viblo.asia
- laptrinhdientu.com
- Slide bài giảng C_language - Giảng viên Phạm Doãn Tĩnh