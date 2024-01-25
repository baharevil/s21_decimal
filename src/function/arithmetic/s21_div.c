#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция деления двух decimal.

  Данная функция является оберткой над функцией s21_div_lazy()

  @param[in] *value_1,*value_2 Делисое и делитель
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - inf, 2 - min_inf, 3 - деление на 0
*/
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_decimal_lazy lazy1, lazy2, res;

  s21_lazy_init(&lazy1, &value_1);
  s21_lazy_init(&lazy2, &value_2);
  s21_lazy_init(&res, NULL);

  error = s21_div_lazy(&lazy1, &lazy2, &res);
  if (!error) s21_from_lazy_to_decimal(&res, result);

  s21_lazy_destroy(&lazy1);
  s21_lazy_destroy(&lazy2);
  s21_lazy_destroy(&res);

  return error;
}