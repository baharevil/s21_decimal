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

  if (result->size != size) {
    s21_lazy_zeroing(result, size);
  }

  uint16_t res = 0, carry = 0;
  uint8_t count = 0, v1 = 0, v2 = 0;

  while (count < size) {
    if (count <= value_1->size) v1 = *(value_1->mantissa + count);
    if (count <= value_2->size) v2 = *(value_2->mantissa + count);

    res = v1 + v2 + carry;
    *(result->mantissa + count) = (uint8_t)res;
    carry = res >> sizeof(uint8_t) * CHAR_BIT;
    count++;
    v1 = v2 = 0;
  }

  // Если остался перенос, доаллоцируем себе массив
  if (carry) {
    result->size++;
    if (s21_lazy_resize(&result) == 0) {
      result->mantissa[result->size - 1] = carry;
    } else
      error = 1;
  }

  return error;
}
