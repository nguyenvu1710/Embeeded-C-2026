# Struct vs Union

## 1. Giống nhau
 Struct và Union đều là kiểu dữ liệu User-defined (Người dùng tự định nghĩa).

## 2. Khác nhau
  ### Struct:
   - Bộ nhớ được cấp phát: Các thành viên được lưu trữ tại các vị trí bộ nhớ liên tiếp và riêng biệt. Mỗi thành viên có vùng bộ nhớ riêng.
   - kích thước:>= tổng kích thước các thành viên trong nó.
   - Truy cập: có thể truy cập vào tất cả các thành viên của nó.
   - Mục đích: Ghép nhóm các dữ liệu liên quan với nhau thành một cấu trúc truy cập đồng thời.

  ### Union:
   - Bộ nhớ được cấp phát: Các thành viên được lưu trữ tại cùng một vị trí bộ nhớ, chỉ dùng chung một vùng bộ nhớ.
   - Kích thước: = kích thước của thành viên lớn nhất trong nó.
   - Truy cập: Tại một thời điểm, chỉ một thành viên duy nhất có thể được truy cập.
   - Mục đích: Tiết kiệm bộ nhớ khi các thành viên không cần thiết phải được lưu trữ cùng lúc, khi muốn xem xét một thành viên hoặc dữ liệu khác nhau với định dạng khác nhau.

## 3. Khi nào nên dùng Struct/Union
### Nên dùng Struct khi: 
- Cần lưu trữ và truy cập đồng thời tất cả các thành viên.
- Cần ưu tiên tính rõ ràng và an toàn của code.
- Dữ liệu cần được truyền hoặc lưu trữ dưới dạng một khối.

### Nên dùng Struct khi: 
- Cần tiết kiệm bộ nhớ.
- Cần truy cập cùng một vùng bộ nhớ dưới nhiều kiểu dữ liệu khác nhau (Type Punning)
- Tổ chức thanh ghi của Vi điều khiển.