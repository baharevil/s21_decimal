#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Копирование s21_decimal_lazy в s21_decimal_lazy

  @param[in] src Указатель на s21_decimal_lazy
  @param[in] *dst Указатель на s21_decimal_lazy
  @return 0 - ок, 1 - ошибка
*/
uint8_t s21_lazy_to_lazy_cp(s21_decimal_lazy *src, s21_decimal_lazy *dest) {
  uint8_t result = 0;

  result = (!src || !dest);

  if (!result) {
    if (dest->size != src->size) {
      uint8_t *temp = realloc(dest->mantissa, sizeof(uint8_t) * src->size);
      result = (temp == NULL);
      if (!result) {
        dest->mantissa = temp;
        dest->size = src->size;
      }
    }
    dest->sign = src->sign;
    dest->exponent = src->exponent;
    memcpy(dest->mantissa, src->mantissa, dest->size);
  }

  return result;
}