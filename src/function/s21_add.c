#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"

/*
    Арифметические операторы. Сумма.
    Функции возвращают код ошибки:

    0 - OK
    1 - число слишком велико или равно бесконечности
    2 - число слишком мало или равно отрицательной бесконечности
    3 - деление на 0
*/

uint16_t s21_add_uint8_t(uint8_t x, uint8_t y) {
  uint16_t add = y;
  uint16_t carry = 0;
  uint16_t result = x;

  while (add) {
    carry = result & add;
    result = result ^ add;
    add = carry << 1;
  }
  return result;
}

int s21_add_lazy(s21_decimal_lazy value_1, s21_decimal_lazy value_2,
                 s21_decimal_lazy *result) {
  int error = 0;

  uint16_t size = (value_1.size > value_2.size) * value_1.size +
                  (value_1.size <= value_2.size) * value_2.size;

  if (result->size < size) {
    result->mantissa = realloc(result->mantissa, sizeof(uint8_t) * size);
    result->size = size;
  }

  uint16_t carry = 0;
  uint16_t res = 0;

  while (size--) {
    value_1.size =
        (value_1.size > 0) * value_1.size - 1 + (value_1.size == 0) * 0;
    value_2.size =
        (value_2.size > 0) * value_2.size - 1 + (value_2.size == 0) * 0;
    res = s21_add_uint8_t(*(value_1.mantissa + value_1.size),
                          *(value_2.mantissa + value_2.size)) +
          carry;
    *(result->mantissa + size) = (uint8_t)res;
    carry = res >> 8;
  }

  return error;
}
