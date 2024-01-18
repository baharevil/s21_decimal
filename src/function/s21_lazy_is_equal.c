#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

//! BUG: при значении экспоненты 0x001A0000 0x00030000, число c большей экспоненотой больше 
int s21_lazy_is_equal(s21_decimal *value_1, s21_decimal *value_2) {
  int result;
  uint8_t exp;
  uint16_t size;

  if (value_1->exponent.bits.sign == value_2->exponent.bits.sign) {
    exp = value_1->exponent.bits.exponent;
    if (value_1->exponent.bits.exponent < value_2->exponent.bits.exponent) {
      exp = value_2->exponent.bits.exponent;
    }

    s21_decimal_lazy value_1_l;
    s21_decimal_lazy value_2_l;

    s21_lazy_init(&value_1_l);
    s21_lazy_init(&value_2_l);

    s21_dec_to_lazy_cp(value_1, &value_1_l);
    s21_dec_to_lazy_cp(value_2, &value_2_l);

    if (value_1_l.size > value_2_l.size) {
      size = value_1_l.size;
      s21_lazy_resize(&value_2_l, size);
    } else if (value_1_l.size < value_2_l.size) {
      size = value_2_l.size;
      s21_lazy_resize(&value_1_l, size);
    } else if (value_1_l.size == value_2_l.size) {
      size = value_1_l.size;
    }

    if (&exp != NULL) {
      s21_lazy_normalization(&value_1_l, exp);
      s21_lazy_normalization(&value_2_l, exp);
    }

    result = s21_memrevcmp(value_1_l.mantissa, value_2_l.mantissa, size);

    if (value_1_l.mantissa != NULL) free(value_1_l.mantissa);
    if (value_2_l.mantissa != NULL) free(value_2_l.mantissa);
  } else if (value_1->exponent.bits.sign < value_2->exponent.bits.sign) {
    result = 1;
  } else {
    result = -1;
  }
  return result;
}
