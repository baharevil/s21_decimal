#include <stddef.h>

#include "s21_decimal.h"

uint8_t s21_lazy_init(s21_decimal_lazy *lazy) {
  uint8_t error = 0;
  error |= (lazy == NULL);

  if (!error) {
    lazy->sign = 0;
    lazy->exponent = 0;
    lazy->mantissa = NULL;
    error |= s21_lazy_zeroing(lazy, 1);
  }

  return error;
}