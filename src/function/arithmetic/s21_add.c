#include <stdlib.h>

#include "s21_decimal.h"

/// @todo Добавить коды ошибок

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция сложения двух decimal.

  Данная функция является оберткой над функцией s21_add_lazy()

  @param[in] value_1,value_2 Cкладываемые числа
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - inf, 2 - min_inf
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  s21_decimal_lazy lazy1, lazy2, res;

  error |= !s21_decimal_ptr_is_valid(&value_1);
  error |= !s21_decimal_ptr_is_valid(&value_2);
  if (!error) error |= (result == NULL);

  /// @bug заглушка
  /// @todo не забыть убрать
  if (error) return -1;

  if (!error) {
    error |= s21_lazy_init(&lazy1, &value_1);
    error |= s21_lazy_init(&lazy2, &value_2);
    error |= s21_lazy_init(&res, NULL);
  }

  if (!error) error = s21_add_lazy(&lazy1, &lazy2, &res);

  // /// @todo сделать резайз с округлением
  // if (!error && res.size > 12)
  //   error = s21_lazy_normalization(&res, lazy1.exponent);

  // if (!error) error = s21_aritmetic_error(&res);
  if (!error) error = s21_from_lazy_to_decimal(&res, result);

  s21_lazy_destroy(&lazy1);
  s21_lazy_destroy(&lazy2);
  s21_lazy_destroy(&res);

  return error;
}
