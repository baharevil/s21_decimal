#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция сложения массива uint8_t.

  @param[in] *v1,*v2 Указатели на складываемые массивы
  @param[in] *result Указатель на результат
  @param[in] size Разммер массивов
  @return carry - остаточный перенос

  @warning Работает только при одинаковых размерах
*/
uint16_t s21_add_uint8_t(uint8_t *v1, uint8_t *v2, uint8_t *result,
                         uint8_t size) {
  uint8_t count = 0;
  uint16_t res = 0, carry = 0;

  while (count < size) {
    res = *(v1 + count) + *(v2 + count) + carry;
    *(result + count) = (uint8_t)res;
    carry = res >> sizeof(uint8_t) * CHAR_BIT;
    count++;
  }

  return carry;
}

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция сложения двух s21_decimal_lazy.

  Функция нормализует значения s21_decimal_lazy
  и складывает их через цикл while. В конце, при необходимости
  (если остался перенос) доалоцирует память.

  @param[in] *value_1,*value_2 Указатели на складываемые числа
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка

  @version 2
*/
int s21_add_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;

  // Первичная валидация
  error |= !s21_lazy_ptr_is_valid(value_1);
  error |= !s21_lazy_ptr_is_valid(value_2);
  error |= !s21_lazy_ptr_is_valid(result);

  int8_t is_normal = 0;
  uint16_t carry = 0;
  s21_decimal_lazy lvalue = {0}, rvalue = {0};

  if (value_1->sign != value_2->sign)
    s21_sub_lazy(value_1, value_2, result);

  else {
    error |= s21_lazy_init(&lvalue, NULL);
    error |= s21_lazy_init(&rvalue, NULL);

    if (!error) {
      error |= s21_lazy_to_lazy_cp(value_1, &lvalue);
      error |= s21_lazy_to_lazy_cp(value_2, &rvalue);
    }

    if (!error) {
      is_normal = s21_is_normal_lazy(&lvalue, &rvalue);

      // нормализация по экспоненте и размеру
      if (is_normal == 0) {
        error |= s21_lazy_normalize_greater(&lvalue, &rvalue);
        error |= s21_lazy_upsize(&lvalue, &rvalue);
      }

      // нормализация по размеру
      else if (is_normal == 1) {
        error |= s21_lazy_upsize(&lvalue, &rvalue);
      }

      // ожидаем что нормализованы и выровняны по размеру - == 2
      else
        error = (is_normal != 2);
    }

    if (!error) {
      if (result->size != lvalue.size) s21_lazy_resize(result, lvalue.size);
      if (result->exponent != lvalue.exponent)
        result->exponent = lvalue.exponent;

      carry = s21_add_uint8_t(lvalue.mantissa, rvalue.mantissa,
                              result->mantissa, result->size);
    }

    if (carry != 0) {
      error |= s21_lazy_resize(result, result->size + 1);
      if (!error) result->mantissa[result->size - 1] = carry;
    }

    result->sign = (value_1->sign && value_2->sign);
  }

  s21_lazy_destroy(&lvalue);
  s21_lazy_destroy(&rvalue);

  return error;
}
