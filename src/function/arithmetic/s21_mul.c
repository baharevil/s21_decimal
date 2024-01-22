#include <stdlib.h>

#include "s21_decimal.h"

/// @todo добавить коды ошибок

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция умножения двух decimal

  Данная функция является оберткой над функцией s21_mul_lazy()

  @param[in] *value_1,*value_2 Умножаемые значения
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - inf, 2 - min_inf
*/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_decimal_lazy lazy1, lazy2, res;

  s21_lazy_init(&lazy1, &value_1);
  s21_lazy_init(&lazy2, &value_2);
  s21_lazy_init(&res, NULL);

  // s21_from_decimal_to_lazy(&value_1, &lazy1);
  // s21_from_decimal_to_lazy(&value_2, &lazy2);

  error = s21_mul_lazy(&lazy1, &lazy2, &res);

  s21_from_lazy_to_decimal(&res, result);

  if (lazy1.mantissa) free(lazy1.mantissa);
  if (lazy2.mantissa) free(lazy2.mantissa);
  if (res.mantissa) free(res.mantissa);

  return error;
}