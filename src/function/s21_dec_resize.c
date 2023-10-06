#include "s21_decimal.h"

#include <stdlib.h>

void s21_dec_resize(s21_decimal* dec) {
    dec->data = realloc(dec->data, dec->size + 1);
}