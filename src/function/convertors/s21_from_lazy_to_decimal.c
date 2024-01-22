#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/// @todo Если exp > 28 ---> Нормализация

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование s21_decimal_lazy в s21_decimal

  @param[in] src Указатель на s21_decimal_lazy
  @param[in] *dst Указатель на s21_decimal
  @return 0 - ок, 1 - ошибка
*/
uint8_t s21_from_lazy_to_decimal(s21_decimal_lazy *src, s21_decimal *dest) {
  uint8_t result = 0;

  result = (!src || !dest || !src->mantissa);

  if (!result) {
    uint8_t dec_size = sizeof(dest->mantissa.bytes);
    uint8_t size =
        src->size * (src->size <= dec_size) + dec_size * (src->size > dec_size);

    dest->exponent.bits.sign = src->sign;
    dest->exponent.bits.exponent = src->exponent;
    result = (memcpy(dest->mantissa.bytes, src->mantissa + src->size - size,
                     size) == NULL);
    
    if (!result && size != dec_size)
      memset(dest->mantissa.bytes + size, 0, dec_size - size);                      
  }
  return result;
}