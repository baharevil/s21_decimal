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
*/
int s21_add_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;

  uint16_t size = (value_1->size > value_2->size) * value_1->size +
                  (value_1->size <= value_2->size) * value_2->size;

  if (result->size != size) s21_lazy_resize(result, size);

  if (s21_is_normal_lazy(value_1, value_2) == 0) {
    s21_decimal_lazy *ptr = NULL;
    uint8_t exp = 0;

    ptr = (s21_decimal_lazy *)((value_1->exponent > value_2->exponent) *
                                   (long)value_2 +
                               (value_1->exponent <= value_2->exponent) *
                                   (long)value_1);

    exp = (value_1->exponent > value_2->exponent) * value_1->exponent +
          (value_1->exponent <= value_2->exponent) * value_2->exponent;

    error |= s21_lazy_normalization(ptr, exp);
    result->exponent = exp;
  }

  if (!error) {
    uint16_t res = 0, carry = 0;
    uint8_t count = 0, v1 = 0, v2 = 0;

    while (count < size) {
      if (count < value_1->size) v1 = *(value_1->mantissa + count);
      if (count < value_2->size) v2 = *(value_2->mantissa + count);

      res = v1 + v2 + carry;
      *(result->mantissa + count) = (uint8_t)res;
      carry = res >> sizeof(uint8_t) * CHAR_BIT;
      count++;
      v1 = v2 = 0;
    }

    // Если остался перенос, доаллоцируем себе массив
    if (carry) {
      error |= s21_lazy_resize(result, result->size + 1);
      if (!error) result->mantissa[result->size - 1] = carry;
    } 

  }
  
  return error;
}
