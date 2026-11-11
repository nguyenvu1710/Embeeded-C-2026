# Báo cáo: Cấp phát bộ nhớ động trong C (`malloc` và `free`)

## 1. Mục tiêu

Sau khi tìm hiểu nội dung này, người học cần:

- Hiểu cấp phát bộ nhớ động là gì và vì sao cần sử dụng.
- Phân biệt vùng nhớ Heap với Stack ở mức cơ bản.
- Biết cách sử dụng `malloc()` để xin cấp phát bộ nhớ.
- Biết kiểm tra kết quả cấp phát và giải phóng bộ nhớ bằng `free()`.
- Nhận biết các lỗi thường gặp như truy cập con trỏ `NULL`, rò rỉ bộ nhớ và con trỏ lơ lửng.

## 2. Khái niệm: Cấp phát bộ nhớ động là gì?

**Cấp phát bộ nhớ động (Dynamic Memory Allocation)** là quá trình xin cấp phát bộ nhớ RAM trong khi chương trình đang chạy (*runtime*), thay vì xác định toàn bộ dung lượng cần dùng ngay từ khi biên dịch.

Trong ngôn ngữ C, hàm `malloc()` thuộc thư viện `<stdlib.h>` được sử dụng để xin một vùng nhớ từ **Heap**.

Có thể hình dung:

- **Stack:** thường lưu các biến cục bộ và dữ liệu phục vụ quá trình gọi hàm. Vùng nhớ này được quản lý tự động theo vòng đời của hàm.
- **Heap:** vùng nhớ dùng cho cấp phát động. Chương trình chủ động xin bộ nhớ và phải giải phóng khi không còn cần sử dụng.

### Tại sao cần cấp phát động?

Giả sử chương trình cần lưu dữ liệu của một số lượng phần tử do người dùng nhập vào. Nếu số lượng này chưa biết trước, việc khai báo một mảng có kích thước cố định có thể không linh hoạt.

Cấp phát động cho phép chương trình xin đúng lượng bộ nhớ cần thiết tại thời điểm chạy, ví dụ: người dùng nhập `n = 5` thì chương trình xin vùng nhớ đủ chứa 5 số nguyên.

## 3. Cú pháp và cách sử dụng `malloc()`

Cú pháp:

```c
#include <stdlib.h>

void *malloc(size_t size);
```

Trong đó:

- `size`: số byte cần cấp phát.
- Giá trị trả về: con trỏ `void*` trỏ tới đầu vùng nhớ được cấp phát.
- Nếu không cấp phát được, hàm trả về `NULL`.
- `malloc()` **không tự khởi tạo dữ liệu** trong vùng nhớ. Vì vậy, không được giả định các phần tử ban đầu bằng 0.

Để tính dung lượng cần xin, thường dùng:

```c
number_of_elements * sizeof(data_type)
```

Ví dụ, để cấp phát chỗ cho 5 số nguyên:

```c
malloc(5 * sizeof(int));
```

Trong C, có thể gán trực tiếp kết quả `malloc()` cho con trỏ kiểu phù hợp mà không cần ép kiểu:

```c
int *arr = malloc(5 * sizeof(int));
```

### Giải phóng bộ nhớ bằng `free()`

Khi không còn cần vùng nhớ đã cấp phát, chương trình phải giải phóng nó:

```c
free(arr);
```

`free()` trả vùng nhớ đó về bộ quản lý bộ nhớ để có thể được sử dụng lại. Sau khi giải phóng, không được tiếp tục truy cập vùng nhớ thông qua con trỏ cũ.

Có thể gán con trỏ về `NULL` sau khi giải phóng:

```c
arr = NULL;
```

Việc này giúp tránh vô tình sử dụng lại con trỏ đã trỏ tới vùng nhớ được giải phóng.

## 4. Cơ chế hoạt động của cấp phát động

Quá trình cấp phát động bằng `malloc()` có thể chia thành các bước:

1. **Yêu cầu bộ nhớ:** chương trình gọi `malloc(size)` với số byte cần sử dụng.
2. **Tìm vùng nhớ:** bộ quản lý bộ nhớ tìm một vùng phù hợp trong Heap.
3. **Trả kết quả:** nếu thành công, `malloc()` trả về địa chỉ đầu vùng nhớ; nếu thất bại, hàm trả về `NULL`.
4. **Sử dụng bộ nhớ:** chương trình truy cập vùng nhớ thông qua con trỏ được trả về.
5. **Giải phóng:** khi dùng xong, chương trình gọi `free(pointer)` để trả vùng nhớ về bộ quản lý bộ nhớ.

Sơ đồ khái quát:

```text
        Gọi malloc(size)
                |
                v
      Yêu cầu bộ nhớ từ Heap
                |
         +------+------+
         |             |
      Thành công     Thất bại
         |             |
         v             v
    Nhận địa chỉ     Trả về NULL
         |
         v
    Sử dụng vùng nhớ
         |
         v
      Gọi free()
         |
         v
   Giải phóng vùng nhớ
```

## 5. Ví dụ minh họa

