#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal_lazy value_1_l = s21_decimal_to_lazy(value_1);
  s21_decimal_lazy value_2_l = s21_decimal_to_lazy(value_2);  
  if (s21_equal_lazy(&value_1_l, &value_2_l) == 0) result = 1;
  return result;
}