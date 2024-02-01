#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_decimal_lazy_print(s21_decimal_lazy *x) {
  uint16_t size = 0;
  while (size < x->size) {
    // printf("%hhu ", *(x->mantissa + size));
    printf("%hhu ", *(x->mantissa + size));
    size++;
  }
  printf(" exp: %u", x->exponent);
  printf(" sign: %u\n", x->sign);
}

void s21_decimal_print(s21_decimal *x, char *str) {
  printf("\n%s", str);

  uint8_t size = 0;
  while (size < sizeof(x->mantissa.bytes)) {
    printf("%hhx ", *(x->mantissa.bytes + size));
    size++;
  }

  printf(" exp: %u", x->exponent.bits.exponent);
  printf(" sign: %u\n", x->exponent.bits.sign);
}

int main() {
  // s21_decimal value_1 = {{0xff, 0x0, 0x0, 0x0}};
  // value_1.exponent.bits.exponent = 1;
  s21_decimal value_2 = {{39, 0x0, 0x0, 0x80010000}};
  s21_decimal_print(&value_2, "value_2: ");

  s21_decimal dec_result = {0};

  // s21_add(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "add: ");

  // s21_mul(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "mul: ");

  // s21_sub(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "sub: ");

  // s21_div(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "div: ");

  s21_decimal_lazy value_l;
  s21_decimal_lazy value_rounded;

  s21_lazy_init(&value_l, &value_2);
  s21_lazy_init(&value_rounded, NULL);

  s21_round_lazy(&value_l, &value_rounded);
  s21_negate_lazy(&value_rounded);

  // s21_truncate(value_1, &dec_result);

  // s21_decimal_print(&dec_result, "result: ");

  // s21_decimal_lazy_print(&value_rounded);

  s21_from_lazy_to_decimal(&value_rounded, &dec_result);

  s21_decimal_print(&dec_result, "result: ");

  return 0;
}