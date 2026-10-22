# Compiler Process in C

## 1. Definition

- A **compiler** is a software tool that translates source code written in a programming language, such as C, into a lower-level language that a computer can execute.
- In C, the compilation process transforms human-readable C code into machine code through several stages.
- **GCC (GNU Compiler Collection)** is a commonly used compiler toolchain for C programming.

## 2. Purpose - Why Do We Need a Compiler?

- **Translate code:** Convert C source code into machine-understandable instructions.
- **Detect errors:** Identify syntax errors and certain other programming errors during compilation.
- **Optimize performance:** Improve the efficiency and execution speed of the generated code.
- **Create executable programs:** Combine compiled code with required libraries to produce an executable file.
- **Support Embedded Systems:** Generate machine code for a specific microcontroller or processor architecture.

## 3. Structure - The Four Main Stages

The C build process generally consists of four stages:

1. **Preprocessing**
2. **Compilation**
3. **Assembly**
4. **Linking**

```text
Source Code (.c)
       |
       v
 Preprocessing
       |
       v
 Preprocessed Code (.i)
       |
       v
   Compilation
       |
       v
 Assembly Code (.s)
       |
       v
    Assembly
       |
       v
 Object File (.o)
       |
       v
     Linking
       |
       v
 Executable File
```

*Note: These file extensions are common conventions when using GCC on many systems.*

## 4. How It Works - Step by Step

### 4.1. Preprocessing

- Handles preprocessor directives beginning with `#`.
- Expands macros defined using `#define`.
- Processes header file inclusions using `#include`.
- Removes comments from the code during preprocessing.

### 4.2. Compilation

- Translates preprocessed C code into assembly language.
- Checks the code for syntax and semantic errors.
- May optimize the code to improve performance or reduce memory usage.

### 4.3. Assembly

- Converts assembly instructions into machine code.
- Produces an object file, commonly ending in `.o` or `.obj`.
- The object file may contain unresolved references to functions or variables defined elsewhere.

### 4.4. Linking

- Combines object files with required library code or references.
- Resolves references between functions and variables across different files.
- Produces the final executable or another build artifact, depending on the target.

For example, a call to `printf()` requires the appropriate C library implementation to be available during linking.

## 5. Syntax and Example

### 5.1. Basic GCC Command

```bash
gcc main.c -o main
```

- `gcc`: Invokes the GCC compiler driver.
- `main.c`: Specifies the source file.
- `-o main`: Names the output executable `main`.

### 5.2. Inspecting Each Stage

```bash
gcc -E main.c -o main.i
gcc -S main.i -o main.s
gcc -c main.s -o main.o
gcc main.o -o main
```

Each command performs one stage of the process. GCC may also perform multiple stages automatically when given a single command.

### 5.3. Complete C Example

```c
#include <stdio.h>

#define NUMBER 10

int main(void) {
    printf("Number = %d\n", NUMBER);
    return 0;
}
```

Compile and run:

```bash
gcc main.c -o main
./main
```

Output:

```text
Number = 10
```

On Windows, the executable can be run using `main.exe`.

## 6. Applications - Especially in Embedded C

- **General C programming:** Build applications that run on computers.
- **Embedded systems:** Compile C code into machine instructions for microcontrollers such as STM32, AVR, and ESP32.
- **Cross-compilation:** Generate code for a different target architecture from the computer used for development.
- **Code optimization:** Reduce execution time, program size, or power consumption when appropriate.
- **Firmware development:** Generate object files and executable images that can be converted into formats suitable for programming a microcontroller.

### Embedded C Example

When developing firmware for an ESP32:

1. Write the program in C or C++.
2. The build system preprocesses and compiles the source files.
3. The assembler generates object files.
4. The linker combines the code and required libraries.
5. The toolchain produces firmware images that can be flashed onto the ESP32.

**Important:** The compiler does not normally execute the program. It generates code for the target processor, which executes the instructions when the program runs.