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
    printf("%hhu ", *(x->mantissa + size));
    size++;
  }
  printf(" exp: %u\n", x->exponent);
}

int main() {
  // s21_decimal value_1 = {{{0x00000111, 0x00000000, 0x00000000}},
  // {0x801c0000}};
  s21_decimal value_1 = {{0x0000001a, 0x00000000, 0x00000000, 0x00090000}};
  // s21_decimal value_2 = {{{0, 0xfffffff, 0xabcdef}}, {0}};
  // s21_decimal result = {0};

  // s21_decimal_lazy x  = {0};
  // s21_decimal_lazy y  = {0};
  // s21_search_msb(&value_1);
  s21_decimal_lazy result = {0};
  s21_dec_to_lazy_cp(&value_1, &result);
  // s21_lazy_to_lazy_cp(&x, &result);

  s21_decimal_lazy_print(&result);
  s21_lazy_normalization(&result, 12);
  s21_decimal_lazy_print(&result);
  // free (x.mantissa);
  // free (y.value);
  free(result.mantissa);

  return 0;
}