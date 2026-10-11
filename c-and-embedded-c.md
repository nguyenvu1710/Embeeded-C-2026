# SO SÁNH STANDARD C VÀ EMBEDDED C


## 1. Bảng so sánh tổng quan

| Tiêu chí | Standard C | Embedded C |
|---|---|---|
| **Phần cứng**| CPU máy tính, RAM và ROM, điểm chung là dung lượng lớn | MCU (Microcontroller Unit) tích hợp Flash, RAM và ngoại vi, điểm chung là tài nguyên rất khắt khe, chỉ có đến hàng chục KB |
| **Hệ điều hành** | Chạy trên OS (Windows, Linux, macOS) | hạy trên vi điều khiển (MCU) — bare-metal (không có OS) hoặc RTOS  |
| **Trước khi chạy** | OS và runtime chuẩn bị môi trường | User chịu phần lớn trách nhiệm mà OS làm trong C thông thường, cần phải build startup code và linker script (quản lý vùng nhớ) |
| **Chạy chương trình** | OS load từ disk | Flash qua programmer (ST-Link, J-Link...) |
| **Hàm 'main'** | Có thể chạy xong rồi thoát (return 0 ở cuối main) | Thường chạy vòng lặp vô hạn while(1) để liên tục đọc dữ liệu |
| **Đầu vào** | Bàn phím, file, tham số dòng lệnh | Các khối phần cứng: GPIO, ADC, UART, SPI, I²C, CAN… |
| **Đầu ra** | Terminal, file, mạng,... | LED, màn hình, relay, động cơ,...|
| **Bộ nhớ** | Thường có bộ nhớ ảo và bảo vệ theo từng process | MCU nhỏ thường không có bộ nhớ ảo; một số có MPU |
| **Công cụ build** | Compiler cho máy tính | Thường dùng cross compiler cho kiến trúc chip |
| **Kết quả build** | File thực thi như `.exe` | Thường là ELF để debug, HEX/BIN để nạp |
| **Debug** | Debugger sẵn có trên Text Editor | Debug probe, SWD/JTAG, UART và dụng cụ đo |
| **ối ưu** | Tốc độ chạy chương trình  | Kích thước code + RAM + điện năng |
| **Phụ thuộc phần cứng** | Chương trình chạy cách ly và không trực tiếp can thiệp phần cứng | Can thiệp trực tiếp vào thanh ghi phần cứng |


## 2. Các khái niệm và thao tác cốt lõi trong Embedded C

### 2.1. Con trỏ

Hầu hết các vi điều khiển đều ánh xạ thanh ghi ngoại vi vào không gian địa chỉ của CPU, do đó con trỏ có tác dụng truy cập trực tiếp vào địa chỉ thanh ghi và ghi dữ liệu

### 2.2. Thao tác bit

Phần cứng thường dùng từng bit để điều khiển từng chức năng, mỗi chân trên vi điều khiển hay dãy dữ liệu trên thanh ghi đều được mã hóa thành từng bit, do đó thao tác bit giúp ta sửa đúng chức năng cần sửa mà không gán lại dữ liệu của toàn bộ thanh ghi.

Embedded dùng bit thường xuyên vì thanh ghi và giao thức chứa nhiều trường bit. Tuy nhiên, **không áp dụng máy móc các phép đọc-sửa-ghi vào mọi thanh ghi**: có thanh ghi chỉ ghi, đọc có tác dụng phụ, hoặc ghi 1 để xóa cờ.

### 2.3. Từ khóa 'volatile', 'const', 'static'

- 'volatile': các giá trị có thể thay đổi bất ngờ, do phần cứng hoặc ngắt ngoài luồng thực thi hiện tại. Từ khóa trên báo cho trình biên dịch phải thực hiện các lần truy cập cần thiết, không tùy ý dùng lại giá trị cũ.
- 'const': thể hiện dữ liệu không được sửa qua cách truy cập tương ứng. Compiler thường bố trí bảng này vào vùng chỉ đọc
- 'static': giữ giá trị giữa các lần gọi để dùng cho các lần sau.



# LỘ TRÌNH HỌC EMBEDDED C CƠ BẢN

**C cơ bản → C dùng trong embedded → làm quen MCU → ngoại vi → dự án nhỏ.**

### 1. Học C cơ bản

- Biến, kiểu dữ liệu, điều kiện, vòng lặp, hàm, mảng và chuỗi.
- Tập viết chương trình đơn giản trên máy tính, biết biên dịch và tìm lỗi.

### 2. Nắm các phần C hay dùng trong embedded

- Con trỏ, `struct`, `enum`; hệ nhị phân, hex và thao tác bit.
- Hiểu các từ khóa `const`, `static`, `volatile`, bộ nhớ và cách chia file `.c`/`.h`.
- Thực hành xử lý mảng dữ liệu, đặt/xóa/kiểm tra bit.

### 3. Làm quen vi điều khiển (MCU)

- Tìm hiểu CPU, RAM, Flash, thanh ghi và cách đọc tài liệu chip.
- Dùng một board có sẵn để tập build, nạp code, debug; bắt đầu bằng nháy LED và đọc nút nhấn.

### 4. Học các ngoại vi cơ bản

- Lần lượt học GPIO → timer và ngắt → UART → ADC/PWM → I²C/SPI.
- Mỗi phần làm một bài nhỏ: gửi dữ liệu, đọc cảm biến hoặc điều khiển độ sáng LED.

### 5. Ghép thành dự án nhỏ

- Ví dụ: đọc cảm biến theo chu kỳ, gửi kết quả qua UART và bật LED khi vượt ngưỡng.
- Khi đã vững, tìm hiểu thêm máy trạng thái, viết driver và RTOS.


