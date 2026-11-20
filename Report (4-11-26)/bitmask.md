# Bitmask


## 1. Mục tiêu

- Hiểu bitmask là gì, tại sao lại sử dụng bitmask.
- Biết các thao tác bitwise cơ bản.
- Biết cú pháp của bitmask.
- Ứng dụng của bitmask

## 2. Khái niệm
- Bitmask là kỹ thuật thao tác và kiểm tra các bit cụ thể trong một số. Một bitmask là một giá trị nhị phân được thiết kế để chỉ định các bit nào cần quan tâm. Bitmasking thường được ứng dụng để xác định trạng thái của bit, bật tắt bit hoặc đảo ngược bit tuỳ vào yêu cầu của bài toán.
- Trong C nhúng, Bitmask sử dụng các phép toán bit để đọc, bật, tắt hoặc thay đổi từng bit trong thanh ghi của vi điều khiển. Dùng bitmask để thao tác chính xác với bit cần thiết mà không ảnh hưởng đến những bit còn lại. 

## 3. Thao tác bitwise cơ bản
- NOT: Đảo ngược bit (1 thành 0, 0 thành 1)

```c
~a
```

- AND: Trả về 1 nếu cả 2 bit là 1

```c
a & b
```

- OR: Trả về 1 nếu ít nhất 1 bit là 1

```c
a | b
```

- XOR: Trả về 1 nếu 2 bit khác nhau

```c
a ^ b
```

- Shift left: Dịch các bit sang trái n vị trí (tương đương 2^n)
```c
a << n
```

- Shift right: Dịch các bit sang phải n vị trí (tương đương 2^n)
```c
a >> n
```

## 4. Cú pháp

```c
tenMask = toan-tu-bitwise
```

- ví dụ:
```c
mask = mask | (1<< 4);
```
  + hoặc
```c
mask =| (1<< 4);
```


## 5. Ví dụ cụ thể
```c
#include <stdio.h>
int main()
{
    unsigned char REG = 0; // nhi phan: REG = 0000 0000
    REG |= (1 << 0); //set bit 0: REG moi: 0000 0001
    REG |= (1 << 2); // set bit 2: REG moi: 0000 0101
    REG |= (1 << 4); // set bit 4: REG moi: 0001 0101
    printf("REG = %d\n", REG);

    REG &= ~(1 << 2);// 1 << 2 = 0000 0100, ~(1<<2) = 1111 1011
    // &: REG moi = 001 0001
    printf("tắt bit 2: %d\n", REG);
    // tuong tu ta co:
    REG ^= (1 << 4);
    printf("đảo bit 4: %d\n", REG);

    if (REG & (1 << 0))
        printf("Bit 0 = ON\n");
    else
        printf("Bit 0 = OFF\n");

    return 0;
}
```

## 6. Ứng dụng
- Cấu hình và điều khiển thanh ghi phần cứng (Hardware Registers)
  + Các ngoại vi của vi điều khiển (GPIO, UART, SPI, I2C, ADC, Timer...) được điều khiển thông qua việc đọc/ghi các bit trong các thanh ghi.
  + Thay vì phải dùng các struct cồng kềnh hoặc tốn nhiều biến riêng lẻ, bitmask cho phép gom nhóm cấu hình chế độ chân (Input/Output, Pull-up/Pull-down, tốc độ) vào một hoặc vài byte/word duy nhất.
- Tối ưu bộ nhớ RAM và không gian lưu trữ (Memory Optimization)