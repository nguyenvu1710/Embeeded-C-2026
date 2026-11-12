#include "project1.h"
#include <stdarg.h>
#include <assert.h> 

int sum(int count, ...) {
    assert(count > 0);
    int a = 0;

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        int x = va_arg(args, int);
        a += x;
    }
    va_end(args);

    return a;
}

float divide(int tu, int mau) {
    assert(mau != 0);

    return (float) tu/mau;
}