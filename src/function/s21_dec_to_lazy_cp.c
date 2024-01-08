#include "s21_decimal.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t s21_dec_to_lazy_cp(s21_decimal *src, s21_decimal_lazy *dest) {
    uint8_t result = 0;

    if(!src || !dest)
        result = 1;

    if (!result) {
        dest->sign = src->exponent.bits.sign;
        dest->exponent = src->exponent.bits.exponent;
        dest->size = s21_search_msb(src);
        dest->mantissa = realloc(dest->mantissa, sizeof(uint8_t) * dest->size);
        if(dest->mantissa)
            memcpy(dest->mantissa, src->mantissa.bytes, dest->size);
        else
            result = 1;
    }

    return result;
}