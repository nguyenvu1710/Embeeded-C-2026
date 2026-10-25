# Struct Pointer

## 1.Muc tieu

* Hiểu cách tạo và sử dụng con trỏ trỏ tới biến kiểu struct.
* Nắm rõ cú pháp truy xuất thành viên struct thông qua con trỏ bằng toán tử mũi tên (`->`).
* Tối ưu hiệu năng chương trình khi truyền struct dung lượng lớn vào các hàm.

## 2.Khai niem

* Struct Pointer (Con trỏ Struct) là biến con trỏ lưu trữ địa chỉ vùng nhớ của một biến kiểu struct.

## 3.Cu phap

Cú pháp khai báo: `struct StructName *ptr;`

Cách truy xuất thành viên: `ptr->member_name` (tương đương với `(*ptr).member_name`).

## 4.Co che hoat dong

* Con trỏ chỉ lưu trữ địa chỉ bắt đầu của struct trong RAM (kích thước con trỏ là 4 bytes hoặc 8 bytes).
* Toán tử `->` tự động giải con trỏ và tính khoảng cách (offset) đến thuộc tính cần truy cập.
* Giúp truyền dữ liệu vào hàm theo dạng tham chiếu (pass-by-reference), tránh việc sao chép toàn bộ struct gây tốn bộ nhớ Stack.

## 5.Vi du minh hoa

```c
#include <stdio.h>

struct Point {
    int x;
    int y;
};

void movePoint(struct Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

int main() {
    struct Point p1 = {10, 20};
    struct Point *ptr = &p1;

    movePoint(ptr, 5, -5);

    printf("Toa do moi: (%d, %d)\n", ptr->x, ptr->y);
    return 0;
}
```

## 6.Ung dung thuc te

* Ánh xạ các thanh ghi phần cứng (Hardware Registers) trong vi điều khiển.
* Xây dựng các cấu trúc dữ liệu động như Danh sách liên kết (Linked List), Cây (Tree), Hàng đợi (Queue).