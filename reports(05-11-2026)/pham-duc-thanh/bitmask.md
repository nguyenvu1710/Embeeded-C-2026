# Bitmask
## 1.Muc tieu
- Hiểu bản chất: Sử dụng từng bit riêng lẻ trong một biến số nguyên để lưu trữ nhiều trạng thái logic (True/False) thay vì dùng nhiều biến riêng biệt.
- Cú pháp & quy tắc: Nắm vững các toán tử thao tác bit (Bitwise operators) để bật, tắt, đảo và kiểm tra trạng thái bit.
- Ứng dụng thực tế: Tối ưu hóa bộ nhớ RAM và đóng gói dữ liệu phần mềm.

## 2.Khai niem
- Bitmask (Mặt nạ bit) là kỹ thuật sử dụng một chuỗi bit cố định (mặt nạ) kết hợp với các toán tử bitwise (AND, OR, XOR, NOT, dịch trái, dịch phải) để thao tác hoặc truy xuất trạng thái của một hay nhiều bit cụ thể bên trong một biến số nguyên (uint8_t, uint16_t, uint32_t).

## 3.Cu phap
```c
// Định nghĩa mặt nạ tại bit thứ n
#define MASK(n)             (1U << (n))
// 1. Bật bit thứ n lên 1 (Set bit)
bien |= MASK(n);
// 2. Tắt bit thứ n về 0 (Clear bit)
bien &= ~MASK(n);
// 3. Đảo trạng thái bit thứ n (Toggle bit)
bien ^= MASK(n);
// 4. Kiểm tra bit thứ n (Check bit)
if (bien & MASK(n)) { /* Bit đang bằng 1 */ }
```
## 4.Co che hoat dong
- Thay vì dùng một biến bool hoặc uint8_t (chiếm 1 byte = 8 bit) chỉ để lưu 1 trạng thái Đúng/Sai (gây lãng phí 7 bit còn lại), Bitmask tận dụng toàn bộ 8 bit của 1 byte để lưu trữ 8 cờ trạng thái (flags) độc lập.
- Khi thực hiện phép toán bitwise giữa biến dữ liệu và mặt nạ (mask):
    + Phép OR (|): Những vị trí mặt nạ có bit 1 sẽ ép bit tương ứng của biến lên 1, các vị trí bit 0 giữ nguyên giá trị cũ.
    + Phép AND với đảo bit (& ~): Những vị trí mặt nạ có bit 1 sau khi đảo (~) sẽ thành 0, ép bit tương ứng của biến về 0.
    + Phép XOR (^): Đảo trạng thái bit tại vị trí mặt nạ có giá trị 1.

## 5.Vi du minh hoa:
```c
#include <stdio.h>
#include <stdint.h>

// Định nghĩa các quyền của người dùng trong hệ thống phần mềm (1 byte = 8 quyền)
#define PERM_READ       (1U << 0) // 0000 0001 (1)
#define PERM_WRITE      (1U << 1) // 0000 0010 (2)
#define PERM_EXECUTE    (1U << 2) // 0000 0100 (4)
#define PERM_DELETE     (1U << 3) // 0000 1000 (8)

int main(void) {
    uint8_t user_permission = 0; // Ban đầu chưa có quyền gì (0000 0000)

    // Cấp quyền Đọc và Ghi cùng lúc
    user_permission |= (PERM_READ | PERM_WRITE);

    // Kiểm tra quyền Ghi
    if (user_permission & PERM_WRITE) {
        printf("User co quyen GHI du lieu.\n");
    }

    // Thu hồi quyền Ghi
    user_permission &= ~PERM_WRITE;

    if (!(user_permission & PERM_WRITE)) {
        printf("Da thu hoi quyen GHI!\n");
    }

    return 0;
}
```

Terminal:   User co quyen GHI du lieu.
            Da thu hoi quyen GHI
## 6.Ung dung:
- Quản lý phân quyền và trạng thái phần mềm: Lưu trữ quyền truy cập file (Read, Write, Execute), trạng thái kết nối mạng, hoặc danh sách các tính năng đang bật của người dùng chỉ trong 1 biến duy nhất.
- Đóng gói/Giải nén giao thức truyền thông (Protocol Parsing): Tách các trường dữ liệu (Header, Payload, Checksum) hoặc ghép hai biến 8-bit thành một biến 16-bit khi truyền nhận gói tin.
- Tối ưu hóa RAM trên hệ thống nhúng: Giảm tới 8 lần dung lượng RAM khi quản lý hàng trăm cờ sự kiện (Event Flags) trong hệ điều hành thời gian thực (RTOS).