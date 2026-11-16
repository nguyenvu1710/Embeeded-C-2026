# Khái niệm
Assert là một cấu trúc lập trình được sử dụng để kiểm tra 1 điều kiện mà người viết cho rằng chắc chắn đúng tại 1 điểm trong mã nguồn.

Nếu điều kiện đó sai, chương trình sẽ lập tức dừng lại và báo lỗi, giúp ta phát hiện sớm các lỗi logic ẩn giấu trong quá trình phát triển.
# Cơ chế hoạt động
Điều kiện đúng (True): Chương trình bỏ qua câu lệnh assert và tiếp tục chạy bình thường.

Điều kiện sai (False): Chương trình văng ra ngoại lệ (AssertionError) kèm theo thông báo (nếu có) và dừng việc thực thi lại.
# Dùng Assert để
- Kiểm tra điều kiện bất biến
- Gỡ lỗi nhanh chóng
- Giúp người đọc hiểu được người viết mong muốn dữ liệu gì
# Ví dụ 
```
#include <assert.h>
#include <stdio.h>

void nhap_tuoi(int tuoi) {
  
  assert(tuoi >= 0);

  printf("Da nhap tuoi thanh cong: %d\n", tuoi);
}

int main() {
  nhap_tuoi(20);  

  nhap_tuoi(-5);  

  printf("Dong nay se khong chay.\n");
  return 0;
}
``` 
