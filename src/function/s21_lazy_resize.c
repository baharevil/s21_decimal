#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

uint8_t s21_lazy_resize(s21_decimal_lazy *lazy, uint16_t new_size) {
  uint8_t result = 0;
  int32_t diff = new_size - lazy->size;

  if (lazy == NULL || lazy->mantissa == NULL || new_size < 1 ||
      new_size > UINT16_MAX - 1)
    result = 1;

  if (!result) {
    uint8_t *temp = realloc(lazy->mantissa, sizeof(uint8_t) * new_size);
    result = (temp == NULL);
    if (!result) {
      lazy->mantissa = temp;
      if (diff > 0)
        memset((lazy->mantissa + lazy->size), 0, diff);
      lazy->size = new_size;
    }
      
  }

  return result;
}