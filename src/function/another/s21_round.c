#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup AnotherFunction Другие функции
  @brief Округляет Decimal до ближайшего целого числа.

  Банковское округление

  @param[in] value Указатели на массивы
  @param[in] result Указатель на результат
  @return 0 - OK 1 - ошибка вычисления
*/

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = ok;

  error |= (result == NULL);

  if (!error) {
    s21_decimal_lazy lazy_value, lazy_result;
    if (!error) {
      error |= s21_lazy_init(&lazy_value, &value);
      error |= s21_lazy_init(&lazy_result, result);
    }
    if (!error) error |= s21_round_lazy(&lazy_value, &lazy_result);
    if (!error) error |= s21_from_lazy_to_decimal(&lazy_result, result);
    s21_lazy_destroy(&lazy_result);
  }
  return error;
}