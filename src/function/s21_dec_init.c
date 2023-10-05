#include "s21_decimal.h"

#include <stdlib.h>

void s21_dec_init(s21_decimal* dec) {
    dec->mantissa.data = calloc(sizeof(char), 1);
}
