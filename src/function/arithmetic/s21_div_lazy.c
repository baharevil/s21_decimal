#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief "Мотор" функции s21_decimal_lazy.

  Подсчитывает сколько value_2 в value_1

  @note Высчитывает если value_2 <= value_1

  @param[in] *value_1,*value_2 Делимое и делитель
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
int s21_div_lazy_core(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                      s21_decimal_lazy *result) {
  int error = 0;

  // Первичная валидация
  error |= (value_1 == NULL || value_1->mantissa == NULL);
  error |= (value_2 == NULL || value_2->mantissa == NULL);
  error |= (result == NULL || result->mantissa == NULL);

  if (!error) {
    // Необходимо для инкрементации
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

/// @todo тесты
/// @todo округление
/// @todo передача по значению для облегчения работы функций

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

  if (!error && s21_is_null_lazy(value_2)) error = 2;

  if (!error) {
    // 0. Создаем необходимые переменные
    int16_t exp_res = 0;

    // необходимо для увеличения результата
    s21_decimal ten = {{0xa, 0x0, 0x0, 0x0}};
    // необходимо для деления в столбик
    s21_decimal rank = {{0x100, 0x0, 0x0, 0x0}};
    /*
      carry     - перенос значения между расчетами
      divider   - делитель
      res_temp  - промежуточный результат
      lazy_ten  - 10 в s21_decimal lazy
      lazy_rank - 100 в hex в s21_decimal lazy
    */
    s21_decimal_lazy carry = {0}, divider = {0}, res_temp = {0}, lazy_ten = {0},
                     lazy_rank = {0};

    // Инициализация переменных
    error |= s21_lazy_init(&res_temp, NULL);
    error |= s21_lazy_init(&lazy_ten, &ten);
    error |= s21_lazy_init(&lazy_rank, &rank);
    error |= s21_lazy_resize(&carry, value_1->size);
    error |= s21_lazy_to_lazy_cp(value_2, &divider);
    error |= s21_lazy_to_lazy_cp(result, &res_temp);

    if (!error) {
      // Для работы с модулями
      carry.sign = 0;
      divider.sign = 0;

      // 1. Высчитываем итоговую экспоненту
      /// @bug заменить на валуе_1
      exp_res = carry.exponent - divider.exponent;

      /*
        2. Деление в столбик

        Пример:
        1 2 3 4 5 | 2 <- divider
        1 2       ----
        ---       | 6 1 7 2 <- res_tmp
          0 3
            2
          ---
            1 4
            1 4
            ---
              0 5
                4
              ---
                1 <- carry
      */
      for (size_t s = value_1->size; !error && s != 0; s--) {
        // Если carry >= divider -> делим
        if (s21_is_equal_lazy(&carry, &divider) >= 0)
          error |= s21_div_lazy_core(&carry, &divider, &res_temp);

        // увеличеваем carry & res_temp на байт
        s21_mul_lazy(&carry, &lazy_rank, &carry);
        s21_mul_lazy(&res_temp, &lazy_rank, &res_temp);
        // Заносим новое значение (По примеру сначало 1, потом 2 ...)
        s21_add_uint8_t(carry.mantissa, value_1->mantissa + s - 1,
                        carry.mantissa, 1);
      }
    }

    // 3. Если экспонента < 0 ---> Увеличиваем результат в 10^epx раз
    while (!error && (exp_res < 0)) {
      error |= s21_mul_lazy(&res_temp, &lazy_ten, &res_temp);
      exp_res++;
    }

    // 4. Запоминаем итоговую экспоненту
    res_temp.exponent = exp_res;

    // 5. Высчитываем остаток от деления
    while (!error && !s21_is_null_lazy(&carry) && res_temp.exponent < 28) {
      error |= s21_mul_lazy(&lazy_ten, &carry, &carry);
      error |= s21_mul_lazy_to_10(&res_temp);
      error |= s21_div_lazy_core(&carry, &divider, &res_temp);
    }

    // Копируем результат + подсчет знака
    if (!error) {
      error = s21_lazy_to_lazy_cp(&res_temp, result);
      result->sign = (value_1->sign != value_2->sign);
    }

    s21_lazy_destroy(&carry);
    s21_lazy_destroy(&divider);
    s21_lazy_destroy(&res_temp);
    s21_lazy_destroy(&lazy_ten);
    s21_lazy_destroy(&lazy_rank);
  }

  return error;
}