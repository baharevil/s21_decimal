#include <stdlib.h>

#include "s21_decimal.h"

uint8_t s21_lazy_resize(s21_decimal_lazy **lazy) {
  uint8_t result = 0;
  if (*lazy && (*lazy)->mantissa) {
    uint8_t *temp = realloc((*lazy)->mantissa, sizeof(uint8_t) * (*lazy)->size);
    if (temp)
      (*lazy)->mantissa = temp;
    else
      result = 1;
  }
  return result;
}