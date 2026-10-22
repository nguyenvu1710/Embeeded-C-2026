# Enum
## 1.Muc tieu
- Hiểu bản chất: Thay thế các "con số ma thuật" (magic numbers) bằng tập hợp hằng số số nguyên tên gợi nhớ.
- Cú pháp & quy tắc: Khai báo enum, thiết lập giá trị tự động hoặc gán thủ công.
- Ứng dụng thực tế của enum

## 2.Khai niem
- enum (Enumeration) định nghĩa một tập hợp các hằng số số nguyên có tên đại diện. Sử dụng enum thay cho các hằng số ma thuật (magic numbers) giúp mã nguồn minh bạch, dễ đọc và dễ bảo trì.


## 3.Cu phap

enum TenEnum {
    GIA_TRI_1,
    GIA_TRI_2,
    GIA_TRI_3,
    ...
};

ví dụ:
enum week_day {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY}; 
    /* now use it */ 
enum week_day today = TUESDAY;

terminal: 2

## 4.Co che hoat dong
- Trong ngữ cảnh của trình biên dịch, các giá trị enum thực chất là các số nguyên (int).
- Mặc định, phần tử đầu tiên được gán giá trị 0, các phần tử tiếp theo tự động tăng dần lên 1 đơn vị.
- Có thể gán thủ công bất kỳ giá trị số nguyên nào cho từng phần tử.

## 5.Vi du minh hoa:

#include <stdio.h>

// Khai báo Enum trạng thái phản hồi HTTP
typedef enum {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_NOT_FOUND = 404,
    HTTP_INTERNAL_SERVER_ERROR = 500
} HttpStatusCode;

int main(void) {
    HttpStatusCode response_code = HTTP_NOT_FOUND;

    if (response_code == 404) {
        printf("Loi: Khong tim thay tai nguyen!\n");
    }

    return 0;
}

Terminal: Loi: Khong tim thay tai nguyen!

## 6.Ung dung:
- Giúp mã nguồn chuyển đổi trạng thái rõ ràng thay vì dùng các số "ma" (magic numbers) như 0, 1, 2, 3
- Chỉ định tốc độ baud của UART, chế độ hoạt động của ADC, hay kênh truyền thông
### Nguồn tham khảo
- viblo.asia
- Slide bài giảng C_language - Giảng viên Phạm Doãn Tĩnh