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
  s21_decimal five_dec = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal two_dec = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal one_dec = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal_lazy five, two, one;
  s21_decimal_lazy fractional = {0}, tmp = {0};

  error |= (value == NULL || value->mantissa == NULL);

  error |= s21_lazy_init(&five, &five_dec);
  error |= s21_lazy_init(&two, &two_dec);
  error |= s21_lazy_init(&one, &one_dec);
  error |= s21_lazy_init(&fractional, NULL);
  error |= s21_lazy_to_lazy_cp(value, &tmp);

  if (!error && tmp.exponent > 0)
    error |= s21_truncate_lazy(&tmp, result);
  else
    error |= s21_lazy_to_lazy_cp(&tmp, result);

  if (!s21_is_null_lazy(result)) {
    if (!error) error |= s21_lazy_normalization(&tmp, 1);
    if (!error) error |= s21_sub_lazy(&tmp, result, &fractional);
    five.sign = one.sign = value->sign;

    s21_lazy_destroy(&tmp);
    error |= s21_lazy_init(&tmp, NULL);
  }

  if (!error && s21_is_equal_lazy(&fractional, &five) >= 0) {
    error |= s21_div_lazy(result, &two, &tmp);
    if (tmp.exponent) error |= s21_add_lazy(result, &one, result);
  }

  s21_lazy_destroy(&five);
  s21_lazy_destroy(&two);
  s21_lazy_destroy(&one);
  s21_lazy_destroy(&tmp);
  s21_lazy_destroy(&fractional);
  return error;
}