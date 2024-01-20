#include <stdint.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Сравнение двух участков памяти.

  Функция сравнения бит со старших к младшим.
  Работает приближено к memcmp(), но реверсивно.

  @param[in] *s1,*s2 const void
  @param[in] size объем памяти
  @return 1: s1 > s2, -1: s1 < s2, 0: s1 == s2
  @warning Если size == 0, проверит 12 байт
  @warning Работает только при одинаковых размерах участков памяти
*/
int s21_memrevcmp(const void *s1, const void *s2, uint16_t size) {
  int result = 0;
  const uint8_t *s1_ptr = s1;
  const uint8_t *s2_ptr = s2;

  if (size == 0) size = 12;

  while (size > 0 && !result) {
    if (*(s1_ptr + size - 1) > *(s2_ptr + size - 1))
      result = 1;
    else if (*(s1_ptr + size - 1) < *(s2_ptr + size - 1))
      result = -1;
    size--;
  }
  return result;
}