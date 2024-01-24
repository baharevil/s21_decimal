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

void s21_decimal_print(s21_decimal *x) {
  uint8_t size = 0;
  while (size < sizeof(x->mantissa.bytes)) {
    printf("%hhx ", *(x->mantissa.bytes + size));
    size++;
  }
  printf(" exp: %u", x->exponent.bits.exponent);
  printf(" sign: %u\n", x->exponent.bits.sign);
}

int main() {
  s21_decimal value_1 = {{0x00010000, 0x0, 0x0, 0x80000000}};
  s21_decimal value_2 = {{0x00000002, 0x0, 0x0, 0x80000000}};
  s21_decimal dec_result = {0};

  // Найди отличия в результатах:
  //----------------- Ver1 -------------------

  s21_decimal_lazy lazy_1 = {0}, lazy_2 = {0}, lazy_res = {0};
  s21_lazy_init(&lazy_1, &value_1);
  s21_lazy_init(&lazy_2, &value_2);
  s21_lazy_init(&lazy_res, &dec_result);

  s21_div_lazy(&lazy_1, &lazy_2, &lazy_res);

  printf("div ver_1: ");
  s21_decimal_lazy_print(&lazy_res);

  s21_lazy_destroy(&lazy_1);
  s21_lazy_destroy(&lazy_2);
  s21_lazy_destroy(&lazy_res);
  //----------------- Ver2 -------------------
  // s21_decimal *lvalue = NULL, *rvalue = NULL;
  // s21_decimal null = {0};

  /// @bug неправельный результат при выражени -5 - 2
  /*
    В даном случае, по текущей версии, получается что
    lvalue = 2, rvalue = -5, из-за чего постоянно переносится carry,
    который не равен 0.
  */

  // if (s21_is_less_or_equal(value_1, null) &&
  //     s21_is_less_or_equal(value_2, null)) {
  //   value_1.exponent.bits.sign = 0;
  //   value_2.exponent.bits.sign = 0;
  //   dec_result.exponent.bits.sign = 1;
  // }

  // if (s21_is_less_or_equal(value_1, value_2)) {
  //   lvalue = &value_2;
  //   rvalue = &value_1;
  //   dec_result.exponent.bits.sign = 1;
  // }

  // uint8_t carry = 0;
  // uint16_t res = 0;
  // for (size_t i = 0; i < (size_t)sizeof(s21_uint96_t); i++) {
  //   res = lvalue->mantissa.bytes[i] - rvalue->mantissa.bytes[i] - carry;
  //   dec_result.mantissa.bytes[i] = (uint8_t)res;
  //   carry = ((res >> sizeof(uint8_t) * CHAR_BIT) > 0);
  // }
  // //------------------------------------------

  // printf("sub ver_2: ");
  // s21_decimal_print(&dec_result);

  return 0;
}