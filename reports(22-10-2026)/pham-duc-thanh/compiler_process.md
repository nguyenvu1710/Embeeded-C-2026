# Compiler_process
## 1.Muc tieu
- Nắm rõ 4 giai đoạn: Hiểu chi tiết quá trình từ file mã nguồn .c biến đổi qua Preprocessing, Compilation, Assembly và Linking.
- Hiểu nhiệm vụ các công cụ: Phân biệt vai trò của Preprocessor (cpp), Compiler (cc1), Assembler (as), và Linker (ld).
- Hiểu sơ đồ bộ nhớ tiến trình: Nắm vững cấu trúc bố trí vùng nhớ khi chương trình thực thi (Stack, Heap, .bss, .data, .rodata, .text).
- Kỹ năng thực hành: Biết cách sử dụng cờ biên dịch GCC (-E, -S, -c, -o) để kiểm tra sản phẩm từng giai đoạn và xử lý các lỗi Linking/Build.
## 2.Tong quan
Source Code (.c) 
       │
       ▼  [1. Preprocessing]  --> Mở rộng #include, #define, xóa comment
 Expanded Code (.i)
       │
       ▼  [2. Compilation]    --> Kiểm tra cú pháp, tối ưu, sinh Assembly
 Assembly Code (.s)
       │
       ▼  [3. Assembly]       --> Chuyển lệnh Assembly thành Mã máy
 Object Code (.o/.obj)
       │
       ▼  [4. Linking]        --> Liên kết các .o và thư viện (.a/.so)
 Executable Binary (.exe / a.out)

## 3.Chi tiet
* Giai đoạn 1: Preprocessing (Tiền Xử Lý)
- Công cụ: cpp (C Preprocessor).
- Nhiệm vụ:
    + Thay thế nội dung các tệp header được gọi qua #include <...> hoặc #include "...".
    + Thay thế các định nghĩa Macro và hằng số #define.
    + Xử lý biên dịch có điều kiện (#ifdef, #ifndef, #else, #endif).
    + Loại bỏ toàn bộ ghi chú (comment) trong mã nguồn.
- Lệnh GCC kiểm tra: gcc -E main.c -o main.i

* Giai đoạn 2: Compilation (Biên Dịch)
- Công cụ: cc1 (C Compiler).
- Nhiệm vụ:
    + Phân tích cú pháp (Lexical & Syntax Analysis) và phân tích ngữ nghĩa (Semantic Analysis).
    + Xây dựng Cây cú pháp trừu tượng (AST).
    + Thực hiện các chiến lược tối ưu hóa mã nguồn (Loop unrolling, dead code elimination, constant folding).
    + Sinh ra mã hội họa (Assembly code) dành riêng cho kiến trúc CPU tương ứng (x86_64, ARM, RISC-V).
- Lệnh GCC kiểm tra: gcc -S main.i -o main.s

* Giai đoạn 3: Assembly (Hội Dịch)
- Công cụ: as (Assembler).
- Nhiệm vụ:
    + Chuyển đổi mã hội họa từ tệp .s thành tập lệnh nhị phân mà CPU hiểu được (Machine Code).
    + Đóng gói mã máy này thành tệp Object (.o hoặc .obj) theo các định dạng tiêu chuẩn như ELF (Linux) hoặc PE (Windows).
    + Tệp Object chứa các section bộ nhớ chưa được gán địa chỉ tuyệt đối.
- Lệnh GCC kiểm tra: gcc -c main.s -o main.o

* Giai đoạn 4: Linking (Liên Kết)
- Công cụ: ld (Linker).
- Nhiệm vụ:
    + Kết hợp tất cả các tệp Object (main.o, utils.o) trong dự án lại với nhau.
    + Giải quyết tham chiếu các biểu tượng (symbol resolution): Ghép nối các lời gọi hàm (printf, malloc) với mã thực thi thực sự trong các thư viện C chuẩn (libc.a, libc.so).
    + Định vị bộ nhớ (relocation): Sắp xếp các phân đoạn mã vào địa chỉ bộ nhớ hợp lệ.
    + Xuất ra tệp thực thi duy nhất (a.out, main.exe hoặc .elf).
- Lệnh GCC kết thúc: gcc main.o -o main
