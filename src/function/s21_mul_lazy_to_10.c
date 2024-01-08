#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

uint8_t s21_mul_lazy_to_10(s21_decimal_lazy *lazy) {
  uint8_t result = 0, carry = 0;
  uint16_t count = 0, tmp = 0;

  while (count < lazy->size) {
    tmp = (uint16_t)lazy->mantissa[count] * 10 + carry;
    lazy->mantissa[count] = (uint8_t)tmp;
    carry = tmp >> 8;
    count++;
  }

  if (carry) {
    lazy->size++;
    uint8_t *temp = realloc(lazy->mantissa, lazy->size);
    if (temp) {
      lazy->mantissa = temp;
      lazy->mantissa[lazy->size - 1] = carry;
    } else
      result = 1;
  }

  return result;
}