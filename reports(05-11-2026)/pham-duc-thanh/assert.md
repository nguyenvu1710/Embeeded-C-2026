# Assert (Kiểm tra giả định)
## 1.Muc tieu
- Hiểu bản chất: Phát hiện sớm các lỗi logic hoặc tham số bất hợp lệ của lập trình viên ngay trong giai đoạn phát triển (Debug).
- Cú pháp & quy tắc: Sử dụng assert() trong thư viện assert.h và cách vô hiệu hóa khi xuất bản phần mềm (Release).
- Ứng dụng thực tế: Bảo vệ hàm khỏi con trỏ NULL, chỉ số vượt quá giới hạn mảng (Out-of-bounds).
## 2.Khai niem
- Assert là một macro tiêu chuẩn trong thư viện assert.h, dùng để kiểm tra một giả định (điều kiện logic) tại thời điểm chạy chương trình (runtime). Nếu giả định đúng, chương trình chạy tiếp bình thường; nếu giả định sai, chương trình lập tức dừng lại và báo vị trí lỗi.

## 3.Cu phap
```c
#include <assert.h>
// Để tắt toàn bộ assert khi biên dịch bản Release, định nghĩa NDEBUG trước #include <assert.h>
// #define NDEBUG 

assert(bieu_thuc_dieu_kien);
```
## 4.Co che hoat dong
- Khi assert(expression) được gọi:
    + Nếu expression khác 0 (True): Không có gì xảy ra, chương trình thực thi dòng lệnh tiếp theo.
    + Nếu expression bằng 0 (False): assert sẽ in thông báo lỗi ra luồng lỗi chuẩn (stderr) bao gồm: biểu thức bị sai, tên file nguồn (__FILE__), số dòng (__LINE__), tên hàm (__func__), sau đó gọi hàm abort() để dừng chương trình ngay lập tức.
- Khi định nghĩa macro #define NDEBUG (No Debug) trước khi khai báo #include <assert.h>, bộ tiền xử lý sẽ xóa bỏ hoàn toàn các lệnh assert() khỏi mã nguồn, giúp bản phần mềm thương mại (Release) không bị tốn tài nguyên kiểm tra.

## 5.Vi du minh hoa:
```c
#include <stdio.h>
#include <assert.h>

double tinh_trung_binh(int *mang, int so_luong) {
    // Giả định bắt buộc: con trỏ mảng không được NULL và số lượng phải dương
    assert(mang != NULL);
    assert(so_luong > 0);

    int tong = 0;
    for (int i = 0; i < so_luong; i++) {
        tong += mang[i];
    }
    return (double)tong / so_luong;
}

int main(void) {
    int diem_so[] = {8, 9, 10};
    printf("Trung binh: %.2f\n", tinh_trung_binh(diem_so, 3));

    // Gọi hàm sai logic (truyền con trỏ NULL) -> Assert sẽ bắt lỗi ngay lập tức
    tinh_trung_binh(NULL, 3);

    return 0;
}
```

Terminal:   Trung binh: 9.00
            Assertion failed: mang != NULL, file main.c, line 6
## 6.Ung dung:
- Phát hiện lỗi trong quá trình phát triển (Unit Test & Debugging): Giúp lập trình viên biết chính xác dòng code nào gây ra lỗi ngay tại thời điểm phát sinh, thay vì để dữ liệu rác lan truyền sang các hàm khác gây treo hệ thống khó truy vết.