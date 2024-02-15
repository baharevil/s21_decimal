#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/// @todo упростить работу с числами

/*!
  @ingroup Support Функции для служебного пользования
  @brief Нормализация s21_decimal_lazy.

  Функция приведения мантиссы числа s21_decimal_lazy к заданной экспоненте.

  @param[in] *lazy Адрес нормализируемого значения
  @param[in] exp Необходимая экспонента
  @return Код ошибки: 0 - OK, 1 - ERROR
*/
uint8_t s21_lazy_normalization(s21_decimal_lazy *lazy, uint8_t exp) {
  uint8_t error = 0;
  s21_decimal ten = {{0xa, 0x0, 0x0, 0x10000}};
  s21_decimal_lazy l_ten = {0};

  s21_decimal_lazy tmp_value = {0};  //, carry = {0};

  // Напраление изменения стпени. Если 1 -> увеличиваем, -1 -> уменьшаем
  int8_t direction = 0, res_exp = 0;

  // Первичная проверка
  error = (lazy == NULL);

  if (!error) {
    direction = (exp > lazy->exponent) - (exp < lazy->exponent);
    res_exp = (direction >= 0) * (exp - lazy->exponent) +
              (direction < 0) * (-exp + lazy->exponent);

    // Инициализация переменных
    error |= s21_lazy_to_lazy_cp(lazy, &tmp_value);
    error |= s21_lazy_init(&l_ten, &ten);
  }

  /*
    Метод расчета домножение мантиссы на 10^|exp - lazy->exponent|

    Подгоняем 10 сначала в геометрической прогрессии,
    потом обыным домножением на 10.
  */
  while (!error && l_ten.exponent * 2 <= res_exp)
    error |= s21_mul_lazy(&l_ten, &l_ten, &l_ten);

  while (!error && l_ten.exponent < res_exp)
    error |= s21_mul_lazy_to_10(&l_ten);

  // если |exp - lazy->exponent| == 0, то нужно вызвать функцию со значением 1
  if (!error && res_exp == 0) error |= s21_div_lazy_to_10(&l_ten);

  // Выбор функции и расчет остатка в случае уменьшения экспоненты вниз
  if (!error) {
    int (*func)(s21_decimal_lazy *, s21_decimal_lazy *, s21_decimal_lazy *) =
        ((int (*)(s21_decimal_lazy *, s21_decimal_lazy *, s21_decimal_lazy *))(
            (direction >= 0) * (uintptr_t)s21_mul_lazy +
            (direction < 0) * (uintptr_t)s21_mod_lazy));

    error |= func(&tmp_value, &l_ten, &tmp_value);
  }

  // Заменяем исходник новым значением
  if (!error) error |= s21_lazy_to_lazy_cp(&tmp_value, lazy);

  s21_lazy_destroy(&tmp_value);
  s21_lazy_destroy(&l_ten);

  return error;
}