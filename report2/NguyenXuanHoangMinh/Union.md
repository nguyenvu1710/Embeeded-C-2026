# Union

## Definition

- `union` is a user-defined data type in C, similar to `struct`.
- Unlike `struct`, where each member has its own memory space, all members of a `union` share the **same memory location**.
- A union can contain members of different data types, such as `int`, `float`, and `char`.
- Because the members share memory, the union can store a value through one member at a time. Writing to one member can overwrite the representation previously stored through another member.

## Purpose - Why use union?

- Mainly for **saving memory** when different data types are used at different times.
- union usually be use as an alternative to struct
- In Embedded C, `union` is commonly used to:
    + Save memory when storing alternative data types.
    + Interpret communication data in different formats.
    + Work with hardware registers or data packets when different representations of the same memory are needed. This requires care because some techniques depend on the compiler and hardware.

## Syntax

```c
union UnionName {
    dataType member1;
    dataType member2;
};

union UnionName variable;
```

- To access a member, use the `.` operator.
- To access a member through a pointer, use the `->` operator.
- Unlike `typedef enum`, `typedef` is optional. Without it, you must write `union UnionName` when declaring a variable.

## Example 1 - Union with different data types

```c
#include <stdio.h>

union Data {
    int number;
    float decimal;
};

int main(void) {
    union Data d;

    d.number = 10;
    printf("Number: %d\n", d.number);

    d.decimal = 3.14f;
    printf("Decimal: %.2f\n", d.decimal);

    return 0;
}
```

**Output**

```text
Number: 10
Decimal: 3.14
```

**How it works**

- `d.number = 10;` stores the value `10` through the `number` member.
- `printf()` displays `d.number` before another member is assigned.
- `d.decimal = 3.14f;` writes to the same shared memory through the `decimal` member.
- After this assignment, you should not expect the previous value of `d.number` to remain available.

## Example 2 - Union in Embedded C

```c
#include <stdio.h>

typedef union {
    unsigned int value;
    unsigned char bytes[4];
} Data;

int main(void) {
    Data data;

    data.value = 0x12345678;

    printf("Value: 0x%X\n", data.value);

    return 0;
}
```

**How it works**

- `value` stores an integer.
- `bytes` provides another way to access the same memory as individual bytes.
- This can be useful when examining or processing data byte by byte.
- The exact byte order depends on the system's endianness, and the example assumes `unsigned int` occupies 4 bytes. Check the target platform before relying on these assumptions.

## Comparison: Struct & Union

## Applications in Embedded C

- Saving RAM in memory-constrained microcontrollers.
- Processing communication packets and binary data.
- Representing alternative data formats that share storage.
- Working with hardware data representations when the platform and compiler behavior are understood.

## Important note

- `struct`: each member has its own storage.
- `union`: all members share storage.
- The size of a union is at least large enough for its largest member, with possible extra space for alignment.
- A union does not automatically convert one member's value into another data type. Avoid assuming that reading a different member produces a meaningful converted value.