Chương trình dưới đây cấp phát động một mảng gồm 5 số nguyên, gán giá trị và in các phần tử ra màn hình.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 5;

    // Xin vùng nhớ đủ chứa n số nguyên
    int *arr = malloc(n * sizeof(int));

    // Kiểm tra cấp phát có thành công không
    if (arr == NULL) {
        printf("Cap phat bo nho that bai!\n");
        return 1;
    }

    // Gán và hiển thị dữ liệu
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Giải phóng vùng nhớ sau khi sử dụng
    free(arr);
    arr = NULL;

    return 0;
}
```

**Kết quả:**

```text
arr[0] = 10
arr[1] = 20
arr[2] = 30
arr[3] = 40
arr[4] = 50
```

### Giải thích từng bước

- `int n = 5;`: xác định số phần tử cần lưu.
- `malloc(n * sizeof(int))`: xin vùng nhớ có dung lượng đủ cho 5 biến kiểu `int`.
- `int *arr`: lưu địa chỉ đầu vùng nhớ được cấp phát.
- `if (arr == NULL)`: kiểm tra việc cấp phát có thành công hay không trước khi truy cập.
- `arr[i] = ...`: ghi dữ liệu vào từng phần tử.
- `free(arr)`: giải phóng vùng nhớ sau khi sử dụng.
- `arr = NULL`: đặt con trỏ về trạng thái không trỏ tới vùng nhớ nào.

## 6. Những lỗi thường gặp và nguyên tắc an toàn

### 6.1. Không kiểm tra `NULL`

Nếu `malloc()` thất bại mà chương trình vẫn sử dụng con trỏ trả về, chương trình có thể gặp lỗi khi truy cập bộ nhớ.

**Cách xử lý:** luôn kiểm tra `pointer == NULL` trước khi sử dụng vùng nhớ.

### 6.2. Quên gọi `free()` — Memory Leak

Nếu chương trình không còn sử dụng vùng nhớ nhưng không giải phóng, vùng nhớ đó vẫn bị giữ lại trong suốt thời gian chương trình hoạt động.

Hiện tượng này gọi là **rò rỉ bộ nhớ (Memory Leak)**. Nếu xảy ra nhiều lần, lượng RAM còn khả dụng có thể giảm dần.

**Cách xử lý:** gọi `free()` khi vùng nhớ không còn cần thiết.

### 6.3. Sử dụng con trỏ sau khi `free()`

Sau khi gọi `free(arr)`, vùng nhớ đã được trả lại cho bộ quản lý bộ nhớ. Truy cập `arr` như thể vùng nhớ vẫn còn hợp lệ có thể gây hành vi không xác định.

Đây là lỗi liên quan đến **con trỏ lơ lửng (Dangling Pointer)**.

**Cách xử lý:** không truy cập vùng nhớ sau khi giải phóng; có thể gán con trỏ về `NULL`.

### 6.4. Phân mảnh bộ nhớ — Memory Fragmentation

Khi chương trình liên tục cấp phát và giải phóng các vùng nhớ có kích thước khác nhau, Heap có thể bị chia thành nhiều vùng trống nhỏ. Tổng dung lượng trống có thể vẫn đủ, nhưng không có vùng liên tục phù hợp với yêu cầu cấp phát mới.

Hiện tượng này gọi là **phân mảnh bộ nhớ (Memory Fragmentation)**.

## 7. Ứng dụng và lưu ý trong Embedded C

Cấp phát động có thể hữu ích khi kích thước dữ liệu chỉ được xác định trong lúc chương trình chạy. Tuy nhiên, trong lập trình vi điều khiển (MCU), việc sử dụng `malloc()` thường cần được cân nhắc kỹ vì:

- RAM của vi điều khiển thường có giới hạn.
- Cấp phát và giải phóng nhiều lần có thể gây phân mảnh Heap.
- Nếu cấp phát thất bại mà không kiểm tra, chương trình có thể hoạt động sai.
- Thời gian cấp phát có thể không ổn định như các thao tác dùng vùng nhớ cố định, gây khó khăn cho hệ thống yêu cầu thời gian thực.

Vì vậy, nhiều dự án Embedded ưu tiên dùng bộ đệm có kích thước xác định trước hoặc chiến lược quản lý bộ nhớ phù hợp với hệ thống. `malloc()` chỉ nên được sử dụng khi đã hiểu rõ giới hạn bộ nhớ và có kế hoạch quản lý vòng đời của vùng nhớ.

## 8. Kết luận

Cấp phát động cho phép chương trình xin bộ nhớ trong khi đang chạy, giúp sử dụng RAM linh hoạt hơn khi kích thước dữ liệu chưa biết trước. Trong C, `malloc()` dùng để cấp phát vùng nhớ trên Heap và `free()` dùng để giải phóng vùng nhớ đó.

Khi sử dụng, cần kiểm tra kết quả trả về, giải phóng bộ nhớ đúng lúc và tránh truy cập vùng nhớ sau khi đã giải phóng. Đối với Embedded C, cần đặc biệt chú ý đến giới hạn RAM và nguy cơ phân mảnh bộ nhớ.
