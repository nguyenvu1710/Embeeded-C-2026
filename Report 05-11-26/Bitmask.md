# BITMASK

Bitmask (mặt nạ bit) là một chuỗi các bit được sử dụng kết hợp với các phép toán thao tác bit (bitwise operations như AND, OR, XOR, NOT) để kiểm tra, bật, tắt hoặc đảo trạng thái của các bit cụ thể trong một số nguyên.

# Các phép toán bitwise thường gặp
AND (&): Dùng để kiểm tra xem một bit có đang bật (1) hay không.

OR (|): Dùng để bật (đặt thành 1) một hoặc nhiều bit.

XOR (^): Dùng để đảo trạng thái của một bit (từ 0 thành 1, hoặc 1 thành 0).

Dịch trái (<<): 1 << i tạo ra một bitmask mà chỉ có bit thứ i bật (giá trị bằng $2^i$).

# Ví dụ dễ hiểu: quản lý quyền hạn
Giả sử hệ thống của bạn có 3 quyền:

READ (Đọc) = bit thứ 0 (giá trị 2^0 =1)

WRITE (Ghi) = bit thứ 1 (giá trị 2^1 = 2)

EXECUTE (Thực thi) = bit thứ 2 (giá trị 2^2 = 4)


## Cách gộp quyền (Dùng phép OR)
Nếu một người dùng vừa có quyền READ 1 vừa có quyền WRITE 2:

Bitmask = 1 | 2 = 3


## Cách kiểm tra quyền (Dùng phép AND)
Kiểm tra xem người dùng có quyền WRITE 2 hay không:

Bitmask & 2 =3 &2 =2

## Cách thêm quyền mới (Dùng phép OR)
Thêm quyền EXECUTE 4 vào bitmask hiện tại 

Bitmask = 3|4 = 7 (hệ nhị phân 111- đủ cả 3 quyền)
