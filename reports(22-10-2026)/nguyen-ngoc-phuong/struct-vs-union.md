# SO SÁNH STRUCT VÀ UNION

| Tiêu chí | Struct | Union |
| --- | --- | --- |
| Vùng nhớ | Các thành viên có vùng lưu trữ riêng | Các thành viên dùng chung vùng nhớ |
| Giá trị lưu trữ | Không làm mất giá trị của trường khác | Có thể ghi đè dữ liệu của thành viên khác |
| Kích thước | Tổng kích thước của các thành viên | Thành viên có kích thước lớn nhất quyết định |
| Mục đích | Đóng gói nhiều thuộc tính của cùng một đối tượng (id, nhiệt độ, độ ẩm,...) | Chỉ cần một giá trị tại một thời điểm, giúp tiết kiệm bộ nhớ (giá trị trạng thái hoặc mã lỗi)


