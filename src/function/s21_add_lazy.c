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

int s21_add_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;

  uint16_t size = (value_1->size > value_2->size) * value_1->size +
                  (value_1->size <= value_2->size) * value_2->size;

  if (result->size < size) {
    result->mantissa = realloc(result->mantissa, sizeof(uint8_t) * size);
    result->size = size;
  }

  uint16_t res = 0, carry = 0;
  uint8_t count = 0, v1 = 0, v2 = 0;

  while (count < size) {
    if (value_1->size >= count)
      v1 = *(value_1->mantissa + count);
    if (value_2->size >= count)
      v2 = *(value_2->mantissa + count);

    res = v1 + v2 + carry;
    *(result->mantissa + count) = (uint8_t)res;
    carry = res >> 8;
    count++;
    v1 = v2 = 0;
  }

  // Если остался перенос, доаллоцируем себе массив
  if (carry) {
    result->size++;
    uint8_t *temp = realloc(result->mantissa, result->size);
    if (temp) {
      result->mantissa = temp;
      result->mantissa[result->size - 1] = carry;
    } else
      error = 1;
  }

  return error;
}
