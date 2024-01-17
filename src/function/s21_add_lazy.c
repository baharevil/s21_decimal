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

// Работает только при равных размерах
uint16_t s21_add_uint8_t(uint8_t *v1, uint8_t *v2, uint8_t *result,
                         uint8_t size) {
  uint8_t count = 0;
  uint16_t res = 0, carry = 0;

  while (count < size) {
    res = *(v1 + count) + *(v2 + count) + carry;
    *(result + count) = (uint8_t)res;
    carry = res >> sizeof(uint8_t) * CHAR_BIT;
    count++;
  }

  return carry;
}

// TODO: коды ошибок
int s21_add_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;

  uint16_t size = (value_1->size > value_2->size) * value_1->size +
                  (value_1->size <= value_2->size) * value_2->size;

  if (result->size != size) s21_lazy_zeroing(result, size);

  // Нормализация значений + запомнаем значение экспоненты
  if (value_1->exponent > value_2->exponent) {
    result->exponent = value_1->exponent;
    s21_lazy_normalization(value_2, value_1->exponent);
  } else {
    result->exponent = value_2->exponent;
    s21_lazy_normalization(value_1, value_2->exponent);
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
    if (s21_lazy_resize(result, result->size + 1) == 0) {
      result->mantissa[result->size - 1] = carry;
    } else
      error = 1;
  }

  return error;
}
