#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_decimal_lazy_print(s21_decimal_lazy* x) {
  uint16_t size = 0;
  while (size < x->size) {
    // printf("%hhu ", *(x->mantissa + size));
    printf("%hhx ", *(x->mantissa + size));
    size++;
  }
  printf(" exp: %u\n", x->exponent);
}

int main() {
  s21_decimal value_1 = {{0x00000002, 0x00000002, 0x1, 0x00000000}};
  s21_decimal value_2 = {{0x00000052, 0x00000002, 0x1, 0x00000000}};
  value_1.exponent.bits.sign = 0x0;
  value_2.exponent.bits.sign = 0x0;
  value_1.exponent.bits.exponent = 14;
  value_2.exponent.bits.exponent = 14;

  // s21_decimal result = {0};

  s21_decimal_lazy x = {0};
  s21_decimal_lazy y = {0};
  s21_decimal_lazy result = {0};
  s21_dec_to_lazy_cp(&value_1, &x);
  s21_dec_to_lazy_cp(&value_2, &y);
  // s21_lazy_to_lazy_cp(&x, &result);

  // s21_decimal_lazy_print(&result);
  // s21_lazy_normalization(&result, 12);
  // s21_add_lazy(&x, &y, &result);
  s21_mul_lazy(&x, &y, &result);
  s21_decimal_lazy_print(&x);
  s21_decimal_lazy_print(&y);
  s21_decimal_lazy_print(&result);
  free(x.mantissa);
  free(y.mantissa);
  free(result.mantissa);

  printf("Equal?: %d\n", s21_lazy_is_equal(&value_1, &value_2));
  printf("less?: %d\n", s21_is_less(value_1, value_2));
  printf("less or equal?: %d\n", s21_is_less_or_equal(value_1, value_2));
  printf("greater?: %d\n", s21_is_greater(value_1, value_2));
  printf("greater or equal?: %d\n", s21_is_greater_or_equal(value_1, value_2));
  printf("equal?: %d\n", s21_is_equal(value_1, value_2));
  printf("not equal?: %d\n", s21_is_not_equal(value_1, value_2));

  return 0;
}