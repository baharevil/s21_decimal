#include <stdlib.h>

#include "s21_decimal.h"


/// @todo дока
/*!
  @bug 
  Большие наклодные разходы. Разбить на деление по разрядно.
  При деление 79,228,162,514,264,337,593,543,950,335 на 1 будет 
  79,228,162,514,264,337,593,543,950,335 вызовов функции вычитания и сложения.
  При переводе на поразрядное деление ---> 126.
*/ 
int s21_div_lazy_core(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                      s21_decimal_lazy *result) {
  int error = 0;

  error |= (value_1 != NULL || value_1->mantissa != NULL);
  error |= (value_2 != NULL || value_2->mantissa != NULL);
  error |= (result != NULL || result->mantissa != NULL);

  if (!error) {
    s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
    s21_decimal_lazy lazy_one = {0}, tmp = {0};

    error |= s21_lazy_init(&lazy_one, &one);
    error |= s21_lazy_resize(&tmp, value_1->size);

    lazy_one.exponent = result->exponent;

    while (!error && (s21_is_equal_lazy(value_1, value_2) >= 0)) {
      error |= s21_sub_lazy(value_1, value_2, value_1);
      error |= s21_add_lazy(result, &lazy_one, result);
    }

    s21_lazy_destroy(&lazy_one);
    s21_lazy_destroy(&tmp);
  }

  return error;
}

/// @todo знак + тесты

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

  error |= (value_1 == NULL || value_1->mantissa == NULL);
  error |= (value_2 == NULL || value_2->mantissa == NULL);
  error |= (result == NULL || result->mantissa == NULL);

  if (!error) {
    if (!s21_is_null_lazy(value_2)) {
      int16_t exp_res = 0;

      s21_decimal ten = {{0xa, 0x0, 0x0, 0x0}};
      s21_decimal_lazy carry = {0}, divider = {0}, res_temp = {0},
                       lazy_ten = {0};

      if (!error) {
        error |= s21_lazy_init(&res_temp, NULL);
        error |= s21_lazy_init(&lazy_ten, &ten);
        error |= s21_lazy_to_lazy_cp(value_1, &carry);
        error |= s21_lazy_to_lazy_cp(value_2, &divider);
        error |= s21_lazy_to_lazy_cp(result, &res_temp);
      }

      if (!error) {
        carry.sign = 0;
        divider.sign = 0;

        // 1.
        exp_res = carry.exponent - divider.exponent;

        // 2.
        error |= s21_div_lazy_core(&carry, &divider, &res_temp);
      }

      // 3.
      while (!error && (exp_res < 0)) {
        error |= s21_mul_lazy(&res_temp, &lazy_ten, &res_temp);
        exp_res++;
      }

      // 4.
      res_temp.exponent = exp_res;

      while (!error && !s21_is_null_lazy(&carry) && res_temp.exponent < 28) {
        error |= s21_mul_lazy(&lazy_ten, &carry, &carry);
        error |= s21_mul_lazy_to_10(&res_temp);
        error |= s21_div_lazy_core(&carry, &divider, &res_temp);
      }

      if (!error) error = s21_lazy_to_lazy_cp(&res_temp, result);

      if (!error) {
        s21_lazy_destroy(&carry);
        s21_lazy_destroy(&divider);
        s21_lazy_destroy(&res_temp);
        s21_lazy_destroy(&lazy_ten);
      }
    } else
      error = 2;
  }

  return error;
}