# UNION: CÁC OBJECT CHIA SẺ CÙNG MỘT VÙNG NHỚ

## 1. Đặc điểm
Dùng chung vùng nhớ: các thành viên trong union dùng chung, chồng lên nhau trong cùng 1 vùng nhớ
Chỉ lưu trữ một giá trị tại một thời điểm: khi ghi đè giá trị mới thì giá trị cũ sẽ biến mất, không thể truy cập được nữa
Kích thước bộ nhớ: Object có size lớn nhất sẽ quyết định kích thước bộ nhớ

## 2. Cú pháp khai báo

```c
typedef union {
    float temp;
    int error;
} Result;
```

## 3. Khi nào nên dùng `union`
Khi dữ liệu có nhiều dạng nhưng tại một thời điểm chỉ cần đọc một giá trị duy nhất, ta có thể dùng `union` để tiết kiệm bộ nhớ
```c
#include <stdio.h>

typedef union {
    float temp;
    uint8_t error;
} Result;

int main(void)
{
    Result result;

    // Lần đầu: đo thành công, lưu nhiệt độ.
    result.temp = 25.5f;
    printf("Temperature: %.1f C\n", result.temp);

    // Lần sau: đo thất bại, chuyển sang lưu mã lỗi.
    result.error = 304;
    printf("Error: %d\n", result.error);

    return 0;
}
```