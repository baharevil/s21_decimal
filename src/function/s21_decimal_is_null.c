#include "s21_decimal.h"

uint8_t s21_decimal_is_null(s21_decimal *decimal) {
  return (s21_search_msb(decimal) == 0);
}