# Tổ chức chương trình C với các file `.h` (header) và `.c` (source)

Trong C, một chương trình lớn thường được chia thành nhiều module để **tái sử dụng** và **đóng gói**. Mỗi module gồm một file header (`.h`) chứa *giao diện* (interface) – khai báo các hàm, kiểu, hằng số công khai – và một file source (`.c`) chứa *phần cài đặt* (implementation) – định nghĩa hàm, biến và logic chi tiết. Cách chia này giúp biên dịch riêng từng module, tăng tốc độ build và giảm lỗi. Ví dụ, một thư mục dự án Embedded C có thể có cấu trúc phổ biến như sau:

```
project/
  include/         # Chứa các file header chung
    motor.h
  src/             # Chứa các file .c (định nghĩa)
    motor.c
    main.c
  build/           # Chứa file object (do build sinh ra)
  bin/             # Chứa file thực thi (binary) sau khi link
  Makefile         # Tập lệnh build
```

Theo khuyến nghị, thư mục `include/` chứa các file `.h` với **API công khai** của module, còn thư mục `src/` chứa các file `.c` chứa phần implement chi tiết. Cách tổ chức này giúp dễ dàng **nhận biết chức năng** của module mà không cần xem mã nguồn chi tiết, đồng thời dễ dàng tái sử dụng (chỉ cần include header là dùng được).

## File header (`.h`) – Giao diện (Interface)

File header định nghĩa **giao diện công khai** của module, gồm:

- **Macro, hằng số**: Các `#define` giá trị cố định nếu cần chia sẻ.  
- **Kiểu dữ liệu**: `typedef`, `struct`, `enum` công khai (nếu các hàm trả về hoặc nhận kiểu này).  
- **Khai báo hàm (prototype)**: Chỉ định chữ ký của các hàm công khai.  
- **Khai báo biến toàn cục (extern)**: Nếu cần chia sẻ biến giữa các file, header sẽ khai báo với từ khóa `extern`. (*Ví dụ*: `extern int counter;`).  
- **Include guard**: Macro bảo vệ (`#ifndef ... #define ... #endif`) để tránh nội dung header bị chèn nhiều lần trong cùng một *translation unit*. 

Ngoài ra, ở đầu header thường có `#include` các header khác mà thư viện cần. **Lưu ý:** Header chỉ chứa *khai báo* (declarations), không nên chứa định nghĩa (definitions) của hàm hay biến (ngoại trừ các hằng số hay hàm `static inline`/`inline` theo thiết kế). Nếu định nghĩa hàm hoặc biến trong header (không được phép lặp lại), sẽ gặp lỗi **Multiple definition** khi link. Ví dụ, trong `motor.h` ta có thể viết như sau:

```c
#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

// Giá trị giới hạn cho tốc độ
#define MOTOR_MAX_SPEED 100

// Kiểu trả về của hàm điều khiển
typedef enum {
    MOTOR_OK,
    MOTOR_ERROR
} MotorStatus;

// Biến toàn cục được chia sẻ (khai báo extern, chỉ định ở 1 file .c)
extern int motorErrorCount;

// Khai báo các hàm công khai của module
void Motor_Init(void);
MotorStatus Motor_SetSpeed(int speed);

#endif /* MOTOR_H */
```

Ở ví dụ trên, `motor.h` chỉ chứa macro (`MOTOR_MAX_SPEED`), kiểu `MotorStatus`, khai báo `extern` và khai báo các hàm. **Include guard** (`#ifndef MOTOR_H ... #endif`) đảm bảo nếu file này được include nhiều lần (trực tiếp hoặc gián tiếp), nội dung chỉ xuất hiện một lần trong mỗi translation unit. Như Stephen C (StackOverflow) giải thích, include guard ngăn chặn việc định nghĩa lại các hàm/biến khi header bị include nhiều lần: lần đầu tiên macro định nghĩa là `MOTOR_H` chưa tồn tại nên nội dung được chèn vào, các lần sau `MOTOR_H` đã định nghĩa nên nội dung sẽ bị bỏ qua. 

## File source (`.c`) – Cài đặt (Implementation)

File `.c` chứa **phần hiện thực** (code) của module:

