#include <stdlib.h>

#include "s21_decimal.h"

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

  error |= s21_lazy_init(&lvalue, NULL);
  error |= s21_lazy_init(&rvalue, NULL);
  error |= s21_lazy_init(&null, NULL);

  // Первичная валидация
  error |= (value_1 == NULL || value_1->mantissa == NULL);
  error |= (value_2 == NULL || value_2->mantissa == NULL);

  //Сравнения
  if (!error) {
    int8_t subzero1 = s21_is_equal_lazy(value_1, &null);
    int8_t subzero2 = s21_is_equal_lazy(value_2, &null);

    // Если слева "+", а справа "-", то это просто сложение (5 - (-1) = 5 + 1)
    if (subzero1 >= 0 && subzero2 < 0) {
      value_2->sign = 0;
      error |= s21_add_lazy(value_1, value_2, result);
      done++;
    }

    // Если слева "-", а справа "+", то это "отрицательное" сложение (-5 - 1 =
    // -6)
    /// @bug Изменять знак у value_2
    else if (subzero1 < 0 && subzero2 >= 0) {
      value_1->sign = 0;
      result->sign = 1;
      error |= s21_add_lazy(value_1, value_2, result);
      done++;
    }

    // Если оба меньше (-5 - (-1) = -4)
    else if (subzero1 < 0 && subzero2 < 0) {
      value_1->sign = 0;
      value_2->sign = 0;
      result->sign = 1;
    }
  }

  //Сравнение на то, что уменьшаемое меньше вычитаемого
  if (!error && !done) {
    if ((s21_is_equal_lazy(value_1, value_2) == -1)) {
      error |= s21_lazy_to_lazy_cp(value_2, &lvalue);
      error |= s21_lazy_to_lazy_cp(value_1, &rvalue);
    } else {
      error |= s21_lazy_to_lazy_cp(value_1, &lvalue);
      error |= s21_lazy_to_lazy_cp(value_2, &rvalue);
    }
  }

  if (!error) {
    int8_t normal = s21_is_normal_lazy(&lvalue, &rvalue);

    if (normal == 0) {
      error |= s21_lazy_normalize_greater(&lvalue, &rvalue);
      error |= s21_lazy_upsize(&lvalue, &rvalue);
    }

    else if (normal == 1) {
      error |= s21_lazy_upsize(&lvalue, &rvalue);
    }

    // 2 - нормализованы и выровняны по размеру
    else
      error |= (normal != 2);
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

  s21_lazy_destroy(&lvalue);
  s21_lazy_destroy(&rvalue);
  s21_lazy_destroy(&null);

  return error;
}