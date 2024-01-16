#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

// TODO: Добавить проверку на уменьшение экспоненты в случае если она больше 28
uint8_t s21_lazy_to_dec(s21_decimal_lazy *src, s21_decimal *dest) {
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
  }
  return result;
}