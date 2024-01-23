#include "s21_decimal.h"

/*!
  @ingroup ComparisonOperators Операторы сравнение
  @brief lazy == 0

  @param[in] *lazy Сравниваемое значения
  @return 0 - FALSE, 1 - TRUE
*/
uint8_t s21_is_null_lazy(s21_decimal_lazy *lazy) {
  uint8_t result = 0;
  s21_decimal null = {{0, 0, 0, 0}};
  s21_decimal_lazy null_lazy = {0};

  s21_lazy_init(&null_lazy, &null);
  result = (s21_is_equal_lazy(lazy, &null_lazy) == 0);
  s21_lazy_destroy(&null_lazy);

  return result;
}