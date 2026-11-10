# **BÁO CÁO TỔNG QUAN: MACRO TRONG NGÔN NGỮ C VÀ LẬP TRÌNH NHÙNG**

## **1. Tổng quan chung về Macro**
- **Định nghĩa:** Macro là cơ chế tiền xử lý được khai báo bằng chỉ thị `#define`, hoạt động dựa trên phương thức thay thế văn bản thuần túy trước khi chương trình được đưa đi biên dịch.
- **Phân loại:** Macro được chia thành hai loại chính là **Object-like Macro** và **Function-like Macro**.

## **2. Object-like Macro (Macro đối tượng/hằng số)**
- **Khái niệm:** Dùng để thay thế một giá trị hoặc một đoạn văn bản/ký tự cố định bằng một tên định danh (thường viết hoa toàn bộ).
- **Công dụng:** Đơn giản hóa mã nguồn, giúp code dễ đọc, dễ quản lý và dễ thay đổi.
- **Cú pháp:** `#define TEN_MACRO GIA_TRI`
- **Ví dụ thực tế:**
  ```c
  #define MAX_VALUE 100
  int threshold = MAX_VALUE; // Tiền xử lý thay thế thành int threshold = 100;
  ```

## **3. Function-like Macro (Macro hàm)**
- **Khái niệm:** Macro có chứa tham số truyền vào, nhìn giống hàm thông thường nhưng hoạt động bằng cách copy và dán văn bản nguyên bản vào vị trí gọi.
- **Cú pháp:** `#define TEN_MACRO(tham_so) ((bieu_thuc))`
- **Ví dụ thực tế:**
  ```c
  #define SQUARE(x) ((x) * (x))
  int result = SQUARE(5); // Tiền xử lý thay thế thành int result = ((5) * (5));
  ```

## **4. So sánh chi tiết Function-like Macro và Function (Hàm thông thường)**

### **Về cơ chế hoạt động**
- **Function:** Trải qua các bước gọi hàm phức tạp (đẩy tham số vào Stack, lưu địa chỉ trả về, nhảy con trỏ lệnh PC, thực thi rồi nhảy về).
- **Macro:** Hoạt động theo dạng copy và dán văn bản thô (text replacement), không có lời gọi hàm hay nhảy vùng nhớ.

### **Về Ưu điểm và Nhược điểm**
- **Macro:**
  + *Ưu điểm:* Tốc độ thực thi cực kỳ nhanh do triệt tiêu hoàn toàn chi phí gọi hàm, rất phù hợp cho vi xử lý cần tốc độ cao.
  + *Nhược điểm:* Tốn bộ nhớ (làm phình to kích thước mã máy nếu đoạn code dài và gọi lặp lại nhiều lần, ví dụ gọi 1,000 lần); không kiểm tra được kiểu dữ liệu do chỉ là sao chép văn bản; khó debug hơn.
- **Function:**
  + *Ưu điểm:* Tiết kiệm bộ nhớ tối ưu (chỉ có 1 bản mã máy duy nhất trong bộ nhớ Flash, vi điều khiển tự gọi lại khi cần); an toàn hơn vì trình biên dịch kiểm tra kiểu dữ liệu chặt chẽ; hỗ trợ debug dễ dàng.
  + *Nhược điểm:* Chậm hơn một chút do chi phí gọi hàm.

## **5. Kết luận và Lựa chọn sử dụng**
- **Nên sử dụng Macro khi:** Thay thế các đoạn code ngắn, đơn giản, tính toán nhanh và vi xử lý đòi hỏi hiệu năng, tốc độ phản hồi tức thời.
- **Nên sử dụng Function khi:** Thực thi các hàm dài, phức tạp, cần tính chính xác cao, gọi lặp lại nhiều lần mà không lo tốn dung lượng bộ nhớ, đồng thời dễ dàng trong việc gỡ lỗi (debug).
