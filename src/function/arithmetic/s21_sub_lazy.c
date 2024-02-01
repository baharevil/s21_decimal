#include <stdlib.h>

#include "s21_decimal.h"

/// @todo 1 - tmp & use lvalue & rvalue

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция вычитания s21_decimal_lazy.

  Функция нормализует и выравнивает по размеру значения
  s21_decimal_lazy. Далее происходит вычетания через
  инверсию бит и дальнейшее их сложение в функции
  s21_add_uint8_t().

  @param[in] *value_1,*value_2 Указатели на вычитаемые знаачения
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
int s21_sub_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int8_t error = 0, done = 0;
  s21_decimal_lazy lvalue = {0}, rvalue = {0}, null = {0};
  s21_decimal_lazy tmp_v1 = {0}, tmp_v2 = {0};
  s21_decimal_lazy tmp = {0};


  // Первичная валидация
  error |= !s21_lazy_ptr_is_valid(value_1);
  error |= !s21_lazy_ptr_is_valid(value_2);
  error |= !s21_lazy_ptr_is_valid(result);

  error |= s21_lazy_init(&null, NULL);
  error |= s21_lazy_init(&lvalue, NULL);
  error |= s21_lazy_init(&rvalue, NULL);

  if (!error) {
    error |= s21_lazy_to_lazy_cp(value_1, &lvalue);
    error |= s21_lazy_to_lazy_cp(value_2, &rvalue);
  }

  // Сравнения
  if (!error) {
    int8_t subzero1 = s21_is_equal_lazy(&lvalue, &null);
    int8_t subzero2 = s21_is_equal_lazy(&rvalue, &null);

    // Если слева "+", а справа "-", то это просто сложение (5 - (-1) = 5 + 1)
    if (subzero1 >= 0 && subzero2 < 0) {
      rvalue.sign = 0;
      error |= s21_add_lazy(&lvalue, &rvalue, result);
      done++;
    }

    // Если слева "-", а справа "+", то это "отрицательное" сложение
    // (-5 - 1 = -6)
    else if (subzero1 < 0 && subzero2 >= 0) {
      rvalue.sign = 1;
      error |= s21_add_lazy(&lvalue, &rvalue, result);
      done++;
    }

    // Если оба меньше (-5 - (-1) = -4)
    // Если оба меньше (-1 - (-5) = 4)
    else
      lvalue.sign = rvalue.sign = 0;
  }

  // Сравнение на то, что уменьшаемое меньше вычитаемого
  if (!error && !done) {
    if ((s21_is_equal_lazy(&lvalue, &rvalue) == -1)) {
      error |= s21_lazy_to_lazy_cp(&lvalue, &tmp);
      error |= s21_lazy_to_lazy_cp(&rvalue, &lvalue);
      error |= s21_lazy_to_lazy_cp(&tmp, &rvalue);
      result->sign = !value_1->sign;
    }
    else
      result->sign = value_1->sign;
  }

  if (!error && !done) {
    int8_t normal = s21_is_normal_lazy(&lvalue, &rvalue);

    // Не нормализованы и не выравнены
    if (normal == 0) {
      error |= s21_lazy_normalize_greater(&lvalue, &rvalue);
      error |= s21_lazy_upsize(&lvalue, &rvalue);
    }

    // Нормализованы, но не выравнены
    else if (normal == 1) {
      error |= s21_lazy_upsize(&lvalue, &rvalue);
    }

    // 2 - нормализованы и выровняны по размеру
    else
      error |= (normal != 2);

    if (result->size != lvalue.size) s21_lazy_resize(result, lvalue.size);
    if (result->exponent != lvalue.exponent) result->exponent = lvalue.exponent;
  }

  if (!error && !done) {
    uint8_t carry = 0;
    uint16_t res = 0;

    for (size_t i = 0; i < result->size; i++) {
      res = lvalue.mantissa[i] - rvalue.mantissa[i] - carry;
      result->mantissa[i] = (uint8_t)res;
      carry = ((res >> sizeof(uint8_t) * CHAR_BIT) > 0);
    }
  }

  s21_lazy_destroy(&null);
  s21_lazy_destroy(&lvalue);
  s21_lazy_destroy(&rvalue);
  s21_lazy_destroy(&tmp_v1);
  s21_lazy_destroy(&tmp_v2);

  return error;
}