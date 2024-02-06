#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Вычисляет целую часть от деления value_1 на value_2

  @param[in] *value_1,*value_2 Делимое и делитель
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка, 2 - деление на 0
*/
int s21_mod_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;
  int16_t exp_res = 0;

  s21_decimal rank = {{0x100, 0x0, 0x0, 0x0}};
  s21_decimal_lazy lazy_rank = {0}, tmp_v1 = {0};
  s21_decimal_lazy carry = {0}, divider = {0}, res_temp = {0};

  // Первичная валидация
  error |= !s21_lazy_ptr_is_valid(value_1);
  error |= !s21_lazy_ptr_is_valid(value_2);
  error |= !s21_lazy_ptr_is_valid(result);

  // Вторичная валидация
  if (!error && s21_is_null_lazy(value_2)) error = 2;

  // Инициализация переменных
  if (!error) {
    error |= s21_lazy_init(&carry, NULL);
    error |= s21_lazy_init(&divider, NULL);
    error |= s21_lazy_init(&res_temp, NULL);
    error |= s21_lazy_init(&lazy_rank, &rank);
    error |= s21_lazy_to_lazy_cp(value_1, &tmp_v1);
  }

  // Подсчет экспоненты
  if (!error) {
    exp_res = value_1->exponent - value_2->exponent;

    while (!error && (exp_res < 0)) {
      error |= s21_mul_lazy_to_10(&tmp_v1);
      exp_res++;
    }
  }

  //  Подготовка к делению
  if (!error) {
    error |= s21_lazy_resize(&carry, tmp_v1.size);
    error |= s21_lazy_to_lazy_cp(value_2, &divider);
    divider.sign = divider.exponent = 0;
  }

  // Расчте целой части методом деления в столбик
  for (size_t s = tmp_v1.size; !error && s != 0; s--) {
    s21_mul_lazy(&carry, &lazy_rank, &carry);
    s21_mul_lazy(&res_temp, &lazy_rank, &res_temp);
    s21_add_uint8_t(carry.mantissa, tmp_v1.mantissa + s - 1, carry.mantissa, 1);

    if (s21_is_equal_lazy(&carry, &divider) >= 0)
      error |= s21_div_lazy_core(&carry, &divider, &res_temp);
  }

  // Копирование результата + Расчет знака и эксп.
  if (!error) {
    error = s21_lazy_to_lazy_cp(&res_temp, result);
    result->sign = (value_1->sign != value_2->sign);
    result->exponent += exp_res;
  }

  // Уничножение переменных
  s21_lazy_destroy(&tmp_v1);
  s21_lazy_destroy(&carry);
  s21_lazy_destroy(&divider);
  s21_lazy_destroy(&res_temp);
  s21_lazy_destroy(&lazy_rank);

  return error;
}