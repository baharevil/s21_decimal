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
  s21_decimal five_dec = {{0x5, 0x0, 0x0, 0x0}};
  s21_decimal two_dec = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal one_dec = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal_lazy unit, fractional, tmp, five, two, one;

  s21_lazy_init(&five, &five_dec);
  s21_lazy_init(&two, &two_dec);
  s21_lazy_init(&one, &one_dec);
  s21_lazy_init(&unit, NULL);  
  s21_lazy_init(&fractional, NULL);
  s21_lazy_init(&tmp, NULL);

  error |= (value == NULL || value->mantissa == NULL);

  if (!error) {
    if (value->exponent > 0) {
      error |= s21_truncate_lazy(value, &unit);
      error |= s21_lazy_to_lazy_cp(value, &tmp);
      error |= s21_lazy_normalization(&tmp, 1);
      error |= s21_sub_lazy(&tmp, &unit, &fractional);
      s21_lazy_destroy(&tmp);
      s21_lazy_init(&tmp, NULL);
      if (!s21_is_null_lazy(&unit)) {
        if (s21_is_equal_lazy(&fractional, &five) != -1) {
          error |= s21_div_lazy(&unit, &two, &tmp);
          if (tmp.exponent) error |= s21_add_lazy(&unit, &one, result);
        }
      }
      if (!result->exponent) error |= s21_lazy_to_lazy_cp(&unit, result);
    } else error |= s21_lazy_to_lazy_cp(value, result);
  if (value->sign > 0) result->sign = value->sign;
  }
      s21_lazy_destroy(&five);
      s21_lazy_destroy(&two);
      s21_lazy_destroy(&one);
      s21_lazy_destroy(&unit);
      s21_lazy_destroy(&fractional);
  return error;
}