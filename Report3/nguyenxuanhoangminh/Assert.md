# `assert` trong Embedded C

## 1. Khái niệm

`assert` là một **macro** được định nghĩa trong thư viện `<assert.h>`. Nó dùng để kiểm tra các giả định logic mà lập trình viên cho rằng phải luôn đúng khi chương trình chạy.

Trong lập trình vi điều khiển, `assert` thường được dùng để phát hiện sớm những lỗi như:

- Giá trị đầu vào nằm ngoài phạm vi cho phép.
- Con trỏ hoặc dữ liệu không ở trạng thái hợp lệ.
- Một điều kiện cần thiết trước khi thực hiện thao tác phần cứng không được đáp ứng.

Mục đích chính của `assert` là hỗ trợ **debug** theo nguyên tắc *Fail-Fast*: phát hiện lỗi ngay tại vị trí xảy ra thay vì để lỗi tiếp tục lan sang các phần khác của chương trình.

## 2. Cú pháp và cách hoạt động

Cú pháp:

```c
assert(condition);
```

Trong đó, `condition` là biểu thức logic cần kiểm tra.

- **Điều kiện đúng** (có giá trị khác 0): chương trình tiếp tục chạy bình thường.
- **Điều kiện sai** (bằng 0): `assert` xuất thông tin chẩn đoán, thường gồm biểu thức bị sai, tên tệp (`__FILE__`) và số dòng (`__LINE__`), sau đó gọi `abort()` để kết thúc chương trình.

Có thể hình dung nguyên lý như sau:

```c
if (!(condition)) {
    // Ghi thông tin về lỗi
    abort();
}
```

Đây là cách mô tả đơn giản để hiểu cơ chế; phần ghi thông báo cụ thể phụ thuộc vào thư viện C và môi trường chạy.

## 3. Ví dụ: Kiểm tra giá trị PWM

Giả sử hàm điều khiển PWM chỉ chấp nhận `duty` trong khoảng từ 0% đến 100%.

```c
#include <stdio.h>
#include <assert.h>

void PWM_SetDutyCycle(int duty)
{
    // Kiểm tra giá trị trước khi xử lý
    assert(duty >= 0 && duty <= 100);

    // Thực hiện thiết lập PWM
    printf("PWM set to %d%%\n", duty);
}

int main(void)
{
    PWM_SetDutyCycle(50);   // Hợp lệ: chương trình tiếp tục

    // PWM_SetDutyCycle(150); // Không hợp lệ: assert được kích hoạt

    return 0;
}
```

Khi gọi `PWM_SetDutyCycle(50)`, biểu thức kiểm tra đúng nên chương trình tiếp tục.

Nếu bỏ dấu chú thích và gọi `PWM_SetDutyCycle(150)`, điều kiện kiểm tra sai. `assert` phát thông tin lỗi và gọi `abort()`, vì vậy chương trình không tiếp tục thực hiện các lệnh phía sau tại lần gọi đó.

## 4. Debug mode và Release mode

`assert` có hai cách hoạt động tùy cấu hình biên dịch:

| Chế độ | Cách hoạt động |
|---|---|
| **Debug** | Kiểm tra điều kiện. Khi điều kiện sai, chương trình báo lỗi và dừng. |
| **Release** | Khi macro `NDEBUG` được định nghĩa trước khi include `<assert.h>`, các lệnh `assert()` bị vô hiệu hóa. |

Ví dụ:

```c
#define NDEBUG
#include <assert.h>
```

Khi `NDEBUG` được định nghĩa, `assert(condition)` được thay bằng biểu thức rỗng `((void)0)` trong quá trình tiền xử lý. Vì vậy, điều kiện bên trong `assert` cũng không được thực hiện.

## 5. Luồng hoạt động tổng thể

1. **Tiền xử lý:** kiểm tra macro `NDEBUG` đã được định nghĩa hay chưa.
2. **Biên dịch:** nếu `NDEBUG` chưa được định nghĩa, chương trình giữ lại phần kiểm tra của `assert`; nếu đã được định nghĩa, các lệnh `assert` bị loại bỏ.
3. **Thực thi:** ở chế độ có bật `assert`, chương trình đánh giá điều kiện tại vị trí gọi.
4. **Xử lý kết quả:** điều kiện đúng thì chạy tiếp; điều kiện sai thì ghi thông tin chẩn đoán và gọi `abort()`.

## 6. Lưu ý khi sử dụng trong Embedded C

- Dùng `assert` để kiểm tra **giả định logic trong quá trình phát triển và debug**, không nên xem nó là cơ chế kiểm tra đầu vào duy nhất của sản phẩm.
- Không đặt các thao tác có tác dụng phụ trong điều kiện `assert`, vì điều kiện này sẽ không được thực hiện khi `NDEBUG` được bật.
- Không phụ thuộc vào `assert` để bảo vệ phần cứng trong Release mode, vì các lệnh này có thể đã bị loại bỏ.
- Trên vi điều khiển, cách xuất thông báo lỗi và xử lý `abort()` phụ thuộc vào thư viện C, hệ thống runtime và cấu hình dự án.

**Kết luận:** `assert` giúp lập trình viên phát hiện sớm những giả định sai trong chương trình. Nó đặc biệt hữu ích khi debug firmware, nhưng cần kết hợp với kiểm tra dữ liệu và cơ chế xử lý lỗi phù hợp trong sản phẩm thực tế.
