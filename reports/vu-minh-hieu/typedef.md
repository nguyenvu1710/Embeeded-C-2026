# Typedef trong C

## 1. Mục tiêu

- Hiểu `typedef` là gì và tại sao cần dùng.
- Biết cách sử dụng `typedef` với các kiểu dữ liệu cơ bản.
- Biết cách kết hợp `typedef` với `enum`, `struct`, `union`.

## 2. Khái niệm

`typedef` dùng để đặt một tên mới (bí danh) cho một kiểu dữ liệu đã tồn tại.

Trong Embedded C, thường phải làm việc với các kiểu dữ liệu như số nguyên, cấu trúc dữ liệu hoặc kiểu enum. Tên kiểu đôi khi dài và khó đọc, nên `typedef` giúp đặt tên ngắn gọn hơn.

## 3. Cú pháp

```c
typedef <kiểu_dữ_liệu_gốc> <tên_mới>;
```

Ví dụ:

```c
typedef int so_nguyen;
// Viết ngoài main
// Sau này khi gọi: so_nguyen x = 12312; thì sẽ được hiểu là int
```

## 4. Kết hợp typedef với các kiểu dữ liệu khác

`typedef` có thể kết hợp với nhiều kiểu dữ liệu: `enum`, `struct`, `union`, cũng như các kiểu cơ bản `int`, `float`, `char`, ...

### Ví dụ với mảng ký tự:

```c
typedef char String[50];
typedef char shit[2];

int main() {
    String name = "Hieu va lihi";
    printf("%s\n", name);

    shit user1 = "H";
    shit user2 = "L";
    printf("%s\n", user1);
    printf("%s\n", user2);
    return 0;
}
```

### Ví dụ với enum:

```c
typedef enum {
    cnhat, t2 = 2, t3 = 3
} day;

// Khi khai báo biến:
day mai = t3;  // thay vì: enum day mai = t3;
```

## 5. Ứng dụng thực tế

- Rút gọn tên kiểu dữ liệu dài, giúp code dễ đọc hơn.
- Đặc biệt hữu ích khi kết hợp với `struct` và `enum` trong Embedded C để tránh phải viết lặp lại `struct` hay `enum` trước mỗi khai báo biến.
