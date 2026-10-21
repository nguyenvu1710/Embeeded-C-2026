1. Pointer là gì?
Pointer (con trỏ) là một biến dùng để lưu địa chỉ của một đối tượng trong bộ nhớ hoặc địa chỉ của một hàm.
nhớ hai toán tử quan trọng:
- &x:	Lấy địa chỉ của x.
- *p:	Truy cập đối tượng mà p trỏ tới.
Lưu ý: * trong khai báo int *p dùng để khai báo con trỏ; trong biểu thức *p, nó dùng để truy cập đối tượng được trỏ tới.

2. Pointer có tác dụng gì trong Embedded C?
Trong lập trình nhúng, pointer quan trọng vì chương trình phải làm việc với bộ nhớ, dữ liệu cảm biến và các ngoại vi của vi điều khiển. Có các ứng dụng như:
- Truy cập thanh ghi phần cứng.
- Truyền dữ liệu giữa các hàm.
- Xử lý buffer.
- Callback.
- Quản lý dữ liệu.
Điều cần hiểu: pointer không phải tính năng riêng của Embedded C. Nhưng trong nhúng, nó đặc biệt hữu ích vì cho phép thao tác trực tiếp với các vùng nhớ và truyền dữ liệu hiệu quả.

3. void, NULL và Function Pointer
3.1. void: không có giá trị trả về
void led_on(void)
{
    // Bật LED
}
- void đầu tiên: hàm không trả về giá trị.
- void trong ngoặc: hàm không nhận tham số.
3.2. void*: con trỏ chưa xác định kiểu dữ liệu
void* có thể lưu địa chỉ của đối tượng thuộc nhiều kiểu dữ liệu khác nhau, nhưng phải chuyển về kiểu phù hợp trước khi đọc hoặc sửa dữ liệu.
3.3. NULL: con trỏ rỗng
NULL biểu thị rằng pointer không trỏ đến đối tượng hoặc hàm hợp lệ.
Ứng dụng nhúng: biểu thị buffer chưa được cấp, dữ liệu chưa sẵn sàng hoặc thao tác trả về pointer thất bại.
3.4. Function Pointer: con trỏ hàm
Pointer thông thường trỏ đến dữ liệu; function pointer trỏ đến một hàm và cho phép gọi hàm thông qua pointer.
Ứng dụng nhúng: callback UART/CAN, xử lý sự kiện timer và state machine. Ví dụ, driver nhận dữ liệu xong sẽ gọi hàm callback đã đăng ký.


4. Pointer to Pointer và Constant Pointer
4.1. Pointer to Pointer: con trỏ cấp hai
Là con trỏ lưu địa chỉ của một con trỏ khác.
4.2. Constant Pointer:con trỏ có const
   Có hai trường hợp rất dễ nhầm:

- Trường hợp A: const int *p
  Không sửa được dữ liệu thông qua p, nhưng có thể đổi địa chỉ mà p trỏ tới.
- Trường hợp B: int * const p
  Không đổi được địa chỉ của p, nhưng có thể sửa dữ liệu mà nó trỏ tới.
