# Enum trong C

## 1. Mục tiêu

- Hiểu `enum` là gì và tại sao cần dùng.
- Biết cách khai báo và sử dụng `enum`.
- Biết cách kết hợp `enum` với `typedef`.
- Hiểu ứng dụng của `enum` trong Embedded C.

## 2. Khái niệm

`enum` (enumeration) là một kiểu dữ liệu cho phép đặt tên cho các giá trị thuộc một nhóm. Theo mặc định, chúng thường tương ứng với các số nguyên 0, 1, 2, 3...

Nhờ vậy, khi so sánh trạng thái, có thể viết theo ý nghĩa thay vì phải nhớ từng con số.

**Mục tiêu chính:** Làm code rõ nghĩa, dễ quản lý các trạng thái và giảm nhầm lẫn, chứ không phải bảo đảm tiết kiệm RAM hay tăng tốc độ so sánh.

## 3. Cú pháp

```c
enum TenEnum {
    TRANG_THAI_1,      // = 0
    TRANG_THAI_2,      // = 1
    TRANG_THAI_3 = 5   // = 5 (gán tùy ý)
};
```

Ví dụ:

```c
enum EngineState {
    ENGINE_OFF,    // = 0
    ENGINE_ON = 1,
};

// Thay vì viết: if (state == 1)
// Viết: if (state == ENGINE_ON) → rõ nghĩa hơn
```

## 4. Cơ chế hoạt động

- C sử dụng `enum` để so sánh giá trị số, chứ không hiểu ý nghĩa thực tế của chúng.
- Vi điều khiển thường chạy chương trình liên tục, phải xác định nó đang ở giai đoạn nào để xử lý đúng. `enum` giúp biểu diễn những trạng thái đó một cách rõ ràng.

## 5. Ví dụ minh họa

### Kết hợp với typedef:

```c
typedef enum {
    cnhat, t2 = 2, t3 = 3
} day;

// Khai báo biến:
day mai = t3;
printf("%d\n", mai);  // Output: 3
```

### Ví dụ khác:

```c
typedef enum {
    lihi = 12, hieu = 28, lihikiku = 1209
} hihi;

hihi ngay_sinh_cua_hieu = hieu;
printf("%d", ngay_sinh_cua_hieu);  // Output: 28
```

## 6. Ứng dụng thực tế

Trong Embedded C, `enum` đặc biệt hữu ích khi quản lý nhiều trạng thái:
- Động cơ tắt/bật
- Lỗi cảm biến
- Các chế độ hoạt động của hệ thống

Ví dụ: quản lý trạng thái máy trạng thái (state machine) trong vi điều khiển.
