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
  int rank = 0, cmp = 0;

  //
  s21_decimal ten = {{0xa, 0x0, 0x0, 0x10000}};
  s21_decimal five = {{0x5, 0x0, 0x0, 0x10000}};
  s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal two = {{0x2, 0x0, 0x0, 0x0}};

  s21_decimal_lazy lazy_five = {0};
  s21_decimal_lazy lazy_one = {0};
  s21_decimal_lazy lazy_two = {0};

  s21_decimal_lazy tmp_value = {0}, carry = {0};
  s21_decimal_lazy l_ten = {0};

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
    error |= s21_lazy_init(&carry, NULL);
    error |= s21_lazy_init(&l_ten, &ten);
    error |= s21_lazy_init(&lazy_five, &five);
    error |= s21_lazy_init(&lazy_one, &one);
    error |= s21_lazy_init(&lazy_two, &two);
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

  // если |exp - lazy->exponent| == 0, то нужно вызвать функцию с 1
  if (!error && res_exp == 0) error |= s21_div_lazy_to_10(&l_ten);

  // Выбор функции и расчет остатка в случае уменьшения экспоненты вниз
  if (!error) {
    int (*func)(s21_decimal_lazy *, s21_decimal_lazy *, s21_decimal_lazy *) =
        ((int (*)(s21_decimal_lazy *, s21_decimal_lazy *, s21_decimal_lazy *))(
            (direction >= 0) * (uintptr_t)s21_mul_lazy +
            (direction < 0) * (uintptr_t)s21_mod_lazy));

    error |= func(&tmp_value, &l_ten, &tmp_value);

    if (!error && func == s21_mod_lazy) {
      error = s21_mul_lazy(&tmp_value, &l_ten, &carry);
      if (!error) error = s21_sub_lazy(lazy, &carry, &carry);
    }

    s21_lazy_destroy(&l_ten);
    error |= s21_lazy_init(&l_ten, &ten);
    carry.sign = 0;
  }

  /*
    Если tmp_value.exponent != 0, значит работаем с дробной частью
    и нужно выравнять значение 5 в нужный ранг.

    Например пришло число 123.5000051234 == 1235000051234 / 10^10, и new_exp
    == 5.

    После вызова функции расчета получаем:
    tmp_value = 12350000 / 10^5  = 123.500000000
    carry     =    51234 / 10^10 = 000.0000051234

    Значит будем сравнивать со значением 000.0000050000 = 50000 / 10^10


    Если tmp_value.exponent == 0, необходимо сравнить carry с 0,5
  */

  // Выравнивание
  if (!error && tmp_value.exponent) {
    if (!error) error |= s21_lazy_ranking(&carry, &rank);

    while (!error && lazy_five.exponent < rank)
      error |= s21_mul_lazy(&lazy_five, &l_ten, &lazy_five);

    lazy_five.exponent = carry.exponent;
    lazy_one.exponent = tmp_value.exponent;
  }

  // Сравнение
  if (!error) {
    lazy_one.sign = tmp_value.sign;
    cmp = s21_is_equal_lazy(&carry, &lazy_five);
  }

  // Если cmp == 0, значит банковское окргление
  if (!error && cmp == 0) {
    error |= s21_div_lazy(&tmp_value, &lazy_two, &carry);
    if (carry.exponent != tmp_value.exponent)
      error |= s21_add_lazy(&tmp_value, &lazy_one, &tmp_value);
  }

  // Если cmp == 1, значит математическое окргление
  else if (cmp == 1) {
    error |= s21_add_lazy(&tmp_value, &lazy_one, &tmp_value);
  }

  // Иначе проверям на код ошибки
  else
    error = (cmp == -2);

  // Заменяем исходник новым значением
  if (!error) error |= s21_lazy_to_lazy_cp(&tmp_value, lazy);

  s21_lazy_destroy(&tmp_value);
  s21_lazy_destroy(&carry);
  s21_lazy_destroy(&lazy_five);
  s21_lazy_destroy(&lazy_one);
  s21_lazy_destroy(&lazy_two);
  s21_lazy_destroy(&l_ten);

  return error;
}