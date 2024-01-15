#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

uint8_t s21_lazy_to_dec(s21_decimal_lazy *src, s21_decimal *dest) {
  uint8_t result = 0;

  result = (!src || !dest || !src->mantissa);

  if (!result) {
    uint8_t size = src->size * (src->size <= sizeof(dest->mantissa.bytes)) +
                   sizeof(dest->mantissa.bytes) *
                       (src->size > sizeof(dest->mantissa.bytes));
    dest->exponent.bits.sign = src->sign;
    dest->exponent.bits.exponent = src->exponent;
    result = (memcpy(dest->mantissa.bytes, src->mantissa, size) == NULL);
  }
  return result;
}