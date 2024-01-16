#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

int s21_mul_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;
  uint16_t result_size = value_1->size + value_2->size;
  s21_decimal_lazy tmp;
  error |= s21_lazy_init(&tmp);

  error |= s21_lazy_zeroing(&tmp, result_size);
  error |= s21_lazy_zeroing(result, result_size);

  if (!error) {
    uint16_t res = 0;
    uint8_t carry = 0;

    for (uint16_t i = 0; i < value_1->size && !error; i++) {
      for (uint16_t j = 0; j < value_2->size && !error; j++) {
        res = (uint16_t)(*(value_1->mantissa + i) * *(value_2->mantissa + j));
        res += carry;
        *(tmp.mantissa + i + j) = (uint8_t)res;

        carry = res >> sizeof(uint8_t) * CHAR_BIT;
        *(tmp.mantissa + i + j + 1) = carry;
      }
      error |= s21_add_lazy(&tmp, result, result);
      error |= s21_lazy_zeroing(&tmp, result_size);
      carry = 0;
    }

    result->exponent = value_1->exponent + value_2->exponent;

    if (tmp.mantissa != NULL) free(tmp.mantissa);
  }

  return error;
}