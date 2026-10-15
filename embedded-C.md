

&#x20;

1\. Embedded C là việc lập trình cho các thiết bị có tài nguyên hạn chế như vi điều khiển, cảm biến. với mục tiêu là điều khiển, tương tác với phần cứng. Hiểu đơn giản là một hệ thống máy tính được tích hợp vào một thiết bị để thực hiện một thao tác cụ thể 



2\. Cách hoạt động của hệ thống nhúng: user phải tự cấu hình I/O, input là các cảm biến,...; output là cơ cấu chấp hành (các thiết bị được điều khiển); phần code logic. tất cả đó chính là **embedded C**



3\. sự khác nhau giữa C và embedded C:

&#x09;- môi trường: embedded C chạy trên vi điều khiển thay vì OS

&#x09;- mục đích: điều khiển các thiết bị 

&#x09;- input: đọc từ cảm biến, GPIO (General Purpose Input/Output - Cổng vào/ra đa năng), giao tiếp ngoại vi

&#x09;- bộ nhớ: cực kì hạn chế, RAM thường chỉ có vài KB đến vài chục KB 

&#x09;- thời gian: phản hồi nhanh, vd: cảm biến va chạm trên xe -> phải phản hồi nhanh -> để bật túi khí

&#x09;- debug: phức tạp. không chỉ phần mềm mà cả phần cứng (kiểm tra mạch điện, đo đạc tín hiệu)

4\. thao tác cốt lõi khi làm việc với embedded C

&#x09;a. con trỏ (pointer)

&#x09;	- Là biến dùng để lưu địa chỉ bộ nhớ của một biến khác.

&#x09;	- \&x: lấy địa chỉ của biến x.

&#x09;	- \*p: truy cập giá trị tại địa chỉ mà con trỏ p trỏ tới.

&#x09;	- Có thể dùng để thay đổi dữ liệu, xử lý mảng và truy cập thanh ghi phần cứng.

&#x09;	- Trong Embedded C, pointer giúp chương trình tương tác trực tiếp với bộ nhớ và phần cứng

&#x09;b. volatile

&#x09;	- Là từ khóa báo cho compiler rằng giá trị có thể thay đổi ngoài luồng thực thi thông thường.

&#x09;	- Giúp compiler không tối ưu các lần đọc/ghi volatile theo cách làm mất ý nghĩa của chúng.

&#x09;	- Thường dùng với thanh ghi phần cứng và biến được cập nhật trong trình phục vụ ngắt. 

&#x09;c. thao tác Bit -Bitwise 

&#x09;	- Trong Embedded C, bitwise thường dùng để cấu hình thanh ghi và điều khiển thiết bị.

&#x09;	- Pointer giúp truy cập đúng địa chỉ; bitwise giúp điều khiển chính xác từng bit tại đó sử dung các phép toán trên bit 0/1 





5\. lộ trình học embedded C

&#x09;1, ngôn ngữ C cơ bản

&#x09;2, pointer địa chỉ bộ nhớ, \&, \*, void \*, NULL, function pointer, pointer to pointer

&#x09;3, bitwise

&#x09;4, các từ khóa thao tác quan trọng: const, static, volatile.

&#x09;5, quản lý, sử lý mảng dữ lieu: struct, enum, typedef, union, const, static

&#x09;

&#x09;











&#x09; 



