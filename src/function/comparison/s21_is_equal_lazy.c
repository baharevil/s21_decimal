#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup ComparisonOperators Операторы сравнение
  @brief value_1 == value_2

  @param[in] *value_1,*value_2 Сравниваемые значения s21_decimal_lazy
  @return Код ошибки: 0 - FALSE, 1 - TRUE
*/
int s21_is_equal_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2) {
  int result;
  uint8_t exp;
  uint16_t size;

  if (value_1->sign == value_2->sign) {
    exp = value_1->exponent;
    if (value_1->exponent < value_2->exponent) {
      exp = value_2->exponent;
    }

    s21_lazy_normalization(value_1, exp);
    s21_lazy_normalization(value_2, exp);

    if (value_1->size > value_2->size) {
      size = value_1->size;
      s21_lazy_resize(value_2, size);
    } else if (value_1->size < value_2->size) {
      size = value_2->size;
      s21_lazy_resize(value_1, size);
    } else if (value_1->size == value_2->size) {
      size = value_1->size;
    }

    result = s21_memrevcmp(value_1->mantissa, value_2->mantissa, size);

    if (value_1->sign && value_2->sign) {
      result = result * -1;
    }

  } else if (value_1->sign < value_2->sign) {
    result = 1;
  } else {
    result = -1;
  }
  return result;
}
