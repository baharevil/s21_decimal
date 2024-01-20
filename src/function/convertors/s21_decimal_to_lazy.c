#include <stdlib.h>

#include "s21_decimal.h"

s21_decimal_lazy s21_decimal_to_lazy(s21_decimal value) {
  s21_decimal_lazy value_l;
  s21_lazy_init(&value_l);
  s21_from_decimal_to_lazy(&value, &value_l);
  return value_l;
}