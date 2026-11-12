# Stdarg (Hàm có số lượng đối số biến thiên)
## 1.Muc tieu
- Hiểu bản chất: Hiểu cách ngôn ngữ C cho phép một hàm nhận vào số lượng tham số không cố định (như printf, scanf).
- Cú pháp & quy tắc: Sử dụng kiểu va_list và bộ 3 macro va_start, va_arg, va_end trong thư viện stdarg.h.
- Ứng dụng thực tế: Xây dựng hàm ghi log hệ thống (Custom Logger), hàm xử lý chuỗi hoặc tính toán thống kê linh hoạt.
## 2.Khai niem
- Stdarg (stdarg.h) là thư viện chuẩn của C cung cấp các kiểu dữ liệu và macro cho phép định nghĩa các Variadic Functions (hàm biến thiên đối số) — tức là các hàm nhận ít nhất một tham số cố định đi kèm với danh sách các tham số tùy ý được biểu diễn bằng dấu ba chấm ....

## 3.Cu phap
```c
#include <stdarg.h>

kieu_tra_ve ten_ham(kieu_co_dinh tham_so_cuoi, ...) {
    va_list args;                       // 1. Khai báo con trỏ danh sách đối số
    va_start(args, tham_so_cuoi);       // 2. Khởi tạo args trỏ ngay sau tham_so_cuoi

    // 3. Lấy từng đối số theo kiểu dữ liệu tương ứng
    kieu_du_lieu val = va_arg(args, kieu_du_lieu);

    va_end(args);                       // 4. Dọn dẹp con trỏ danh sách đối số
}
```

## 4.Co che hoat dong
- Khi gọi hàm trong C, các đối số được đẩy vào vùng nhớ Stack (hoặc thanh ghi tùy kiến trúc ABI) theo thứ tự liên tiếp nhau. 
- Biến va_list thực chất hoạt động như một con trỏ byte trỏ vào vùng nhớ Stack chứa các đối số:
    + va_start(args, last_fixed_param): Lấy địa chỉ của tham số cố định cuối cùng (last_fixed_param), cộng thêm kích thước của nó để trỏ đúng vào đối số ẩn đầu tiên trong dấu ....
    + va_arg(args, type): Đọc giá trị tại vị trí hiện tại của args theo kích thước của kiểu type, đồng thời tự động dịch chuyển con trỏ args sang đối số tiếp theo (args += sizeof(type)).
    + va_end(args): Đặt lại con trỏ args về NULL để đảm bảo an toàn bộ nhớ sau khi kết thúc.
- Lưu ý quan trọng: Bản thân hàm variadic không tự biết có bao nhiêu đối số được truyền vào, nên tham số cố định đầu tiên bắt buộc phải đóng vai trò chỉ báo (ví dụ: truyền số lượng tham số, hoặc truyền chuỗi định dạng %d, %s như printf).

## 5.Vi du minh hoa:
```c
#include <stdio.h>
#include <stdarg.h>

// Hàm tính tổng của N số nguyên bất kỳ
int tinh_tong(int so_luong, ...) {
    int tong = 0;
    va_list danh_sach;

    // Khởi tạo con trỏ danh_sach bắt đầu từ sau tham số 'so_luong'
    va_start(danh_sach, so_luong);

    for (int i = 0; i < so_luong; i++) {
        // Lấy từng số nguyên ra và tự động dịch sang phần tử kế tiếp
        tong += va_arg(danh_sach, int);
    }

    va_end(danh_sach);
    return tong;
}

int main(void) {
    printf("Tong 3 so: %d\n", tinh_tong(3, 10, 20, 30));
    printf("Tong 5 so: %d\n", tinh_tong(5, 1, 2, 3, 4, 5));

    return 0;
}
```

Terminal:   Tong 3 so: 60
            Tong 5 so: 15
## 6.Ung dung:
- Xây dựng hệ thống Logging chuyên nghiệp (log_info, log_error): Viết các hàm bọc (wrapper) nhận chuỗi định dạng tùy biến kèm thời gian, mức độ lỗi (Level) để xuất thông tin chẩn đoán phần mềm.
- Hàm đóng gói bản tin hoặc nối chuỗi linh hoạt: Truyền nhiều chuỗi ký tự hoặc nhiều trường dữ liệu khác nhau vào một hàm duy nhất để ghép thành gói tin hoàn chỉnh.