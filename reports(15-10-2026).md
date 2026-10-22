   # Tổng quan về Embedded C
- Embedded C (C cho hệ thống nhúng) là việc sử dụng ngôn ngữ C để viết phần mềm điều khiển các thiết bị điện tử có nhiệm vụ chuyên biệt. Thay vì viết ứng dụng chạy trên máy tính, chương trình Embedded C chạy trực tiếp trên vi điều khiển (Microcontroller - MCU) hoặc bộ xử lý nhúng, tương tác trực tiếp với các phần cứng như chân vào/ra (I/O), bộ định thời, bộ chuyển đổi tín hiệu và các chuẩn giao tiếp.

    **Các đặc điểm khác biệt so với C tiêu chuẩn**
- Môi trường chạy (Bare-metal): Code tương tác và điều khiển trực tiếp phần cứng vật lý thay vì thông qua một hệ điều hành trung gian (như Windows hay Linux).
- Tài nguyên khắt khe: Phải tối ưu từng dòng code vì hệ thống bị giới hạn nghiêm ngặt về bộ nhớ (RAM thường chỉ có vài KB đến vài chục KB).
- Thư viện hạn chế: Không có sẵn các thư viện đồ sộ hỗ trợ. Các lệnh chuẩn như printf để in ra màn hình bị hạn chế hoặc phải tự định nghĩa lại (retarget) để truyền qua cổng nối tiếp.
- Cấu trúc vòng lặp vô tận: Chương trình nhúng không bao giờ kết thúc (không có lệnh return 0; ở cuối main). Nó chạy trong một vòng lặp while(1) vô tận để liên tục đọc tín hiệu và xử lý sự kiện với yêu cầu khắt khe về tốc độ phản hồi.
- Quy trình Debug phức tạp: Gỡ lỗi trong Embedded C không chỉ là tìm lỗi logic phần mềm, mà còn đòi hỏi bạn phải kiểm tra mạch điện, đo đạc tín hiệu bằng đồng hồ vạn năng hoặc máy hiện sóng (Oscilloscope) để xác định lỗi thuộc về phần cứng hay code.

    **Các khái niệm và thao tác cốt lõi**
    Khi làm việc với Embedded C, có 3 công cụ bạn bắt buộc phải làm chủ để can thiệp được vào các thiết bị ngoại vi:
- Con trỏ (Pointers): Trong vi điều khiển, các thiết bị ngoại vi và thanh ghi điều khiển được thiết kế ánh xạ thành các địa chỉ bộ nhớ vật lý. Bạn sẽ dùng con trỏ để trỏ thẳng vào các địa chỉ này, từ đó đọc hoặc ghi giá trị để cấu hình phần cứng theo ý muốn.

- Từ khóa volatile: Khai báo này cấm trình biên dịch (compiler) tự động tối ưu hóa biến. Trong hệ thống nhúng, một biến (ví dụ: trạng thái nút nhấn) có thể bị thay đổi đột ngột bởi phần cứng bên ngoài thông qua Ngắt (Interrupt) dù trong code không có lệnh nào tác động tới nó. Gắn volatile phía trước biến sẽ buộc CPU phải đọc lại giá trị thực tế của biến này từ RAM ở mỗi lần sử dụng, tránh việc sử dụng lại giá trị cũ đang lưu trong cache.

- Thao tác Bit (Bitwise Operations): Mỗi chân vật lý của chip tương ứng với 1 bit trên thanh ghi điều khiển. Vì ngôn ngữ C không có kiểu dữ liệu cho từng bit đơn lẻ, bạn phải dùng các phép toán thao tác bit (& AND, | OR, ^ XOR, <<, >>) để bật, tắt hoặc kiểm tra trạng thái của một chân cụ thể mà không làm thay đổi trạng thái của các chân khác nằm cùng trên thanh ghi đó.

    ## Lộ trình tự học Embedded C cơ bản
1.Nắm vững ngôn ngữ C và Điện tử cơ bản:Ôn tập lại cú pháp C, đặc biệt tập trung vào con trỏ, struct, và các phép toán bit (bitwise). Song song đó, tìm hiểu cách đọc sơ đồ mạch điện cơ bản, điện trở, LED, nút nhấn và cách dùng đồng hồ vạn năng (VOM) để đo thông mạch, điện áp.
    |
    V
2.Làm quen với vi điều khiển 8-bit:AVR hoặc PIC.Bắt đầu với một kit phát triển đơn giản như Arduino Uno, nhưng không dùng thư viện Arduino. Hãy cài đặt môi trường lập trình C thuần (như Atmel Studio) để tập viết code can thiệp thẳng vào thanh ghi cấu hình GPIO (nháy LED, đọc nút nhấn).
    |
    V
3.Lập trình các ngoại vi cốt lõi (Bare-metal):Tiến hành đọc tài liệu (Datasheet) của chip để cấu hình và điều khiển các thành phần quan trọng: Ngắt ngoài (External Interrupts), Bộ định thời (Timers/Counters để tạo xung PWM điều khiển động cơ), và Chuyển đổi tín hiệu tương tự sang số (ADC).
    |
    V
4.Làm chủ các giao thức truyền thông:Học cách lập trình để vi điều khiển giao tiếp với các cảm biến hoặc chip khác thông qua 3 chuẩn giao tiếp phổ biến nhất: UART (giao tiếp với máy tính, module Bluetooth/Wifi), I2C (giao tiếp cảm biến, màn hình LCD), và SPI (giao tiếp tốc độ cao với thẻ nhớ, chip mở rộng).
    |
    V
5.Chuyển sang kiến trúc 32-bit ARM Cortex-M:STM32.Khi đã hiểu bản chất qua chip 8-bit, hãy nâng cấp lên dòng vi điều khiển chuẩn công nghiệp (thường là STM32). Làm quen với môi trường IDE chuyên nghiệp (như STM32CubeIDE), cách đọc Reference Manual, cấu hình Clock Tree và sử dụng thư viện HAL của ST.
    |
    V
6.Tiếp cận Hệ điều hành thời gian thực (RTOS):Khi dự án phình to, cấu trúc vòng lặp while(1) tuần tự sẽ làm hệ thống chậm trễ. Bạn cần học cách tích hợp và sử dụng FreeRTOS để quản lý đa tác vụ (Tasks), cấp phát tài nguyên (Mutex, Semaphore) và truyền dữ liệu giữa các luồng (Queue).