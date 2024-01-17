#include <stdlib.h>

#include "s21_decimal.h"

uint8_t s21_lazy_resize(s21_decimal_lazy **lazy) {
  uint8_t result = 0;

  if (*lazy == NULL || (*lazy)->mantissa == NULL || (*lazy)->size < 1 ||
      (*lazy)->size > UINT16_MAX - 1)
    result = 1;

  if (!result) {
    uint8_t *temp = realloc((*lazy)->mantissa, sizeof(uint8_t) * (*lazy)->size);
    result = (temp == NULL);
    if (!result) (*lazy)->mantissa = temp;
  }

  return result;
}