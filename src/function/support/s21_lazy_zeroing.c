#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Зануление s21_decimal_lazy.

  Функция обнуления числа s21_decimal_lazy

  @param[in] *lazy Адрес значения
  @param[in] size размер мантиссы
  @return Код ошибки: 0 - OK, 1 - ERROR
*/
uint8_t s21_lazy_zeroing(s21_decimal_lazy *lazy, uint16_t size) {
  uint8_t *temp = NULL;
  if (size > 0) temp = realloc(lazy->mantissa, size);
  if (temp) {
    lazy->mantissa = temp;
    lazy->size = size;
    memset(lazy->mantissa, 0, size);
  }
  return (temp == NULL);
}