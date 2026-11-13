#BITMASK
Bitmask (mặt nạ bit) là một chuỗi các bit được sử dụng kết hợp với các phép toán thao tác bit (bitwise operations như AND, OR, XOR, NOT) để kiểm tra, bật, tắt hoặc đảo trạng thái của các bit cụ thể trong một số nguyên.

#Các phép toán bitwise thường gặp
AND (&): Dùng để kiểm tra xem một bit có đang bật (1) hay không.
OR (|): Dùng để bật (đặt thành 1) một hoặc nhiều bit.
XOR (^): Dùng để đảo trạng thái của một bit (từ 0 thành 1, hoặc 1 thành 0).
Dịch trái (<<): 1 << i tạo ra một bitmask mà chỉ có bit thứ i bật (giá trị bằng $2^i$).

#Ví dụ dễ hiểu: quản lý quyền hạn
Giả sử hệ thống của bạn có 3 quyền:
READ (Đọc) = bit thứ 0 (giá trị 2^0 =1)
WRITE (Ghi) = bit thứ 1 (giá trị 2^1 = 2)
EXECUTE (Thực thi) = bit thứ 2 (giá trị 2^2 = 4)

##Cách gộp quyền (Dùng phép OR)
Nếu một người dùng vừa có quyền READ ($1$) vừa có quyền WRITE ($2$):$$\text{Bitmask} = 1 \mid 2 = 3 \quad (\text{hệ nhị phân: } 011_2)$$Cách kiểm tra quyền (Dùng phép AND)Kiểm tra xem người dùng có quyền WRITE (giá trị $2$) hay không:$$\text{Bitmask} \ \& \ 2 = 3 \ \& \ 2 = 2 \quad (\neq 0 \rightarrow \text{Có quyền})$$Cách thêm quyền mới (Dùng phép OR)Thêm quyền EXECUTE (giá trị $4$) vào bitmask hiện tại (3):$$\text{Bitmask mới} = 3 \mid 4 = 7 \quad (\text{hệ nhị phân: } 111_2 \rightarrow \text{Đủ cả 3 quyền})$$
