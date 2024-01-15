#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

int s21_lazy_is_equal(s21_decimal *value_1, s21_decimal *value_2) {
  int result;

  if (value_1->exponent.bits.sign == value_2->exponent.bits.sign) {
    int exp_min = 2;
    uint8_t exp = value_1->exponent.bits.exponent;
    if (value_1->exponent.bits.exponent < value_2->exponent.bits.exponent) {
      exp = value_2->exponent.bits.exponent;
      exp_min = 1;
    }

    s21_decimal_lazy value_1_l = {0};
    s21_decimal_lazy value_2_l = {0};

    s21_dec_to_lazy_cp(value_1, &value_1_l);
    s21_dec_to_lazy_cp(value_2, &value_2_l);

    if (exp_min == 1)
      s21_lazy_normalization(&value_1_l, exp);
    else
      s21_lazy_normalization(&value_2_l, exp);
    result = memcmp(value_1_l.mantissa, value_2_l.mantissa, value_1_l.size);
    if (value_1_l.mantissa != NULL) free(value_1_l.mantissa);
    if (value_2_l.mantissa != NULL) free(value_2_l.mantissa);
  } else if (value_1->exponent.bits.sign < value_2->exponent.bits.sign) {
    result = 1;
  } else {
    result = -1;
  }
  return result;
}
