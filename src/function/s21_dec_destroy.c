#include "s21_decimal.h"

#include <stdlib.h>

void s21_dec_destroy(s21_decimal* dec) {
    free(dec->mantissa.data);
    dec->mantissa.data = S21_NULL;
}
