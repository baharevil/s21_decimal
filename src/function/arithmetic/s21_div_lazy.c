#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief "Мотор" функции s21_decimal_lazy.

  Подсчитывает сколько value_2 в value_1

  @note Высчитывает если value_1 >= value_2

  @param[in] *value_1,*value_2 Делимое и делитель
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
int s21_div_lazy_core(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                      s21_decimal_lazy *result) {
  int error = 0;

  // Первичная валидация
  error |= !s21_lazy_ptr_is_valid(value_1);
  error |= !s21_lazy_ptr_is_valid(value_2);
  error |= !s21_lazy_ptr_is_valid(result);

  if (!error) {
    // Инициализация переменых
    s21_decimal_lazy lazy_two = {0}, lazy_one = {0}, tmp = {0}, tmp_res = {0};
    error |= s21_from_int_to_lazy(1, &lazy_one);
    error |= s21_from_int_to_lazy(2, &lazy_two);
    error |= s21_lazy_init(&tmp, NULL);
    error |= s21_lazy_init(&tmp_res, NULL);
    error |= s21_lazy_upsize(value_1, value_2);

    // Рассчет через битовый сдвиг
    if (!error) {
      lazy_one.exponent = result->exponent;
      int64_t i = value_2->size * sizeof(*value_2->mantissa) * CHAR_BIT - 1;
      while (i >= 0 && !s21_is_null_lazy(value_1)) {
        s21_lazy_left_shift(value_2, &tmp, i);
        if (s21_is_equal_lazy(value_1, &tmp) >= 0) {
          s21_sub_lazy(value_1, &tmp, value_1);
          s21_lazy_left_shift(&lazy_one, &tmp, i);
          s21_add_lazy(&tmp_res, &tmp, &tmp_res);
        }
        --i;
      }
    }
    if (!error) error |= s21_lazy_to_lazy_cp(&tmp_res, result);

    s21_lazy_destroy(&tmp);
    s21_lazy_destroy(&tmp_res);
    s21_lazy_destroy(&lazy_one);
    s21_lazy_destroy(&lazy_two);
  }

  return error;
}

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция деления двух s21_decimal_lazy.

  Функция нормализует значения s21_decimal_lazy
  и делит их методом: деление в столбик с доделением остатка
  по необходимости

  @param[in] *value_1,*value_2 Делимое и делитель
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка, 2 - деление на 0
*/
int s21_div_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;

  s21_decimal ten = {{0xa, 0x0, 0x0, 0x0}};
  s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal five = {{0x5, 0x0, 0x0, 0x0}};
  s21_decimal_lazy lazy_ten = {0}, lazy_one = {0}, lazy_five = {0};

  s21_decimal_lazy carry = {0}, divider = {0}, res_temp = {0}, tmp = {0};

  // Первичная валидация
  error |= !s21_lazy_ptr_is_valid(value_1);
  error |= !s21_lazy_ptr_is_valid(value_2);
  error |= !s21_lazy_ptr_is_valid(result);

  // Вторичная валидация
  if (!error && s21_is_null_lazy(value_2)) error = div_by_0;

  // Инициализация переменных
  if (!error) {
    error |= s21_lazy_init(&tmp, NULL);
    error |= s21_lazy_init(&carry, NULL);
    error |= s21_lazy_init(&divider, NULL);
    error |= s21_lazy_init(&res_temp, NULL);
    error |= s21_lazy_init(&lazy_one, &one);
    error |= s21_lazy_init(&lazy_five, &five);
    error |= s21_lazy_init(&lazy_ten, &ten);
  }

  // Расчет целой части от деления
  if (!error) error = s21_mod_lazy(value_1, value_2, result);
  // Расчет остатка от деления
  if (!error) error = s21_mul_lazy(result, value_2, &res_temp);
  if (!error) error = s21_sub_lazy(value_1, &res_temp, &carry);

  // Подготовка к рачету дробной части
  if (!error) {
    error = s21_lazy_to_lazy_cp(result, &res_temp);
    error |= s21_lazy_to_lazy_cp(value_2, &divider);
  }

  if (!error) {
    carry.exponent = carry.sign = 0;
    divider.exponent = divider.sign = 0;
  }

  // Расчет дробной части
  while (!error && !s21_is_null_lazy(&carry) && res_temp.exponent < 30) {
    error |= s21_mul_lazy(&lazy_ten, &carry, &carry);
    error |= s21_mul_lazy_to_10(&res_temp);
    error |= s21_div_lazy_core(&carry, &divider, &tmp);
    error |= s21_add_lazy(&res_temp, &tmp, &res_temp);
  }

  if (!error && s21_is_equal_lazy(&carry, &lazy_five) >= 0) {
    lazy_one.exponent = res_temp.exponent;
    error |= s21_add_lazy(&res_temp, &lazy_one, &res_temp);
  }

  // Копирование результата + Расчет знака
  if (!error) {
    error = s21_lazy_to_lazy_cp(&res_temp, result);
    result->sign = (value_1->sign != value_2->sign);
  }

  // Уничножение переменных
  s21_lazy_destroy(&tmp);
  s21_lazy_destroy(&carry);
  s21_lazy_destroy(&divider);
  s21_lazy_destroy(&res_temp);
  s21_lazy_destroy(&lazy_one);
  s21_lazy_destroy(&lazy_five);
  s21_lazy_destroy(&lazy_ten);

  return error;
}
