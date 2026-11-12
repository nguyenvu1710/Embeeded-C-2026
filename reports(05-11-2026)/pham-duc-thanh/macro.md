# Macro & Tiền xử lý (Preprocessor)
## 1.Muc tieu
- Hiểu bản chất: Hiểu cơ chế thay thế văn bản (Text Substitution) trước khi trình biên dịch dịch mã C sang mã máy.
- Cú pháp & quy tắc: Khai báo hằng số, hàm macro (Function-like macro), các toán tử #, ##, và quy tắc đóng ngoặc an toàn.
- Ứng dụng thực tế: Viết hàm tính toán nhanh không tốn chi phí gọi hàm, biên dịch có điều kiện cho nhiều cấu hình phần mềm.
## 2.Khai niem
- Macro là một đoạn mã hoặc định danh được định nghĩa thông qua chỉ thị tiền xử lý #define. Trước khi quá trình biên dịch (Compilation) bắt đầu, bộ tiền xử lý (Preprocessor) sẽ quét toàn bộ file mã nguồn và thay thế tên Macro bằng nội dung tương ứng của nó.

## 3.Cu phap
```c
#include <assert.h>
// 1. Object-like Macro (Định nghĩa hằng số)
#define PI              3.14159f
#define BUFFER_SIZE     256

// 2. Function-like Macro (Macro giống hàm - luôn bọc ngoặc từng tham số và toàn biểu thức)
#define MAX(a, b)       (((a) > (b)) ? (a) : (b))
#define SQUARE(x)       ((x) * (x))

// 3. Macro nhiều dòng (sử dụng dấu '\' ở cuối dòng và bọc trong do { ... } while(0))
#define SWAP(a, b, type) do { \
    type temp = (a);          \
    (a) = (b);                \
    (b) = temp;               \
} while(0)

// 4. Toán tử chuỗi hóa (#) và nối chuỗi định danh (##)
#define TO_STRING(x)    #x
#define CONCAT(a, b)    a##b
```
## 4.Co che hoat dong
- Thay thế văn bản thuần túy (Pure Text Replacement): Bộ tiền xử lý không hiểu cú pháp C hay kiểu dữ liệu; nó chỉ tìm chuỗi ký tự khớp với tên Macro và dán nội dung thay thế vào vị trí đó ở bước Preprocessing (tạo ra file .i).
- Không tốn chi phí gọi hàm (No Function Call Overhead): Khác với hàm thông thường phải lưu địa chỉ trả về và cấp phát Stack Frame, Macro chèn trực tiếp mã lệnh vào nơi gọi, giúp tốc độ thực thi nhanh hơn nhưng làm tăng kích thước mã máy (Code size) nếu gọi nhiều lần.
- Bẫy độ ưu tiên toán tử (Operator Precedence Trap): Nếu viết #define SQUARE(x) x * x, khi gọi SQUARE(1 + 2), bộ tiền xử lý sẽ bung thành 1 + 2 * 1 + 2 = 5 (sai). Do đó, nguyên tắc bắt buộc khi viết Function-like Macro là bọc ngoặc đơn quanh từng tham số (x) và quanh toàn bộ biểu thức ((x) * (x)).  

## 5.Vi du minh hoa:
```c
#include <stdio.h>

#define SQUARE(x)           ((x) * (x))
#define PRINT_VAR(var)      printf(#var " = %d\n", var)
#define MAKE_VAR(name, id)  int name##_##id

int main(void) {
    int a = 3;
    // Kiểm tra tính an toàn khi truyền biểu thức vào Macro
    int ket_qua = SQUARE(a + 2); // Bung thành: ((3 + 2) * (3 + 2)) = 25
    PRINT_VAR(ket_qua);

    // Tạo biến động bằng toán tử nối ##: tạo ra biến 'sensor_1'
    MAKE_VAR(sensor, 1) = 100;
    PRINT_VAR(sensor_1);

    return 0;
}
```

Terminal:   ket_qua = 25
            sensor_1 = 100
## 6.Ung dung:
- Biên dịch có điều kiện (Conditional Compilation): Kết hợp #ifdef, #ifndef, #endif để bật/tắt tính năng Debug log hoặc biên dịch mã nguồn cho các phiên bản sản phẩm khác nhau (ví dụ: bản tiêu chuẩn và bản cao cấp) từ cùng một bộ source code.
- Tạo hàm tổng quát (Generic Programming trong C): Vì C không có Template như C++, Macro cho phép viết các phép toán (MIN, MAX, SWAP, ARRAY_SIZE) hoạt động được với mọi kiểu dữ liệu (int, float, double).