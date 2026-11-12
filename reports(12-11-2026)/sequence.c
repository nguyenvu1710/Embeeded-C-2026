#include "sequence.h"
#include <assert.h>
#include <stdarg.h>

double Sum(int count, ...) {
    va_list num;
    double total = 0.0;

    assert(count > 0);

    va_start(num, count);
    for (int i = 0; i < count; i++) {
        total += va_arg(num, double);
    }
    va_end(num);

    return total;
}

bool CheckDenom(double denominator) {
    return denominator != 0.0;
}

bool DivideSums(double numerator, double denominator, double *result) {
    if (!CheckDenom(denominator)) {
        return false;
    }

    *result = numerator / denominator;
    return true;
}
