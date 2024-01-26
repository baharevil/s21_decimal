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
  uint8_t error = 0;
  uint16_t size = 0;

  error = (!src || !dest);

  if (!error && dest->size != src->size) {
    size = s21_search_msb_lazy(src);
    size += (size == 0);
    error = s21_lazy_resize(dest, size);
  }

  if (!error) {
    dest->sign = src->sign;
    dest->exponent = src->exponent;
    memcpy(dest->mantissa, src->mantissa, dest->size);
  }

  return error;
}