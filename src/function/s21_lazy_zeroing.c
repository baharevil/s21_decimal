#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

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