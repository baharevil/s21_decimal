#include <stdint.h>
#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup ComparisonOperators Операторы сравнение
  @brief Нормализованы ли 2 значения s21_decimal_lazy

  @param[in] *value_1,*value_2 Сравниваемые значения
  @return
    -1 - ошибка
    0 - не нормализованы
    1 - нормализованы
    2 - нормализованы и выровняны по размеру
*/
int8_t s21_is_normal_lazy(s21_decimal_lazy *value_1,
                          s21_decimal_lazy *value_2) {
  int8_t result = 0;

  // Если экспоненты не равны, размеры мы проверять не должны
  if (value_1->exponent == value_2->exponent)
    result = 1 + (value_1->size == value_2->size);

  return result;
}