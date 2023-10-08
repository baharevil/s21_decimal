#include "s21_decimal.h"

#include <stdlib.h>

void s21_dec_resize(s21_decimal* dec) {
    s21_size_t new_size = dec->size / 8 + 1;
    dec->data = realloc(dec->data, new_size);
}