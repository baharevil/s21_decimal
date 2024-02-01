#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция деления s21_decimal_lazy на мантиссы и
  эксоненты на 10.

  @param[in] *lazy Указатели на значение
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
uint8_t s21_div_lazy_to_10(s21_decimal_lazy *lazy) {
  uint8_t error = 0;
  s21_decimal ten = {{0xa, 0x0, 0x0, 0x0}};

  s21_decimal_lazy ten_lazy = {0};
  s21_decimal_lazy result = {0};

  error |= !s21_lazy_ptr_is_valid(lazy);

  if (!error) {
    error |= s21_lazy_init(&ten_lazy, &ten);
    error |= s21_lazy_init(&result, NULL);
  }

  if (!error) error = s21_mod_lazy(lazy, &ten_lazy, &result);

  if (!error) {
    result.exponent = lazy->exponent - 1;
    error |= s21_lazy_to_lazy_cp(&result, lazy);
  }

  s21_lazy_destroy(&ten_lazy);
  s21_lazy_destroy(&result);

  return error;
}