- Thêm `#include "module.h"` để đảm bảo định nghĩa khớp với khai báo.  
- Định nghĩa các hàm đã khai báo trong header.  
- Định nghĩa **một duy nhất** biến toàn cục cho mỗi `extern` đã khai báo. Ví dụ, file `motor.c` sẽ định nghĩa `int motorErrorCount = 0;` tương ứng với `extern int motorErrorCount;` trong header. Mỗi biến toàn cục chỉ nên được định nghĩa ở một file `.c` duy nhất.  
- Khai báo/bình tĩnh (định nghĩa) các hàm và biến **nội bộ** của module với từ khóa `static`, để chúng chỉ khả dụng trong file đó. Từ khóa `static` ở phạm vi file (file scope) tạo *internal linkage*, nghĩa là hàm/biến chỉ "nhìn thấy" trong module đó. (Ngược lại, nếu không dùng `static`, một hàm hay biến không được khai báo `static` mặc định có *external linkage*, có thể bị gọi từ file khác). Việc dùng `static` giúp "ẩn" phần riêng tư của module khỏi bên ngoài và tránh xung đột tên. Ví dụ:

```c
#include "motor.h"
#include <stdio.h>

// Biến nội bộ của module (chỉ có trong motor.c)
static int currentSpeed = 0;

// Định nghĩa biến toàn cục duy nhất (cho extern ở header)
int motorErrorCount = 0;

// Hàm nội bộ, chỉ dùng trong motor.c (không được khai báo ở header)
static void updateHardware(int speed) {
    // Giả sử đây là code điều khiển phần cứng PWM
    printf("Cập nhật tốc độ PWM: %d\n", speed);
}

void Motor_Init(void) {
    currentSpeed = 0;
    motorErrorCount = 0;
    // Thực hiện khởi tạo phần cứng motor tại đây...
}

MotorStatus Motor_SetSpeed(int speed) {
    if (speed < 0 || speed > MOTOR_MAX_SPEED) {
        motorErrorCount++;
        return MOTOR_ERROR;
    }
    currentSpeed = speed;
    updateHardware(speed);  // gọi hàm nội bộ
    return MOTOR_OK;
}
```

Ở trên, `currentSpeed` và `updateHardware()` được khai báo `static`, nghĩa là *riêng tư* trong `motor.c`. Chúng không thể bị code bên ngoài truy cập, tránh xung đột tên với các module khác. Ngược lại, `motorErrorCount` được định nghĩa một lần ở đây (dành cho `extern` trong `motor.h`), và các file khác muốn dùng biến này chỉ cần `extern` trong header. Như chính sách của C đã nêu: **mỗi biến/hàm dùng chung phải có một định nghĩa** (ở đúng một file .c), còn header chỉ khai báo extern hoặc prototype. 

Tóm lại theo C K&R và các tài liệu tham khảo: *“Exactly one definition for everything shared. One `.c` file defines it; the header declares it with `extern` (objects) or a prototype (functions). Internal linkage for everything private. If no other file needs it, write `static`.”*. Điều này khẳng định: header chỉ chứ khai báo (external), còn phần cài đặt mới định nghĩa (internal).

## Quy trình biên dịch (Preprocessing → Compilation → Linking)

Khi biên dịch chương trình C đa file, có ba giai đoạn chính:

- **Tiền xử lý (Preprocessing)**: Bộ tiền xử lý (preprocessor) quét các chỉ thị bắt đầu bằng `#`. Nó **mở rộng macro** (`#define`), **xóa bình luận**, **xử lý `#include`** (chèn nội dung file header vào vị trí `#include`), và `#ifdef/#ifndef` (cho các include guard). Kết quả của bước này là file nguồn đầy đủ (ở dạng `.i` hay text) với tất cả header đã được “dán” vào. Như đã giải thích, mỗi file `.c` sau bước tiền xử lý là một *translation unit* riêng biệt, bởi các `#include` đã được thay thế bằng nội dung thật của header. (Nói cách khác, header không phải là unit biên dịch riêng; nó chỉ góp phần nội dung cho file .c.)

