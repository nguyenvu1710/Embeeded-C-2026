
# Pointer in Embedded C Programming

## 1. Goals

- Understand:
    + what pointer is
    + why it is important in Embedded C 
    + Basic method to using pointer

## 2. Definition

- Pointers are variables that contain the address or location of a variable, constant, function, or data object.

int x = 20;
int *apple = &x;   // apple holds address of x

- So a pointer **isn't the actual data**. It simply represents the **address or location** of the data that is being referenced.

## 3. Importance

- Access memory-mapped hardware registers
- Manage arrays and buffers *efficiently*
    + A pointer can point to the first element of an array, allowing you to access elements without **copying the entire array**.

- Implement *pass-by-reference* in functions
    + can alter existing variable at the original address **!=** changing a copy value

- Optimize memory usage with minimal overhead
    + Basically: Recalling an existing variable is much more storage efficient than creating a copy of it - if the variable is huge then a copy will double the occupy avaible memory.
    + a pointer will always occupy a fixed amount of byte (based on the system: 16/32/64 bit ~ 2/4/8 bytes) so 



## 5.

## 6. Sources

- https://www.ewskills.com/embedded-c/pointer
- https://www.geeksforgeeks.org/c/c-pointers/
