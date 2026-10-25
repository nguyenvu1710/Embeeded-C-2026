# Struct

## 1.Muc tieu

* Nắm vững khái niệm về struct và cách đóng gói nhiều thuộc tính của một đối tượng.
* Hiểu cách truy xuất, gán giá trị và quản lý bộ nhớ của struct.
* Áp dụng struct vào việc tổ chức dữ liệu một cách khoa học.

## 2.Khai niem

* struct (Structure) là một kiểu dữ liệu do người dùng tự định nghĩa, cho phép kết hợp các biến có kiểu dữ liệu khác nhau vào cùng một nhóm để quản lý một đối tượng thực tế.

## 3.Cu phap

Cú pháp khai báo: `struct StructName { Type1 member1; Type2 member2; ... };`

Cách sử dụng: Khai báo biến `struct StructName variable_name;` và truy cập thành viên bằng toán tử dấu chấm (`.`).

## 4.Co che hoat dong

* Mỗi thành viên trong struct được cấp phát một vùng nhớ riêng biệt.
* Các thành viên được sắp xếp liên tiếp nhau trong bộ nhớ.
* Trình biên dịch có thể tự động thêm bộ nhớ đệm (Memory Alignment/Padding) để tối ưu hóa truy xuất CPU.

## 5.Vi du minh hoa

```c
#include <stdio.h>

struct Student {
    int id;
    char name[30];
    float gpa;
};

int main() {
    struct Student s1 = {101, "Nguyen Van A", 3.8};

    printf("ID: %d\n", s1.id);
    printf("Name: %s\n", s1.name);
    printf("GPA: %.2f\n", s1.gpa);

    return 0;
}
```

## 6.Ung dung thuc te

* Định nghĩa các đối tượng thực tế có nhiều thuộc tính (Sinh viên, Hóa đơn, Sản phẩm,...).
* Đóng gói các gói tin dữ liệu trong lập trình mạng và nhúng.