#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

uint8_t s21_dec_to_lazy_cp(s21_decimal *src, s21_decimal_lazy *dest) {
  uint8_t result = 0;

  result = (!src || !dest);

  if (!result) {
    uint8_t *temp = NULL;
    uint16_t size = s21_search_msb(src);
    
    // size может быть == 0 если мантисса == 0
    if (size != 0){
      temp = realloc(dest->mantissa, sizeof(uint8_t) * size);
      result = (temp == NULL);
    } 

    if (temp != NULL) {
      dest->sign = src->exponent.bits.sign;
      dest->exponent = src->exponent.bits.exponent;
      dest->size = size;
      dest->mantissa = temp;
      memcpy(dest->mantissa, src->mantissa.bytes, dest->size);
    }
  }

  return result;
}