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
    printf("%hhx ", *(x->mantissa + size));
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
  // s21_decimal value_1 = {{0x00000000, 0x0, 0x2, 0x80000000}};
  // s21_decimal value_2 = {{0x00000001, 0x0, 0x0, 0x80000000}};
  // s21_decimal dec_result = {0};

  // s21_add(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "add: ");

  // s21_mul(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "mul: ");

  // s21_sub(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "sub: ");

  // s21_div(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "div: ");

  float a = 2147483647;
  int b = (int)a;

  printf("INT_MAX:  %d\n", INT32_MAX);

  printf("a:        %f\n", a);
  printf("b:       %d\n", b);

  return 0;
}