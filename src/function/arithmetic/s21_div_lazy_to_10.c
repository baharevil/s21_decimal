#include <stddef.h>

#include "s21_decimal.h"

/// @todo Сырое - тесты

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция деления s21_decimal_lazy на мантиссы и
  эксоненты на 10.

  @param[in] *lazy Указатели на значение
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
uint8_t s21_div_lazy_to_10(s21_decimal_lazy *lazy) {
  uint8_t error = 0;

  error = (lazy == NULL || lazy->mantissa == NULL);

  if (!error) {
    s21_decimal ten = {{0xa, 0x0, 0x0, 0x00010000}};
    s21_decimal_lazy ten_lazy = {0}, result = {0};

    error |= s21_lazy_init(&ten_lazy, &ten);
    error |= s21_lazy_init(&result, NULL);
    result.exponent = ten_lazy.exponent = lazy->exponent;

    error |= s21_div_lazy_core(lazy, &ten_lazy, &result);
    result.exponent--;
    error |= s21_lazy_to_lazy_cp(&result, lazy);
    s21_lazy_destroy(&ten_lazy);
    s21_lazy_destroy(&result);
  }

  return error;
}