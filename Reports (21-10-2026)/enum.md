# Kiểu dữ liệu Enum

## 1. Mục tiêu

- Hiểu kiểu dữ liệu Enum là gì.
- Biết cách khai báo và sử dụng enum
- Biết cách truy cập các phần tử của enum.
- Biết khi nào nên sử dụng enum.
- Biết ưu/nhược điểm của enum.

## 2. Khái niệm
Enum (viết tắt của Enumeration) là một kiểu dữ liệu do người dùng định nghĩa cho phép gán các tên có ý nghĩa (gọi là enumerators) cho một tập hợp các giá trị số nguyên. Về cơ bản, nó tạo ra một danh sách các hằng số nguyên được đặt tên.

## 3. Cú pháp
### Khai báo:
```c
enum Ten_Enum {
    ten_thanh_vien_1,
    ten_thanh_vien_2,
    //...
};
```

Ví dụ:
```c
enum LED {
    OFF = 0,
    ON = 1,
    BLINK = 2
};
```

## 4. Tại sao cần có enum.
Tăng cường tính dễ đọc của code.
Giảm lỗi: Khi sử dụng Enum, trình biên dịch có thể kiểm tra kiểu dữ liệu. Nếu cố gắng gán một giá trị không hợp lệ cho một biến Enum, trình biên dịch có thể cảnh báo hoặc báo lỗi, giúp phát hiện lỗi sớm. Điều này tốt hơn nhiều so với việc sử dụng #define cho các hằng số, nơi mà trình biên dịch không thể kiểm tra kiểu.
Dễ bảo trì và sửa đổi code.
Tự động gán giá trị.
Dễ debug

## 5. Phân biệt enum và macro(#define)
Giống nhau: đều có thể dùng để định nghĩa các hằng số.
Khác nhau:
### Enum:
- Kiểu dữ liệu: Là một kiểu dữ liệu (integer type). Trình biên dịch hiểu và kiểm tra kiểu.
- Phạm vi: Có phạm vi giống các biến thông thường (hàm, struct).
- Debug: Dễ dàng debug vì các tên Enum có thể hiển thị trong debugger.
- Gán giá trị: Có thể tự động gán giá trị tăng dần hoặc gán giá trị cụ thể.
- Dễ xảy ra lỗi: Ít lỗi hơn nhờ kiểm tra kiểu và phạm vi.

### #define
- Kiểu dữ liệu: không là một kiểu dữ liệu mà chỉ là một text substitution. Không có kiểm tra kiểu.
- Phạm vi: Không có phạm vi. Thay thế ở bất kỳ đâu nó xuất hiện sau khi định nghĩa.
- Debug: Debugger chỉ nhìn thấy giá trị số đã được thay thế.
- Gán giá trị: Phải gán giá trị cụ thể cho từng macro.
- Dễ xảy ra lỗi: Dễ xảy ra lỗi.