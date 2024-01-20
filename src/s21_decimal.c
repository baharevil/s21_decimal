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
  s21_decimal value_1 = {{0xf, 0xfff, 0xabcde, 0x8050000}};
  s21_decimal value_2 = {{0x0, 0x1, 0xfff, 0x00000000}};
  s21_decimal dec_result = {0};

  // Найди отличия в результатах:
  //----------------- Ver1 -------------------
  s21_sub(value_1, value_2, &dec_result);
  s21_decimal_print(&dec_result);

  //----------------- Ver2 -------------------
  // s21_decimal *lvalue = NULL, *rvalue = NULL;

  // if (s21_is_less_or_equal(value_1, value_2)) {
  //   lvalue = &value_2;
  //   rvalue = &value_1;
  //   dec_result.exponent.bits.sign = 1;
  // } else {
  //   lvalue = &value_1;
  //   rvalue = &value_2;
  // }

  // uint8_t carry = 0;
  // uint16_t res = 0;
  // for (size_t i = 0; i < (size_t)sizeof(s21_uint96_t); i++) {
  //   res = lvalue->mantissa.bytes[i] - rvalue->mantissa.bytes[i] - carry;
  //   dec_result.mantissa.bytes[i] = (uint8_t)res;
  //   carry = ((res >> sizeof(uint8_t) * CHAR_BIT) > 0);
  // }
  //------------------------------------------

  s21_decimal_print(&dec_result);

  // s21_decimal_lazy x = {0};
  // s21_decimal_lazy y = {0};
  // s21_decimal_lazy result = {0};
  // s21_dec_to_lazy_cp(&value_1, &x);
  // s21_dec_to_lazy_cp(&value_2, &y);
  // // s21_lazy_to_lazy_cp(&x, &result);

  // // s21_decimal_lazy_print(&result);
  // // s21_lazy_normalization(&result, 12);
  // // s21_add_lazy(&x, &y, &result);
  // printf("x: ");
  // s21_decimal_lazy_print(&x);
  // printf("y: ");
  // s21_decimal_lazy_print(&y);

  // s21_sub_lazy(&x, &y, &result);

  // printf("result: ");
  // s21_decimal_lazy_print(&result);

  // s21_lazy_to_dec(&result, &dec_result);

  // printf("dec_result: ");
  // s21_decimal_print(&dec_result);

  // free(x.mantissa);
  // free(y.mantissa);
  // free(result.mantissa);
  // s21_decimal_lazy value_1_l = s21_decimal_to_lazy(value_1);
  // s21_decimal_lazy value_2_l = s21_decimal_to_lazy(value_2);

  // s21_decimal_print(&value_1);
  // s21_decimal_print(&value_2);

  // printf("Equal?: %d\n", s21_equal_lazy(&value_1_l, &value_2_l));
  // printf("less?: %d\n", s21_is_less(value_1, value_2));
  // printf("less or equal?: %d\n", s21_is_less_or_equal(value_1, value_2));
  // printf("greater?: %d\n", s21_is_greater(value_1, value_2));
  // printf("greater or equal?: %d\n", s21_is_greater_or_equal(value_1,
  // value_2)); printf("equal?: %d\n", s21_is_equal(value_1, value_2));
  // printf("not equal?: %d\n", s21_is_not_equal(value_1, value_2));

  return 0;
}