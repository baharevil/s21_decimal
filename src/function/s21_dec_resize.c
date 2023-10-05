#include "s21_decimal.h"

#include <stdlib.h>

void s21_dec_resize(s21_decimal* dec, s21_size_t size) {
    dec->mantissa.data = realloc(dec->mantissa.data, size);
}