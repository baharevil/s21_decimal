#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

//! BUG: при значении экспоненты 0x001A0000 0x00030000, число c большей
//! экспоненотой больше
int s21_equal_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2) {
  int result;

  if (value_1->sign == value_2->sign) {
    if (value_1->exponent == value_2->exponent) {
      uint16_t size;

      if (value_1->exponent != 0) {
        s21_lazy_normalization(value_1, value_1->exponent);
        s21_lazy_normalization(value_2, value_1->exponent);
      }

      if (value_1->size > value_2->size) {
        size = value_1->size;
        s21_lazy_resize(value_2, size);
      } else if (value_1->size < value_2->size) {
        size = value_2->size;
        s21_lazy_resize(value_1, size);
      } else if (value_1->size == value_2->size) {
        size = value_1->size;
      }

      result = s21_memrevcmp(value_1->mantissa, value_2->mantissa, size);

      if (value_1->sign && value_2->sign) {
        result = result * -1;
      }

    } else if (value_1->exponent > value_2->exponent) {
      result = -1;
    } else {
      result = 1;
    }
  } else if (value_1->sign < value_2->sign) {
    result = 1;
  } else {
    result = -1;
  }
  return result;
}
