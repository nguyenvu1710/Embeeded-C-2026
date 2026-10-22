# Compiler process trong C

## 1. Mục tiêu

- Hiểu Compiler process là gì.
- Hiểu các giai đoạn của compiler process

## 2. Khái niệm
  - Vì C là một ngôn ngữ lập trình cấp trung, nó cần một trình biên dịch để chuyển đổi mã nguồn thành mã thực thi, nhờ đó chương trình mới có thể chạy trên máy tính.
  - Quá trình biên dịch một chương trình C (Compiler Process) là hành trình chuyển đổi từ mã nguồn viết bằng ngôn ngữ C sang mã máy để máy tính có thể hiểu và thực thi được.
  - Quá trình này gồm 4 giai đoạn chính diễn ra như sau:
    Tiền xử lý > Biên dịch > Lắp ráp > Liên kết

## 3. Các giai đoạn biên dịch
### Giai đoạn tiền xử lý (Preprocessing)
 - Nhiệm vụ: Xử lý các câu lệnh bắt đầu bằng dấu # (gọi là tiền chỉ thị - preprocessor directives).
 - Các hoạt động chính:
 + Thay thế các tệp tiêu đề (Header files) như #include <stdio.h> bằng nội dung thực tế của tệp đó.
 + Thay thế các macro #define bằng giá trị cụ thể.
 + Xử lý biên dịch có điều kiện (#ifdef, #ifndef, #endif).
 + Xóa các dòng chú thích (// hoặc /* */).
- => Tạo ra tệp mã nguồn mở rộng (thường có phần mở rộng là .i).

### Giai đoạn biên dịch (Compilation)
 - Nhiệm vụ: Kiểm tra cú pháp ngôn ngữ C và chuyển đổi mã nguồn đã tiền xử lý thành mã Assembly (hợp ngữ).
 - Các hoạt động chính:
 + Phân tích cú pháp xem có lỗi viết sai ngữ pháp C hay không.
 + Tối ưu hóa mã nguồn.
 + chuyển đổi mã C thành tập lệnh dành riêng cho kiến trúc CPU của máy tính (như x86, ARM).
=> Tạo ra tệp mã Assembly (thường có phần mở rộng là .s hoặc .asm).

### Giai đoạn lắp ráp (Assembly)
 - Nhiệm vụ: Dịch mã Assembly thành mã máy (mã nhị phân 0 và 1).
 - Các hoạt động chính:
 + Chuyển đổi các lệnh hợp ngữ (như MOV, ADD, PUSH) thành các dãy mã nhị phân mà máy có thể hiểu trực tiếp. Tuy nhiên, tệp này vẫn chưa thể chạy độc lập được vì chưa có địa chỉ bộ nhớ chính thức cho các hàm.
- => Tạo ra tệp đối tượng (Object file, thường có phần mở rộng là .o hoặc .obj).

### Giai đoạn liên kết (Linking)
 - Nhiệm vụ: Gom tất cả các tệp đối tượng (.o/.obj) và các thư viện hệ thống thành một file thực thi duy nhất.
 - Các hoạt động chính:
 + Liên kết mã của bạn với mã của các hàm thư viện chuẩn.
 + Giải quyết các địa chỉ hàm và biến toàn cục để chúng khớp nối với nhau.
- => Tạo ra Tệp thực thi cuối cùng (như tệp .exe hoặc .out).

