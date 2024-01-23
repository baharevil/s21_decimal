#include "s21_decimal.h"

/*!
  @ingroup ComparisonOperators Операторы сравнение
  @brief value_1 == value_2

  @param[in] *value_1,*value_2 Сравниваемые значения
  @return
  -1: value_1 < value_2,
  0: value_1 == value_2
  1: value_1 > value_2,
*/
int s21_is_equal_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2) {
  int result = 0;

  if (value_1->sign == value_2->sign) {
    s21_decimal_lazy lvalue = {0}, rvalue = {0};
    result |= s21_lazy_to_lazy_cp(value_1, &lvalue);
    result |= s21_lazy_to_lazy_cp(value_2, &rvalue);

    int8_t is_normal = s21_is_normal_lazy(&lvalue, &rvalue);

    if (is_normal == 0) {
      s21_lazy_normalize_greater(&lvalue, &rvalue);
      s21_lazy_upsize(&lvalue, &rvalue);
    }

    else if (is_normal == 1) {
      s21_lazy_upsize(&lvalue, &rvalue);
    }

    result = s21_memrevcmp(lvalue.mantissa, rvalue.mantissa, lvalue.size);

    if (value_1->sign && value_2->sign) result *= -1;

    s21_lazy_destroy(&lvalue);
    s21_lazy_destroy(&rvalue);
  } else
    result = (value_2->sign) - (value_1->sign);

  return result;
}
