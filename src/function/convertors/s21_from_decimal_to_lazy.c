#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование s21_decimal в s21_decimal_lazy

  @param[in] src Указатель на s21_decimal
  @param[in] *dst Указатель на s21_decimal_lazy
  @return 0 - ок, 1 - ошибка
*/
uint8_t s21_from_decimal_to_lazy(s21_decimal *src, s21_decimal_lazy *dest) {
  uint8_t result = 0;

  result = (!src || !dest);

  if (!result) {
    uint8_t *temp = NULL;
    uint16_t size = s21_search_msb(src);

    // size не может быть == 0 если мантисса == 0
    // Для хранения пустого s21_decimal нужен 1 байт содержащий 0
    if (!size) size = 1;

    temp = realloc(dest->mantissa, sizeof(uint8_t) * size);
    result = (temp == NULL);

    if (temp != NULL) {
      dest->sign = src->exponent.bits.sign;
      dest->exponent = src->exponent.bits.exponent;
      dest->size = size;
      dest->mantissa = temp;
      memcpy(dest->mantissa, src->mantissa.bytes, dest->size);
    }
  }

  return result;
}