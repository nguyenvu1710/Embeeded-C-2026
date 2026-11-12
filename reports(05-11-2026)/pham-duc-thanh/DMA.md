# Cấp phát động (Dynamic Memory Allocation)
## 1.Muc tieu
- Hiểu bản chất: Quản lý bộ nhớ trên vùng Heap tại thời điểm chương trình đang chạy (Runtime) thay vì cố định kích thước lúc biên dịch.
- Cú pháp & quy tắc: Phân biệt rõ malloc, calloc, realloc, free trong thư viện stdlib.h và quy tắc phòng chống rò rỉ bộ nhớ (Memory Leak).
- Ứng dụng thực tế: Xây dựng cấu trúc dữ liệu động (Danh sách liên kết, Hàng đợi, Cây nhị phân) và bộ đệm kích thước thay đổi.
## 2.Khai niem
- Cấp phát động là kỹ thuật xin cấp phát và giải phóng vùng nhớ một cách chủ động từ vùng nhớ Heap trong quá trình chương trình đang thực thi (Runtime), thông qua các hàm chuẩn trong thư viện stdlib.h

## 3.Cu phap
```c
#include <stdlib.h>

// 1. Cấp phát vùng nhớ kích thước 'size' byte (chưa khởi tạo giá trị - chứa rác)
void *malloc(size_t size);

// 2. Cấp phát vùng nhớ cho 'num' phần tử, mỗi phần tử 'size' byte (khởi tạo toàn bộ về 0)
void *calloc(size_t num, size_t size);

// 3. Thay đổi kích thước vùng nhớ đã cấp phát trước đó thành 'new_size' byte
void *realloc(void *ptr, size_t new_size);

// 4. Giải phóng vùng nhớ trả lại cho Heap
void free(void *ptr);
```
## 4.Co che hoat dong
- Khác với các biến cục bộ nằm trên Stack (tự động cấp phát khi vào hàm và tự hủy khi thoát hàm), vùng nhớ Heap được quản lý bởi trình quản lý bộ nhớ (Heap Allocator):
    + Khi gọi malloc() hoặc calloc(), bộ quản lý tìm một khối nhớ trống đủ lớn trên Heap, đánh dấu là "đã sử dụng" và trả về địa chỉ đầu tiên của khối đó (hoặc trả về NULL nếu Heap đã đầy).
    + Vùng nhớ này tồn tại suốt vòng đời chương trình cho đến khi lập trình viên chủ động gọi free().
- Các rủi ro cần kiểm soát trong C nhúng:
    + Rò rỉ bộ nhớ (Memory Leak): Cấp phát nhưng quên free(), làm cạn kiệt RAM sau thời gian dài chạy.
    + Phân mảnh bộ nhớ (Heap Fragmentation): Cấp phát và giải phóng các khối nhớ kích thước khác nhau liên tục tạo ra nhiều khoảng trống nhỏ rời rạc trên Heap, khiến các lần xin cấp phát khối lớn sau đó thất bại dù tổng dung lượng trống vẫn còn.
    + Con trỏ treo (Dangling Pointer): Tiếp tục truy cập con trỏ sau khi đã free(). Do đó, sau khi free(ptr), luôn gán ptr = NULL;.

## 5.Vi du minh hoa:
```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 3;
    // Cấp phát động mảng 3 số nguyên và khởi tạo bằng 0
    int *arr = (int *)calloc(n, sizeof(int));
    if (arr == NULL) {
        printf("Loi: Khong du bo nho Heap!\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
    }

    // Mở rộng mảng lên 5 phần tử
    int *temp = (int *)realloc(arr, 5 * sizeof(int));
    if (temp != NULL) {
        arr = temp;
        arr[3] = 40;
        arr[4] = 50;
    }

    printf("Mang sau khi mo rong: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Giải phóng bộ nhớ và chống Dangling Pointer
    free(arr);
    arr = NULL;

    return 0;
}
```

Terminal:   Mang sau khi mo rong: 10 20 30 40 50

## 6.Ung dung:
- Khởi tạo một lần lúc khởi động (Startup Allocation): Trong các hệ thống nhúng yêu cầu độ ổn định cao, lập trình viên thường dùng malloc để cấp phát các cấu trúc dữ liệu (Ring Buffer, Object Pool) một lần duy nhất lúc khởi tạo phần mềm dựa theo cấu hình người dùng và giữ nguyên không free để tránh phân mảnh Heap.