- **Biên dịch (Compilation)**: Trình biên dịch dịch từ mã C đã qua tiền xử lý thành mã máy (trước hết ở dạng assembly, rồi object). Mỗi file `.c` được biên dịch **riêng lẻ** thành một file đối tượng `.o`. Trong giai đoạn này, compiler thực hiện kiểm tra lỗi ngữ pháp, kiểm tra kiểu dữ liệu với prototype đã có trong header. Ví dụ, nếu ta compile `motor.c` và `main.c` riêng, các lệnh (với gcc) có thể là:
  ```
  gcc -Wall -c src/motor.c -o build/motor.o
  gcc -Wall -c src/main.c  -o build/main.o
  ```
  Cờ `-c` cho biết chỉ tạo file object (không link).  

- **Liên kết (Linking)**: Cuối cùng, linker sẽ gộp các file `.o` với thư viện cần thiết, giải quyết các tham chiếu hàm/bien ngoài. Ví dụ, linker sẽ ghép `motor.o` và `main.o` thành chương trình thực thi:
  ```
  gcc build/main.o build/motor.o -o bin/program
  ```
  Như GeeksforGeeks mô tả, “Linking is the final stage of the compilation process. The linker combines object files with the required libraries and resolves references to external functions and variables”. Ở giai đoạn này, nếu chúng ta thiếu định nghĩa cho một hàm hoặc biến (hoặc có định nghĩa trùng lặp), linker sẽ báo lỗi. Ví dụ, nếu chúng ta định nghĩa `Motor_SetSpeed` trong cả `motor.c` và `main.c`, hay không có định nghĩa nào nhưng dùng prototype, link sẽ lỗi.

Tóm lại: header và source được xử lý nối tiếp. **Header được xử lý** trong giai đoạn tiền xử lý (nội dung được dán vào mã nguồn), **file .c được biên dịch** thành `.o`, rồi **linker** kết nối `.o` với nhau.

## Những điều cần nhớ khi viết header/source

- **Định nghĩa vs Khai báo**: Theo quy tắc Biên Dịch của C, *header chỉ chứa khai báo*, *source chứa định nghĩa*. Nếu ta đặt **định nghĩa** (function body hay biến toàn cục không `extern`) trong header, và header đó được include ở hai chỗ, ta sẽ có **2 định nghĩa** giống nhau – dẫn đến lỗi linker “multiple definition”. Ví dụ, nếu viết `int foo = 5;` trong `common.h` rồi `#include "common.h"` ở cả `a.c` và `b.c`, linker sẽ báo trùng tên `foo`. Để tránh, chỉ khai báo extern trong header và định nghĩa một lần trong một file .c duy nhất.

- **`extern` biến toàn cục**: Mỗi biến toàn cục dùng chung phải theo “exactly one definition rule”: header chỉ **khai báo** `extern int x;`, và một file .c duy nhất định nghĩa `int x = giá trị;`. Nếu không, hoặc nếu định nghĩa nhiều lần (hoặc không định nghĩa nào), ta sẽ gặp lỗi link (thiếu định nghĩa hoặc định nghĩa đôi).

- **`static` ở file scope**: Từ khóa `static` ở ngoài hàm (file scope) chỉ thị *internal linkage*. Như đã nêu, một tên với static chỉ “thấy” trong file đó. Điều này ngược với scope cục bộ (stack). Như VLSI Mentor giải thích: “At file scope, `static` controls linkage — it makes the name private to the translation unit”. Nhắc lại: muốn ẩn hàm hay biến trong file, dùng `static`; nếu không dùng, hàm/bien mặc định có external linkage và có thể xung đột với các module khác.

