#include <stdint.h>
#include <stdlib.h>

#include "s21_decimal.h"

uint8_t s21_div_lazy_to_10(s21_decimal_lazy *lazy) {
  uint8_t result = 0;  //, carry = 0;
  uint16_t count = 0;
  uint16_t *tmp = NULL;

  // Грязно. Тащу по половине байта, при этом выхожу за границу мантиссы.
  // Переделать.
  while (count < lazy->size) {
    tmp = (uint16_t *)(lazy->mantissa + count);
    *(lazy->mantissa + count) = *tmp / 16;
    count++;
  }

  // Уменьшаем экспоненту на 1, снаружи этого делать не надо
  if (!result) lazy->exponent -= (lazy->exponent > 0);

  return result;
}