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
  s21_decimal value_1 = {{0x0000ffff, 0x00000000, 0x0000, 0x00000000}};
  s21_decimal value_2 = {{0x0000ffff, 0x0000, 0x00000000, 0x00000000}};
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

  return 0;
}