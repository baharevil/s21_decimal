#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup ComparisonOperators Операторы сравнение
  @brief value_1 == value_2

  @param[in] value_1,value_2 Сравниваемые значения s21_decimal
  @return Код ошибки: 0 - FALSE, 1 - TRUE
*/
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;

  s21_decimal_lazy value_l_1;
  s21_decimal_lazy value_l_2;  

  s21_lazy_init(&value_l_1);
  s21_lazy_init(&value_l_2);

  s21_from_decimal_to_lazy(&value_1, &value_l_1);
  s21_from_decimal_to_lazy(&value_2, &value_l_2);

  if (s21_is_equal_lazy(&value_l_1, &value_l_2) == 0) result = 1;

  if (value_l_1.mantissa != NULL) free(value_l_1.mantissa);
  if (value_l_2.mantissa != NULL) free(value_l_2.mantissa);

  return result;
}