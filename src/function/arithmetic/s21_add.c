#include <stdlib.h>

#include "s21_decimal.h"

/// @todo Добавить коды ошибок

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция сложения двух decimal.

  Данная функция является оберткой над функцией s21_add_lazy()

  @param[in] *value_1,*value_2 Cкладываемые числа
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - inf, 2 - min_inf
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_decimal_lazy lazy1, lazy2, res;

  s21_lazy_init(&lazy1, &value_1);
  s21_lazy_init(&lazy2, &value_2);
  s21_lazy_init(&res, NULL);

  error = s21_add_lazy(&lazy1, &lazy2, &res);

  // Функция обратного копирования s21_from_lazy_to_decomal()
  // копирует только 12 байт или менее, в зависимости от размера src->size
  s21_from_lazy_to_decomal(&res, result);

  if (lazy1.mantissa) free(lazy1.mantissa);
  if (lazy2.mantissa) free(lazy2.mantissa);
  if (res.mantissa) free(res.mantissa);

  return error;
}
