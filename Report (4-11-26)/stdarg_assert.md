# Stdarg, assert


## 1. Mục tiêu

- Hiểu thư viện Stdarg.h là gì.
- Biết thành phần chính trong Stdarg.h, ví dụ
- Lưu ý khi sử dụng stdarg.h.
- Hiểu thư viện assert.h là gì.
- So sánh Stdarg.h với assert.h.


## 2. Khái niệm stdarg.h
- stdarg.h là một thư viện chuẩn trong ngôn ngữ lập trình C, cung cấp các kiểu dữ liệu và macro cho phép một hàm có thể nhận số lượng đối số (arguments) không cố định (hay còn gọi là hàm biến thiên - variadic functions, ví dụ điển hình là hàm printf hay scanf).

## 3. Thành phần chính trong stdarg.h
|**`va_list`** |Kiểu dữ liệu dùng để khai báo một biến đại diện cho danh sách các đối số chưa biết. | 
|-|-|
|**`va_start()`**| Kiểu dữ liệu dùng để khai báo một biến đại diện cho danh sách các đối số chưa biết. |
|**`va_arg()`**| Macro dùng để lấy giá trị của đối số hiện tại ra khỏi danh sách và dịch chuyển con trỏ sang đối số tiếp theo (cần truyền kèm kiểu dữ liệu của đối số đó).|
|**`va_end()`**| Macro dọn dẹp và kết thúc việc xử lý danh sách đối số biến đổi (bắt buộc phải gọi trước khi hàm kết thúc).|
|**`va_copy()`**|Dùng để sao chép một danh sách|

## 4. Ví dụ
```c
#include <stdio.h>
#include <stdarg.h>
// Hàm tính tổng, tham số đầu tiên (k) chỉ số lượng các số theo sau
int sum(int k, ...) {
    int total = 0;
    va_list args;
    // Khởi tạo danh sách đối số, bắt đầu từ sau tham số 'k'
    va_start(args, k);
    for (int i = 0; i < k; i++) {
        // Lấy giá trị kiểu int từ danh sách
        total += va_arg(args, int);
    }
    // Kết thúc làm việc với va_list
    va_end(args);
    return total;
}
int main() {
    printf("Sum1: %d\n", sum(3, 10, 20, 30));
    printf("Sum2: %d\n", sum(2, 5, 5));
    return 0;
}

```
OUTPUT:
> Sum1: 60
> Sum2: 10

## 5. Lưu ý khi sử dụng stdarg.h
- Cần biết trước số lượng tham số hoặc có cơ chế xác định điểm kết thúc.
- Phải lấy tham số đúng kiểu dữ liệu.
- Không thể tự động xác định kiểu dữ liệu của từng tham số.
- Phải gọi `va_end()` sau khi hoàn thành.
- Không được gọi `va_arg()` vượt quá số lượng tham số thực tế.

## 6. Khái niệm assert.h
- assert.h là thư viện cung cấp macro `assert()` dùng để kiểm tra một điều kiện trong chương trình.
  + Nếu điều kiện đúng: chương trình tiếp tục chạy.
  + Nếu điều kiện sai: chương trình in thông báo lỗi và gọi abort() để kết thúc bất thường.

## 7.  Cú pháp của assert
```c
#include <assert.h>
assert(condition);
```
## 8.  So sánh stdarg.h và assert.h
|  | `stdarg.h` |`assert.h`|
|-|-|-|-|
|Mục đích|Xử lý tham số biến đổi|Kiểm tra điều kiện|
|Thành phần chính|`va_start`, `va_arg`, `va_end`, `va_list`|`assert()`|
|Loại|Các macro và kiểu dữ liệu|Macro|
|Tác động khi release|Luôn hoạt động trong mọi bản build.|Có thể vô hiệu hóa hoàn toàn trên bản Release bằng `#define NDEBUG`.|
|Ảnh hưởng đến luồng chạy|Không làm dừng chương trình, chỉ giúp đọc giá trị tham số.|Có thể làm dừng/abort chương trình nếu điều kiện sai.|
|Ứng dụng|Thường dùng khi định nghĩa hàm (function author).|Thường dùng trong thân hàm để kiểm tra dữ liệu đầu vào/trạng thái hợp lệ.|




