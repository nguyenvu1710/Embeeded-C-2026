# khái niệm
Cấp phát động (Dynamic Memory Allocation) là cách một chương trình máy tính xin cấp một khoản bộ nhớ (RAM) trong lúc chương trình đang chạy (runtime), thay vì phải ấn định sẵn kích thước từ lúc viết code (cấp phát tĩnh).
# phân biệt
- **Cấp phát tĩnh** Trong code: int arr[100]; (Cố định mảng 100 phần tử từ lúc biên dịch)
- **cấp phát động** Trong code: xin hệ điều hành một vùng nhớ vừa đủ dùng bằng câu lệnh, dùng xong thì trả lại (giải phóng) để tiết kiệm RAM.
# các hàm cấp phát động
- **malloc(size) (Memory Allocation)**:

Xin cấp phát một vùng nhớ có kích thước bằng size (tính bằng byte).

Đặc điểm: Vùng nhớ mới cấp phát sẽ chứa các giá trị rác (giá trị ngẫu nhiên đang có sẵn trong RAM tại thời điểm đó).

-**calloc(num, size) (Contiguous Allocation)**:

Xin cấp phát bộ nhớ cho num phần tử, mỗi phần tử có kích thước size byte.

Đặc điểm: Khác với malloc, calloc sẽ tự động gôm sạch và khởi tạo tất cả các byte bằng 0.

-**realloc(ptr, new_size) (Re-allocation)**:

Dùng khi bạn đã xin một vùng nhớ rồi nhưng thấy không đủ (hoặc thừa), muốn nới rộng hoặc thu hẹp lại. Nó sẽ điều chỉnh kích thước của vùng nhớ cũ (ptr) thành new_size.

-**free(ptr)**:

Cực kỳ quan trọng! Sau khi dùng xong vùng nhớ trỏ bởi ptr, bạn phải gọi hàm này để trả lại bộ nhớ cho hệ thống. Nếu quên gọi, chương trình sẽ bị rò rỉ bộ nhớ (memory leak).
