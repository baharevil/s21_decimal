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
    s21_decimal_lazy l_ten = {0};

    s21_lazy_init(&l_ten, &ten);
    error = s21_div_lazy(lazy, &l_ten, lazy);
    s21_lazy_destroy(&l_ten);
  }

  return error;
}