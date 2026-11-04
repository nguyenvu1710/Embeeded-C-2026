# Assert

## 1. Mục tiêu

- Hiểu assert là gì. 
- Biết cú pháp của assert.
- Bản chất của assert, tại sao lại sử dụng assert.
- Ví dụ.
- Lưu ý khi dùng assert.
- Ứng dụng của assert.

## 2. Khái niệm
- Assert là một macro được định nghĩa trong thư viện chuẩn <assert.h>, dùng để kiểm tra một giả định tại thời điểm chạy.

## 3. Cú pháp
```c
assert(expression);
```

## 4. Bản chất
- Cách hoạt động:  assert(expression); sẽ kiểm tra giá trị của biểu thức expression.
  + Nếu biểu thức đúng (khác 0), chương trình chạy tiếp bình thường.
  + Nếu biểu thức sai (bằng 0), assert sẽ in thông báo lỗi ra dòng lỗi chuẩn (stderr) và gọi hàm abort() để dừng chương trình (hoặc kích hoạt ngắt/reset trong hệ thống nhúng)
- Bị vô hiệu hóa khi release: Khi định nghĩa macro NDEBUG trước khi include <assert.h>, toàn bộ các câu lệnh assert(...) sẽ bị biến thành ((void)0) (không thực hiện gì cả và không tốn dung lượng hay thời gian xử lý trong mã nguồn chạy thật)

## 5. Ứng dụng
- Bắt lỗi logic trong giai đoạn debug: Giúp lập trình viên phát hiện sớm các giá trị con trỏ NULL không mong muốn, lỗi tràn dữ liệu, hoặc sai trạng thái phần cứng/phần mềm ngay khi đang viết và chạy thử trên môi trường giả lập/bo mạch thật.
- Tựu trung tài liệu: Viết `assert(ptr != NULL)`; thay cho một dòng chú thích giúp người đọc code biết chắc chắn rằng tại thời điểm đó, con trỏ ptr không bao giờ được phép bằng NULL.

## 6. Ví dụ
```c
#include <stdio.h>
#include <assert.h>

int main()
{
    unsigned int a = 9600;

    // Kiem tra a
    assert(a== 9600 || a == 115200);

    printf("OK!\n");

    return 0;
}

```
OUTPUT:
```c
ok!
```

## 7. Lưu ý khi dùng assert
-  không đưa các hàm có "tác dụng phụ" (side effects) vào bên trong assert: Ví dụ sai: 
> assert(read_sensor_data() == 0);
- Không nên phụ thuộc vào assert để đảm bảo an toàn cho hệ thống nhúng khi chạy thực tế.
  + Khi định nghĩa macro NDEBUG trước khi include <assert.h>, các kiểm tra assert sẽ bị vô hiệu hóa.
  + Khi assertion thất bại, chương trình thường bị dừng, điều này có thể khiến hệ thống nhúng không tiếp tục hoạt động.
  + Một số hệ thống nhúng không có môi trường xuất thông báo lỗi như máy tính thông thường.
