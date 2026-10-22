# Union
## 1.Muc tieu
- Hiểu cơ chế chia sẻ bộ nhớ: Nắm rõ bản chất tất cả các thành phần trong union dùng chung một vùng nhớ duy nhất.
- Phân biệt Struct và Union: Hiểu sự khác nhau về dung lượng bộ nhớ và khả năng lưu trữ dữ liệu đồng thời giữa hai kiểu.
- Tối ưu hóa bộ nhớ: Biết cách ứng dụng Union vào các bài toán tiết kiệm RAM/bộ nhớ hoặc phân tích dữ liệu nhị phân.

## 2.Khai niem
- union là một kiểu dữ liệu đặc biệt cho phép lưu trữ các kiểu dữ liệu khác nhau tại cùng một vùng nhớ. Khác với struct, tất cả các thành phần trong union dùng chung bộ nhớ với nhau.
## 3.Cu phap
Cú pháp khai báo:
    union union_name {
        Type1 field1;
        Type2 field2;
        ...
    }

Cách truy xuất: Sử dụng toán tử dấu chấm (.) giống như struct để truy cập các thành viên.

## 4.Co che hoat dong
- Dùng chung một ô nhớ: Tất cả các thành viên trong một union đều bắt đầu từ cùng một địa chỉ bộ nhớ.
- Lưu trữ một giá trị tại một thời điểm: Do dùng chung vùng nhớ, bạn có thể gán giá trị cho nhiều thành viên, nhưng union chỉ giữ lại giá trị của thành viên được gán sau cùng. Khi bạn thay đổi giá trị của thành viên này, các thành viên khác sẽ bị ghi đè theo.
- Kích thước bộ nhớ: Kích thước (dung lượng byte) của một union được xác định bởi thành viên có kích thước lớn nhất trong danh sách khai báo đó, chứ không phải tổng kích thước của tất cả các thành viên như struct

## 5.Vi du minh hoa:

#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main(void) {
    union Data data;

    data.i = 10;
    printf("data.i = %d\n", data.i);

    data.f = 220.5; // f ghi đè lên vùng nhớ của i
    printf("data.f = %.1f\n", data.f);
    printf("data.i (bi ghi che) = %d\n", data.i); // Dữ liệu bị thay đổi

    printf("Kich thuoc bo nho: %lu bytes\n", sizeof(union Data)); // 20 bytes
    return 0;
}

Terminal:   data.i = 10
            data.f = 220.5
            data.i (bi ghi che) = 1130135552
            Kich thuoc bo nho: 20 bytes


* Do union không tự lưu trữ thông tin về việc thành phần nào đang chứa dữ liệu hợp lệ, lập trình viên thường kết hợp struct và enum để tạo ra một "Variant Type".

#include <stdio.h>

typedef enum { TYPE_INT, TYPE_FLOAT, TYPE_STRING } DataType;

typedef struct {
    DataType type; // Nhãn đánh dấu kiểu dữ liệu hiện tại
    union {
        int i_val;
        float f_val;
        char *str_val;
    } value;
} Variant;

void print_variant(const Variant *v) {
    switch (v->type) {
        case TYPE_INT:    printf("Integer: %d\n", v->value.i_val); break;
        case TYPE_FLOAT:  printf("Float: %.2f\n", v->value.f_val); break;
        case TYPE_STRING: printf("String: %s\n", v->value.str_val); break;
    }
}

## 6.Ung dung:
- Trình biên dịch/Thông dịch (Parsers/Interpreters): Xây dựng Cây cú pháp trừu tượng (AST) đại diện cho các hằng số số nguyên, số thực hoặc chuỗi ký tự.
- Tiết kiệm bộ nhớ: Khi xử lý mảng lớn chứa các đối tượng có các thuộc tính thay đổi tùy theo phân loại.

### Nguồn tham khảo
- viblo.asia
- Slide bài giảng C_language - Giảng viên Phạm Doãn Tĩnh