- **Include đúng file**: Nên `#include` file `.h`, không bao giờ include trực tiếp file `.c`. Nếu nhúng một file .c, nội dung file đó sẽ được copy (như #include bản copy của nó) vào nhiều chỗ, gây ra *nhiều định nghĩa trùng* khi link. Cách đúng là compile riêng từng .c rồi link.

- **Kiểm tra thay đổi và tái biên dịch**: Nếu sửa header, mọi file .c nào include header đó (trực tiếp hoặc gián tiếp) phải được biên dịch lại, vì interface thay đổi có thể ảnh hưởng đến chúng. Ngược lại, nếu chỉ sửa file .c, về lý thuyết chỉ cần biên dịch lại file đó. Tuy nhiên, thực tế còn phụ thuộc hệ thống build (Makefile). Hệ thống đơn giản thường cho phép tái biên dịch độc lập từng file.

- **Phân biệt Compile và Link**: Việc *compile* (gcc -c) chỉ xử lý một file .c, kiểm tra cú pháp và tạo .o. *Link* (gcc ...) kết hợp các .o thành chương trình. Có thể xảy ra lỗi ở giai đoạn compile (sai cú pháp, thiếu header) hoặc ở giai đoạn link (định nghĩa thiếu/đúp, hàm không tìm thấy).

- **Trường hợp ngoại lệ (Header-only)**: Một vài tình huống ngoại lệ tồn tại ở C99/C++ như hàm `inline`, hàm template, hoặc các biến `constexpr` trong C++ được định nghĩa trong header mà không gây lỗi. Ví dụ, một hàm `static inline` có thể định nghĩa trong header để nhờ compiler thay thế inline. Tuy nhiên, đây là trường hợp đặc biệt và không phổ biến trong Embedded C thuần túy; chúng không làm thay đổi nguyên tắc chung trên.

## Ví dụ minh họa: Module điều khiển Motor

Giả sử ta có một module `Motor` điều khiển động cơ điện. Ta tạo các file như sau:

- **`motor.h`** (giao diện): chứa `#define`, `typedef`, `extern`, prototype.  
- **`motor.c`** (implement): định nghĩa biến, hàm, dùng `static` nội bộ.  
- **`main.c`** (ứng dụng): include `motor.h`, gọi hàm để khởi tạo và đặt tốc độ motor.

Ví dụ cụ thể:

```c
/* motor.h */
#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define MOTOR_MAX_SPEED 100

typedef enum { MOTOR_OK, MOTOR_ERROR } MotorStatus;

// Khai báo biến toàn cục được chia sẻ
extern int motorErrorCount;

// Prototype hàm
void Motor_Init(void);
MotorStatus Motor_SetSpeed(int speed);

#endif /* MOTOR_H */
```

```c
/* motor.c */
#include "motor.h"
#include <stdio.h>   // Ví dụ chỉ để in đầu ra giả lập

static int currentSpeed = 0;    // Biến riêng nội bộ

int motorErrorCount = 0;        // Định nghĩa duy nhất cho extern

// Hàm tĩnh nội bộ, chỉ gọi trong motor.c
static void updateHardware(int speed) {
    printf("PWM set to %d%%\n", speed);
}

void Motor_Init(void) {
    currentSpeed = 0;
    motorErrorCount = 0;
    // Khởi tạo phần cứng motor ở đây
}

MotorStatus Motor_SetSpeed(int speed) {
    if (speed < 0 || speed > MOTOR_MAX_SPEED) {
        motorErrorCount++;
        return MOTOR_ERROR;
    }
    currentSpeed = speed;
    updateHardware(speed);
    return MOTOR_OK;
}
```

```c
/* main.c */
#include <stdio.h>
#include "motor.h"

int main(void) {
    Motor_Init();
    MotorStatus status = Motor_SetSpeed(80);
    if (status == MOTOR_OK) {
        printf("Motor da chay voi toc do 80.\n");
    } else {
        printf("Sai so! Toc do khong hop le.\n");
    }
    return 0;
}
```

Giả sử thư mục dự án như cấu trúc trên, ta biên dịch và chạy được:

```
gcc -Wall -c src/motor.c -o build/motor.o
gcc -Wall -c src/main.c  -o build/main.o
gcc build/main.o build/motor.o -o bin/program
./bin/program
```

Kết quả sẽ in ra (giả sử thí dụ phần cứng):

```
PWM set to 80%
Motor da chay voi toc do 80.
```

Ở ví dụ này, **nội dung** được phân chia rõ ràng: `motor.h` chứa **interface** (macro, kiểu, extern, prototype), còn `motor.c` chứa **cài đặt** (định nghĩa biến, hàm). `main.c` chỉ include `motor.h` và gọi hàm mà không cần biết cài đặt bên trong. 

## Các lỗi thường gặp và cách khắc phục

1. **Lỗi định nghĩa trùng (multiple definition)**: Thường do định nghĩa hàm/biến trong header hoặc #include nhầm file .c. Ví dụ, nếu viết thân hàm `Motor_Init` trong `motor.h` (không inline) hoặc định nghĩa `motorErrorCount` trong `motor.h` (không `extern`), sau khi include nhiều lần sẽ báo lỗi “multiple definition”. Khắc phục: chỉ để **khai báo** trong header, định nghĩa duy nhất trong một source file.

2. **Lỗi undeclared identifier (chưa khai báo)**: Do quên include header hoặc viết nhầm tên. Ví dụ, gọi `Motor_Init()` mà không `#include "motor.h"`, trình biên dịch không biết khai báo hàm ở đâu. Giải pháp: chắc chắn include header chứa prototype của hàm trước khi dùng.

3. **Lỗi liên kết (linker) “undefined reference”**: Xảy ra khi dùng hàm/biến mà không có định nghĩa. Ví dụ, khai báo `extern int motorErrorCount;` nhưng quên định nghĩa `int motorErrorCount = 0;` trong `motor.c`. Linker sẽ báo không tìm thấy `motorErrorCount`. Cách sửa: thêm định nghĩa trong đúng file `.c`.

4. **Lỗi thiếu include guard**: Nếu thiếu guard và header được include nhiều lần (thường do phụ thuộc lẫn nhau), trình biên dịch sẽ báo lỗi định nghĩa lại struct hoặc hàm. Ví dụ, không có guard ở `motor.h` và `motor.h` được include lặp, sẽ thấy lỗi “redefinition”. Giải pháp: luôn dùng include guard (`#ifndef ...`).

5. **Sai extern/static**: Ví dụ, khai báo biến toàn cục nhưng lỡ thêm `static` ở header, mỗi file include sẽ có bản sao biến riêng biệt, dẫn đến logic sai và khó gỡ lỗi. Nhớ rằng `static` ở file-scope cắt external linkage. Hoặc ngược lại, quên `static` khi cần thì biến “leak” ra ngoài.

Nhìn chung, “golden rule” của header C: **header chỉ chứa *khai báo*; source chứa *định nghĩa***. Các ngoại lệ (inline, template C++) rất hiếm trong Embedded C.

## Kết luận

Việc phân chia code C thành header và source có nhiều lợi ích: làm rõ ràng **API công khai**, **tái sử dụng** module, cho phép biên dịch riêng (giảm thời gian build), và **ẩn thông tin nội bộ**. Header đóng vai trò “hợp đồng” (interface) giữa các module, trong khi source chứa chi tiết. Khi phát triển Embedded C, khái niệm này cũng giúp tiết kiệm bộ nhớ (nhiều chế độ chia code ra) và bảo vệ phần cứng (nếu có lỗi logic, chương trình có thể dừng lại dễ dàng qua assert/chế độ debug). 

Để tránh nhầm lẫn, người viết code nên nhớ:
- **Đừng định nghĩa** hàm hay biến toàn cục trong header trừ trường hợp cần thiết (hàm `inline`, hằng số, v.v.).  
- Dùng `extern` trong header cho biến dùng chung, và `static` ở đầu file `.c` cho phần riêng.  
- Dùng **include guard** với mỗi header.  
- **Không include file .c**; compile riêng rồi link.  
- Sửa header ảnh hưởng đến toàn bộ các module phụ thuộc; sửa source thường chỉ cần compile lại file đó (tuy nhiên hệ thống build như Make cần khai báo đúng phụ thuộc để tự động làm việc).  
- Phân biệt rõ **compile vs. link**: sự cố thiếu file header gây lỗi compile, thiếu definition gây lỗi link.

Với người mới học, điều quan trọng là hiểu *tại sao* phải tách như vậy. Mục đích không chỉ là “theo quy tắc”, mà để **mã sạch, dễ kiểm soát và an toàn hơn**. Quá trình tiền xử lý/biên dịch/đối chiếu giúp phát hiện lỗi sớm: nếu có mâu thuẫn giữa khai báo và định nghĩa, compiler/linker sẽ báo lỗi, giúp sửa nhanh trước khi phần cứng gặp sự cố.  

**Tóm lại**, tổ chức code theo module với các file `.h` (interface) và `.c` (implementation) là cách tiếp cận chuẩn trong C. Cách làm này giúp quản lý mã tốt hơn và tạo thói quen lập trình chắc chắn cho Embedded C.

**Tài liệu tham khảo:** Các quy tắc trên được tổng hợp từ C89/C99 chuẩn và các hướng dẫn của chuyên gia, ví dụ như K&R/C để đảm bảo một định nghĩa duy nhất, sử dụng `extern/static`, include guard và các lỗi biên dịch/chạy liên quan.
