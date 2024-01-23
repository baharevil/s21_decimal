#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

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
  // Временное переменная чтобы не испортить оригинал
  s21_decimal_lazy tmp_value = {0};
  // Напраление изменения стпени. Если 1 -> увеличиваем, -1 -> уменьшаем
  int8_t direction = 0;

  // Первичная проверка
  error = (lazy == NULL);

  if (!error) {
    direction = (exp > lazy->exponent) - (exp < lazy->exponent);
    // Проверяем что все норм скопировалось
    error |= s21_lazy_to_lazy_cp(lazy, &tmp_value);
  }

  if (!error) {
    // Выбор необходимой функции для нормализации
    uint8_t (*func)(s21_decimal_lazy *) = (uint8_t(*)(s21_decimal_lazy *))(
        (direction >= 0) * (uintptr_t)s21_mul_lazy_to_10 +
        (direction < 0) * (uintptr_t)s21_div_lazy_to_10);

    // Нормализация
    while (tmp_value.exponent != exp) error = func(&tmp_value);

    error |= s21_lazy_to_lazy_cp(&tmp_value, lazy);
  }

  if (!error) {
    free(tmp_value.mantissa);
    tmp_value.mantissa = NULL;
  }

  if (tmp_value.mantissa != NULL) free(tmp_value.mantissa);

  return error;
}