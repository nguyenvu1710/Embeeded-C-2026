# Struct_pointer
## 1.Muc tieu
- Nắm vững cú pháp & kỹ năng: Khai báo, khởi tạo, truy xuất thành phần con trỏ struct bằng toán tử mũi tên (->)
- Hiểu được ứng dụng của Struct trong lập trình nhúng.

## 2.Khai niem
-Trong thực tế phát triển phần mềm, việc truyền một struct lớn vào hàm theo cơ chế truyền giá trị (pass-by-value) sẽ làm giảm hiệu năng do phải sao chép toàn bộ vùng nhớ. Sử dụng Con trỏ Struct giúp giải quyết triệt để vấn đề này.

## 3.Cu phap
Khai báo: Dùng dấu sao (*) sau tên kiểu struct.
Toán tử mũi tên (->): Dùng để truy xuất thành phần của struct thông qua con trỏ.

## 4.Co che hoat dong
Khi khai báo một struct, hệ điều hành hoặc vi điều khiển sẽ cấp phát một khối bộ nhớ liên tục để chứa tất cả các thành phần bên trong.
Khi gán một con trỏ trỏ tới struct:
- Con trỏ struct thực chất chỉ lưu giữ địa chỉ của ô nhớ đầu tiên (thành viên đầu tiên) trong khối bộ nhớ đó.
- Khi viết s->y = 205;, vi xử lý không tự nhiên biết y ở đâu. Bản chất của toán tử mũi tên -> là sự kết hợp của hai hành động: Lấy giá trị của con trỏ (Dereference) và Cộng độ lệch vị trí (Offset).
Trình biên dịch (Compiler) sẽ tự động tính toán khoảng cách (Offset) từ đầu struct đến thành viên bạn muốn truy cập dựa trên kích thước của các thành viên đứng trước nó.

## 5.Vi du minh hoa:

#include <stdio.h>

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} SensorData;

// Hàm cập nhật dữ liệu cảm gia tốc dùng con trỏ struct
void readSensor(SensorData *s) {
    // Dùng toán tử -> để thay đổi trực tiếp giá trị của biến gốc
    s->x = 100;
    s->y = 205;
    s->z = 1024;
}

int main(void) {
    SensorData mySensor;
    
    readSensor(&mySensor); // Truyền địa chỉ của struct vào hàm
    
    printf("X: %d, Y: %d, Z: %d\n", mySensor.x, mySensor.y, mySensor.z);
    return 0;
}

Terminal: X: 100, Y: 205, Z: 1024

## 6.Ung dung:
- Truyền tham số hiệu quả (Pass by Reference): Truyền địa chỉ của struct vào hàm thay vì copy toàn bộ struct giúp tiết kiệm bộ nhớ RAM và thời gian xử lý.
- Quản lý gói dữ liệu (Communication Packets): Trỏ trực tiếp con trỏ struct lên vùng nhớ đệm (buffer) của UART/SPI/CAN để đọc/ghi các gói tin mạng hoặc cảm biến nhanh chóng.

### Nguồn tham khảo
- viblo.asia
- W3schools - C struct and Pointer
- Slide bài giảng C_language - Giảng viên Phạm Doãn Tĩnh