
# Chia file .h và .c


## 1. Mục tiêu
- Hiểu về file .h, .c
- Hiểu cách chia file .h và .c, tại sao


## 2. Header file ( .h)
### Khái niệm
- Header file trong C là tệp khai báo, dùng để chia sẻ thông tin giữa các file .c trong cũng một chương trình. 
- Header file không chứa code chạy.
- Header file chỉ chứa thông tin sau: 
   + Nguyên mẫu hàm.
   + Khai báo kiểu dữ liệu: `struct`, `union`, `enum`, `typedef`.
   + Các hằng số hoặc macro (#define).
   + khai báo biến toàn cục dạng `extern`

### Cấu trúc:
- Header guard
**Lưu ý:** Luôn sử dụng Header Guard để tránh lỗi định nghĩa trùng lặp khi include file nhiều lần

```c

#ifndef HEADER_H
#define HEADER_H


#endif
```
- #include<...> và #include"..."

```c
#include <stdio.h>
#include"user_file.h"
```
-  Cấu trúc chuẩn
```c
#ifndef HEADER_H
#define HEADER_H

// macro
#define A = 100

// typedef
typedef struct{
	int id;
} Item;

// extern
extern int count;

// prototype:
void foo(void);

#endif
```
## 3. File source ( .c)
### Khái niệm
- File .c dùng để định nghĩa.
- Nội dung bao gồm code xử lý chi tiết, thuật toán, logic điều khiển
### Cách dùng
- Dùng lệnh `#include "ten_file.h"` để liên kết với file header tương ứng.
- Viết toàn bộ nội dung (thân hàm) cho các hàm đã khai báo ở file .h
Ví dụ: có 3 file
```c
// math.h
#ifndef MATH
#define MATH
int cong (int a, int b);
#endif
```

```c
//math.c
#include "math.h"

int cong (int a, int b){
	retunr a+b;}
```
```c
//main.c 
#include <stdio.h>
#include "math.h"

int main(void){
	printf("%d", cong( 1, 2));
	return 0;
}
```
## 4. Cách chia file trong dự án
- Một cặp file luôn phải cùng tên, chỉ khác phần mở rộng (ví dụ: math.h và math.c)
Ví dụ :
``math.h > math.c > main.c``

## 5. Lý do cần chia file .h và .c
- Dễ quản lý và đọc hiểu: Thay vì để hết code vào một file main.c duy nhất, nên tách code theo từng module
- Trừu tượng hóa : File .h đóng vai trò như một bản mô tả/mục lục cho người dùng hoặc các file khác biết thư viện của bạn có những hàm gì, cấu trúc ra sao mà không cần quan tâm phần code logic bên trong viết thế nào.
- Làm việc nhóm hiệu quả: Nhiều người có thể cùng làm việc trên một dự án mà ít khi bị xung đột code do mỗi người phụ trách các module/file .c khác nhau.
- Tăng tốc độ biên dịch (Compile): Khi bạn sửa code trong một file .c, trình biên dịch chỉ cần biên dịch lại file đó thay vì phải dịch lại toàn bộ dự án.
- Bảo mật mã nguồn: Khi phát triển thư viện thương mại, bạn có thể gửi file .h (khai báo API) kèm theo file nhị phân đã biên dịch (.lib, .dll, .a) mà không cần để lộ mã nguồn logic trong file .c
