# **BITWISE VÀ BITMASK TRONG LẬP TRÌNH C NHÙNG**

## **1. Tổng quan về Bitwise (Phép toán trên bit)**

Trong thế giới lập trình nhúng, vi điều khiển (MCU) xử lý dữ liệu ở cấp độ phần cứng thông qua hệ thống nhị phân gồm các dòng **0** và **1**.

- **Bitwise** là tập hợp các toán tử tác động trực tiếp lên từng bit đơn lẻ bên trong các toán hạng (thanh ghi phần cứng).
+ Các phép toán bitwise cơ bản trong ngôn ngữ C bao gồm:
  - **AND (&)**
  - **OR (|)**
  - **XOR (^)**
  - **NOT (~)**
  - **Dịch trái (<<)**
  - **Dịch phải (>>)**

## **2. Bản chất và Mục đích tối thượng của Bitmask (Mặt nạ bit)**

### **Khái niệm**

- **Bitmask** là một chuỗi các bit nhị phân được cấu hình đóng vai trò như một chiếc "mặt nạ" để che đậy, lựa chọn, hoặc tương tác chính xác với một hoặc nhiều bit cụ thể trong một biến số nguyên, hoàn toàn không làm ảnh hưởng đến các vùng bit lân cận xung quanh.

### **Tại sao phải dùng Bitmask trong C nhúng?**

+ **Tối ưu hóa bộ nhớ cực đỉnh:** Thay vì lãng phí tài nguyên bằng cách khai báo nhiều biến `bool` rời rạc, kỹ thuật bitmask cho phép nhồi nhét **32 trạng thái độc lập** vào trong **đúng một biến duy nhất** (ví dụ kiểu dữ liệu `uint32_t` 4 bytes).
+ **Giao tiếp trực tiếp với thanh ghi phần cứng (Registers):** Các ngoại vi của MCU được điều khiển bằng cách thay đổi giá trị các bit trong thanh ghi thông qua bitmask một cách chuẩn xác.
+ **Hiệu năng thực thi chớp nhoáng:** Các phép toán bitwise được xử lý trực tiếp tại tầng ALU (Arithmetic Logic Unit) của CPU chỉ trong **1 chu kỳ máy**.

## **3. Nguyên lý hoạt động chi tiết của các phép toán Bitwise**

### **A. Bảng quy luật cơ bản**

Giả sử có hai bit $A$ và $B$:

- **AND (&):** Trả về $1$ chỉ khi **cả** $A$ **và** $B$ **đều bằng** $1$. Dùng để lọc hoặc xóa bit về $0$.
- **OR (|):** Trả về $1$ nếu **ít nhất một trong hai** bằng $1$. Dùng để bật bit thành $1$.
- **XOR (^):** Trả về $1$ nếu $A$ và $B$ **khác nhau**. Dùng để đảo trạng thái bit (toggle).
- **NOT (~):** Đảo ngược hoàn toàn ($0 \rightarrow 1$, $1 \rightarrow 0$). Tạo mặt nạ nghịch đảo.

### **B. Kỹ thuật tạo mặt nạ định vị (1 << n)**

Biểu thức **1 << n** nghĩa là dịch chuyển số **1** sang trái **n** vị trí (tính từ phải sang, bắt đầu từ vị trí $0$).

+ `1 << 0` tạo ra mặt nạ tại bit 0 (giá trị thập phân là `1`).
+ `1 << 1` tạo ra mặt nạ tại bit 1 (giá trị thập phân là `2`).
+ `1 << 2` tạo ra mặt nạ tại bit 2 (giá trị thập phân là `4`).
+ `1 << 3` tạo ra mặt nạ tại bit 3 (giá trị thập phân là `8`).

## **4. Các thao tác kinh điển khi lập trình với Bitmask**

Giả sử ta có một thanh ghi trạng thái thiết bị 8-bit (`uint8_t reg`) đang lưu giá trị nhị phân ban đầu là `0b00001100`:

### **1. Bật bit (Set a bit thành 1)**

- **Nguyên lý:** Dùng phép **OR (|)** kết hợp với mặt nạ. Bất kỳ số nào OR với $0$ giữ nguyên, OR với $1$ sẽ ép thành $1$.
+ **Công thức C:** `reg |= (1 << n);`

### **2. Tắt bit (Clear a bit thành 0)**

- **Nguyên lý:** Dùng phép **AND (&)** với mặt nạ nghịch đảo `~(1 << n)`. Vị trí cần tắt sẽ mang giá trị $0$, các vị trí khác mang giá trị $1$.
+ **Công thức C:** `reg &= ~(1 << n);`

### **3. Đảo trạng thái bit (Toggle bit)**

- **Nguyên lý:** Dùng phép **XOR (^)** với mặt nạ. Đang là $1$ thành $0$, đang là $0$ thành $1$.
+ **Công thức C:** `reg ^= (1 << n);`

### **4. Kiểm tra trạng thái bit (Check bit)**

- **Nguyên lý:** Dùng phép **AND (&)** để cô lập bit cần kiểm tra, các bit khác bị triệt tiêu về $0$.
+ **Đoạn code minh họa:**

```c
if (reg & (1 << n)) {
    // Bit thứ n đang BẬT (1)
} else {
    // Bit thứ n đang TẮT (0)
}
```
