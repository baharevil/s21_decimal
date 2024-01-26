#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Нормализация к меньшей экспоненте

  @param *value_1,*value_2 Указатели на значения
  @return 0 - OK, 1 - ошибка нормализации
*/
uint8_t s21_lazy_normalize_less(s21_decimal_lazy *value_1,
                                s21_decimal_lazy *value_2) {
  uint8_t error = 0, exp = 0;
  s21_decimal_lazy *ptr = NULL;

  exp = (value_1->exponent > value_2->exponent) * value_2->exponent +
        (value_1->exponent <= value_2->exponent) * value_1->exponent;

  ptr = (s21_decimal_lazy *)((value_1->exponent > value_2->exponent) *
                                 (uintptr_t)value_1 +
                             (value_1->exponent < value_2->exponent) *
                                 (uintptr_t)value_2);

  if (ptr != NULL) error |= s21_lazy_normalization(ptr, exp);

  return error;
}