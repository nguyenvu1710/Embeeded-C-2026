# Khái niệm
Trong lập trình (đặc biệt là C và C++), Macro là một quy tắc dùng để hướng dẫn bộ tiền xử lý (preprocessor) thay thế một đoạn mã hoặc một giá trị bằng một tên định danh trước khi chương trình được đem đi biên dịch.

Macro hoạt động giống như một "phép thay thế văn bản" (text substitution) thuần túy chứ không phải là một hàm thực sự nằm trong bộ nhớ khi chạy.
# Phân loại
- **Macro dạng đối tượng**
    Thường dùng để định nghĩa các hằng số hoặc cấu hình. Khi biên dịch gặp tên macro, nó sẽ được thay thế bằng giá trị tương ứng.
- **Macro dạng hàm**
    Nhìn có vẻ giống hàm thông thường nhưng hoạt động bằng cách chèn trực tiếp mã nguồn vào vị trí gọi.
```
#include <stdio.h>

#define PI 3.14

#define TINH_DIEN_TICH(r) ((PI) * (r) * (r))

int main() {
  double ban_kinh = 3.0;
  double dien_tich = TINH_DIEN_TICH(ban_kinh);
  printf("Dien tich hinh tron: %.2f\n", dien_tich);
  return 0;

```
# Ưu, nhược điểm
## Ưu điểm
- Tốc độ xử lý nhanh
- Linh hoạt về kiểu dữ liệu
## Nhược điểm
- Lỗi tiên đoán toán tử
- Khó gỡ lỗi
