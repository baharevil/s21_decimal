#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

int s21_mul_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;
  uint8_t *temp = NULL;
  s21_decimal_lazy tmp = {0}, empty = {0};

  temp = realloc(result->mantissa, value_1->size + value_2->size);
  if (temp != NULL) {
    result->mantissa = temp;
    result->size = value_1->size + value_2->size;
    memset(result->mantissa, 0, result->size);
    error = !!(s21_lazy_to_lazy_cp(result, &tmp) +
               s21_lazy_to_lazy_cp(result, &empty));
  } else
    error = 1;

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
      error = !!(s21_add_lazy(&tmp, result, result) +
                 s21_lazy_to_lazy_cp(&empty, &tmp));
      carry = 0;
    }

    if (tmp.mantissa != NULL) free(tmp.mantissa);
    if (empty.mantissa != NULL) free(empty.mantissa);
  }

  return error;
}