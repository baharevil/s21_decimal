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
  error |= s21_is_valid("%lp%lp%lp", value_1, value_2, result);

  if (!error) {
    // Необходимо для инкрементации
    s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal_lazy lazy_one = {0};

    error |= s21_lazy_init(&lazy_one, &one);
    lazy_one.exponent = result->exponent;

    while (!error && (s21_is_equal_lazy(value_1, value_2) >= 0)) {
      error |= s21_sub_lazy(value_1, value_2, value_1);
      error |= s21_add_lazy(result, &lazy_one, result);
    }

    s21_lazy_destroy(&lazy_one);
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
  s21_decimal_lazy lazy_ten = {0};
  s21_decimal_lazy carry = {0}, divider = {0}, res_temp = {0};

  // Первичная валидация
  error |= s21_is_valid("%lp%lp%lp", value_1, value_2, result);

  // Вторичная валидация
  if (!error && s21_is_null_lazy(value_2)) error = 2;

  // Инициализация переменных
  if (!error) {
    error |= s21_lazy_init(&carry, NULL);
    error |= s21_lazy_init(&divider, NULL);
    error |= s21_lazy_init(&res_temp, NULL);
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
  while (!error && !s21_is_null_lazy(&carry) && res_temp.exponent < 28) {
    error |= s21_mul_lazy(&lazy_ten, &carry, &carry);
    error |= s21_mul_lazy_to_10(&res_temp);
    error |= s21_div_lazy_core(&carry, &divider, &res_temp);
  }

  // Копирование результата + Расчет знака
  if (!error) {
    error = s21_lazy_to_lazy_cp(&res_temp, result);
    result->sign = (value_1->sign != value_2->sign);
  }

  // Уничножение переменных
  s21_lazy_destroy(&carry);
  s21_lazy_destroy(&divider);
  s21_lazy_destroy(&res_temp);
  s21_lazy_destroy(&lazy_ten);

  return error;
}
