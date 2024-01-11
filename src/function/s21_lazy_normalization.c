#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

uint8_t s21_lazy_normalization(s21_decimal_lazy *lazy, uint8_t exp) {
  uint8_t result = 0;

  // Первичная проверка
  if (lazy == NULL) result = 1;

  if (!result) {
    // Напраление изменения стпени. Если 1 -> увеличиваем, -1 -> уменьшаем
    int8_t direction = (exp > lazy->exponent) - (exp < lazy->exponent);
    // Временное переменная чтобы не испортить оригинал
    s21_decimal_lazy tmp_value = {0};

    // Проверяем что все норм скопировалось
    if (s21_lazy_to_lazy_cp(lazy, &tmp_value) != 1) {
      // Выбор необходимой функции для нормализации
      uint8_t (*func)(s21_decimal_lazy *) =
          (direction > 0) ? s21_mul_lazy_to_10 : s21_div_lazy_to_10;

      // Нормализация
      while (tmp_value.exponent != exp) result = func(&tmp_value);

    } else
      result = 1;

    if (s21_lazy_to_lazy_cp(&tmp_value, lazy) != 1) {
      free(tmp_value.mantissa);
      tmp_value.mantissa = NULL;
    } else
      result = 1;

    if (tmp_value.mantissa != NULL) free(tmp_value.mantissa);
  }

  return result;
}