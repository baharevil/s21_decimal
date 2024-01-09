#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

uint8_t s21_lazy_to_lazy_cp(s21_decimal_lazy *src, s21_decimal_lazy *dest) {
  uint8_t result = 0;

  if (!src || !dest) result = 1;

  if (!result) {
    if (dest->size != src->size) {
      uint8_t *temp = realloc(dest->mantissa, sizeof(uint8_t) * src->size);
      if (temp) {
        dest->sign = src->sign;
        dest->exponent = src->exponent;
        dest->size = src->size;
        dest->mantissa = temp;
        memcpy(dest->mantissa, src->mantissa, dest->size);
      } else
        result = 1;
    }
  }

  return result;
}