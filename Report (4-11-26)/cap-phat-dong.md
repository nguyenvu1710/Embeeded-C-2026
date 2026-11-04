# Cấp phát động


## 1. Mục tiêu

- Hiểu về cấp phát động trong C/C++ và một số đặc điểm của cấp phát động.
- So sánh cấp phát động và cấp phát tĩnh
- Biết các hàm cấp phát động: malloc, calloc, realloc, free.
- Biết các toán tử new và detete trong C++

## 2. Khái niệm cấp phát động
- Cấp phát động (Dynamic memory allocation) trong C/C++ là hình thức xin cấp phát vùng nhớ.
- Khi cấp phát động thì người lập trình sẽ chủ động xin cấp phát vùng nhớ khi cần và giải phóng vùng nhớ khi cần thu hồi.

## 3. Cấp phát tĩnh vs cấp phát động
|  |Cấp phát tĩnh|Cấp phát động|
|-|-|-|
|Thời điểm cấp phát|Khi biên dịch|Khi chạy chương trình|
|Vùng nhớ|Stack / Data segment|Heap|
|Kích thước|Cố định|Linh hoạt, có thể thay đổi (`realloc`)|
|Giải phóng|Tự động khi hết phạm vi hàm|Phải dùng hàm `free()` thủ công|

## 4. Các hàm
### Hàm malloc()
- `malloc()`: (Memory Allocation) dùng để cấp phát một vùng nhớ có kích thước xác định.
- Lưu ý:
  + Với một mảng có kiểu dữ liệu xác định ta phải ép kiểu để phù hợp với kiểu dữ liệu của mảng.
  + Hàm `malloc` chỉ cấp phát mà không khởi tạo giá trị ban đầu cho các biến.
- Cú pháp: 
 ```c
   void *malloc(size_t so_byte_can_cap_phat);
```
  + Để đảm bảo cấp phát đủ bộ nhớ cho một mảng, ta thường sử dụng:
```c 
   malloc(n*sizeof(data_type));
 ```
  + trong đó:
  + `n`: là số phần tử
  + Toán tử `sizeof(kiểu_dữ_liệu)`: trả về kích thước của kiểu dữ liệu 
  
Ví dụ:
```c
#include <stdio.h>
#include <stdlib.h>

int main(){
    int *ptr;
    ptr = malloc(5 * sizeof(int)); //cấp phát mảng động kiểu int với 5 phần tử
    for (int i = 0; i < 5; i++){
        ptr[i] = i + 1;
    }
    for (int i = 0; i < 5; i++){
        printf("%d ", ptr[i]);
    }
    return 0;
}
```
OUTPUT:
> 1 2 3 4 5

### Hàm calloc()
- `calloc()`: (Contiguous Allocation) dùng để cấp phát bộ nhớ cho một mảng gồm nhiều phần tử và khởi tạo tất cả các byte trong vùng nhớ bằng 0.
-  Lưu ý:
   + Với một mảng có kiểu dữ liệu xác định ta phải ép kiểu để phù hợp với kiểu dữ liệu của mảng.
   + Sau khi cấp phát, các phần tử sẽ được gán giá trị 0.
```c
void* calloc(size_t num, size_t a);
// Cấp phát mảng động có num phần tử có kích thước a byte
```
Ví dụ:
```c
#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p = (int*)calloc(2, sizeof(int));
    for (int i = 0; i < 1; i++){
        p[i] = i + 1;

    }
    for (int i = 0; i < 2; i++){
        printf("%d ", p[i]);
    }
    return 0;
}
```
OUTPUT 
> 1 0

###  Hàm realloc
- `realloc()`: (Re-allocation) Thay đổi kích thước của một vùng nhớ đã được cấp phát trước đó (mở rộng hoặc thu hẹp).
```c
void* realloc(void *ptr, size_t a);
// Thay đổi kích thước vùng nhớ được trỏ bởi con trỏ ptr với kích thước mới là a byte.
```
Ví dụ:
```c
#include <stdio.h>
#include <stdlib.h>
int main(){
	int *p = (int*)malloc(5*sizeof(int));
	int *q = (int*)realloc(p, 10*sizeof(int));
		
    for (int i = 0; i < 5; i++){
        q[i] = i + 1;
    }
    for (int i = 0; i < 10; i++){
        printf("%d ", q[i]);
    }
    return 0;
}
```
OUTPUT 
> 1 2 3 4 5 0 0 0 0 0

### Hàm free
- `free()`: Giải phóng vùng nhớ đã cấp phát động khi không còn sử dụng để trả lại tài nguyên cho hệ điều hành.
- *Chú ý: Phải luôn giải phóng bộ nhớ động khi không dùng đến nữa.*
```c
void free(void *p);
// Giải phóng vùng nhớ trỏ bởi con trỏ p.
```
Ví dụ:
```c
int *a = (int*)malloc(512);
free(a);
```
## 5. Toán tử new và detete trong C++
### new
- Cấp phát động một biến:
```c
char *str = new char(); 
//Cấp phát một chuỗi chưa biết số lượng phần tử
```
- Cấp phát cho một mảng n phần tử:
```c
int *a = new int[n];
```
### delete
- Thu hồi một biến:
```c
- delete a; //thu hồi vùng nhớ của con trỏ a
```
- Thu hồi một mảng:
```c
delete []a; //thu hồi mảng a
```

## 6. Lưu ý quan trọng khi sử dụng
- **Rò rỉ bộ nhớ :** Nếu cấp phát bằng `malloc`/`calloc` nhưng quên gọi `free()` khi không dùng nữa, vùng nhớ đó sẽ bị chiếm dụng đến khi tắt chương trình. 
- **Con trỏ treo:** Sau khi gọi `free(ptr)`, giá trị của `ptr` vẫn trỏ tới ô nhớ cũ. Nên gán `ptr = NULL;` ngay sau khi giải phóng để tránh lỗi truy cập nhầm.
- **Kiểm tra null:** Luôn kiểm tra xem con trỏ có khác `NULL` hay không sau khi cấp phát để đảm bảo hệ điều hành còn đủ bộ nhớ trống.
