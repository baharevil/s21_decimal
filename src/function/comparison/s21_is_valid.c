#include <execinfo.h>
#include <stddef.h>

#include "s21_decimal.h"

int s21_decimal_is_valid(const void *decimal) {
  return !((*(s21_decimal *)decimal).exponent.bits.empty0 ||
           (*(s21_decimal *)decimal).exponent.bits.empty1);
}

int s21_decimal_ptr_is_valid(const void *decimal) {
  return !(((s21_decimal *)decimal)->exponent.bits.empty0 ||
           ((s21_decimal *)decimal)->exponent.bits.empty1);
}

int s21_lazy_is_valid(const void *lazy) {
  return !(((s21_decimal_lazy *)lazy)->mantissa == NULL);
}

int s21_lazy_ptr_is_valid(const void *lazy) {
  return !(((s21_decimal_lazy *)lazy) == NULL ||
           ((s21_decimal_lazy *)lazy)->mantissa == NULL);
}