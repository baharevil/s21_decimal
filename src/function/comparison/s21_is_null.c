#include "s21_decimal.h"

/*!
  @ingroup ComparisonOperators Операторы сравнение
  @brief decimal == 0

  @param[in] *decimal Сравниваемое значения
  @return Код ошибки: 0 - FALSE, 1 - TRUE
*/
uint8_t s21_is_null(s21_decimal *decimal) {
  return (s21_search_msb(decimal) == 0);
}