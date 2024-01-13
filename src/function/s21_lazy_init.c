#include "s21_decimal.h"

uint8_t s21_lazy_init(s21_decimal_lazy *lazy) {
  return s21_lazy_zeroing(lazy, 1);
}