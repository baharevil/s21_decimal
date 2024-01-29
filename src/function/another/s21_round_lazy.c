#include <stddef.h>
#include <string.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Возвращает округленное до целого число lazy Decimal.
  @param[in] value Указатели на массивы
  @param[in] result Указатель на результат
  @return 0 - OK 1 - ошибка вычисления
*/

uint8_t s21_round_lazy(s21_decimal_lazy *value, s21_decimal_lazy *result) {
  uint8_t error = 0;
  uint8_t number_five = 5;
  uint8_t number_two = 2;
  uint8_t number_one = 1;

  error |= (value == NULL || value->mantissa == NULL || result == NULL ||
            result->mantissa == NULL);

  if (!error) {
    s21_decimal_lazy zero;
    if (value->exponent > 0) {
      s21_decimal_lazy unit, fractional, tmp;
      s21_decimal_lazy five;
      five.mantissa = &number_five;
      s21_decimal_lazy two;
      two.mantissa = &number_two;
      s21_decimal_lazy one;
      one.mantissa = &number_one;
      error |= s21_truncate_lazy(value, &unit);
      error |= s21_lazy_to_lazy_cp(value, &tmp);
      error |= s21_lazy_normalization(&tmp, 1);
      error |= s21_sub_lazy(&tmp, &unit, &fractional);
      s21_lazy_destroy(&tmp);
      error |= s21_lazy_normalization(&fractional, 0);
      if (!s21_is_null_lazy(&unit)) {
        if (s21_is_equal_lazy(&fractional, &five) == 0||1) {
          error |= s21_div_lazy(&unit, &two, &tmp);
          if (!tmp.mantissa) error |= s21_add_lazy(&unit, &one, result);
        } 
      }
      if (!result) error |= s21_lazy_to_lazy_cp(&unit, result);
    } else error |= s21_lazy_to_lazy_cp(&zero, result);
  if (value->sign > 0) result->sign = value->sign;
  }
  return error;
}