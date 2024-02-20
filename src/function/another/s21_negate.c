#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup AnotherFunction Другие функции
  @brief Возвращает результат умножения указанного Decimal на -1.

  @param[in] value Указатели на массивы
  @param[in] result Указатель на результат
  @return 0 - OK 1 - ошибка вычисления
*/
int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = ok;

  error |= !s21_decimal_ptr_is_valid(&value);
  error |= (result == NULL);

  if (!error) {
    s21_decimal_lazy lazy_result;
    if (!error) error |= s21_lazy_init(&lazy_result, &value);
    if (!error) error |= s21_negate_lazy(&lazy_result);
    if (!error) error |= s21_from_lazy_to_decimal(&lazy_result, result);
    s21_lazy_destroy(&lazy_result);
  }

  return error;
}