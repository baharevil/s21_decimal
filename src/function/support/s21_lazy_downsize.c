#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Выравнивание размеров к меньшему

  @param *value_1,*value_2 Указатели на значения
  @return 0 - OK, 1 - ошибка выравнивнивания
*/
uint8_t s21_lazy_downsize(s21_decimal_lazy *value_1,
                          s21_decimal_lazy *value_2) {
  uint8_t error = 0;
  uint16_t new_size = 0;
  s21_decimal_lazy *ptr = NULL;

  ptr = (s21_decimal_lazy *)((value_1->size > value_2->size) * (uintptr_t)value_1 +
                             (value_1->size < value_2->size) * (uintptr_t)value_2);

  new_size = (value_1->size > value_2->size) * value_2->size +
             (value_1->size <= value_2->size) * value_1->size;

  if (ptr != NULL) error |= s21_lazy_resize(ptr, new_size);

  return error;
}