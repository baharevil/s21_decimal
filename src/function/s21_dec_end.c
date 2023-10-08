#include "s21_decimal.h"

unsigned char * s21_dec_end(s21_decimal* dec) {
    return dec->data + dec->size / 8 + 1;
}
