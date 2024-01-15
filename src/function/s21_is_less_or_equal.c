#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  if (s21_lazy_is_equal(&value_1, &value_2) < 0 ||
      s21_lazy_is_equal(&value_1, &value_2) == 0)
    result = 1;
  return result;
}