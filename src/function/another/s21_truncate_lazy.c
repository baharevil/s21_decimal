#include <stddef.h>
#include <string.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Возвращает целые цифры указанного Decimal числа.

  Любые дробные цифры отбрасываются, включая начальные нули.

  @param[in] value Указатели на массивы
  @param[in] result Указатель на результат
  @return 0 - OK 1 - ошибка вычисления
*/

uint8_t s21_truncate_lazy(s21_decimal_lazy *value, s21_decimal_lazy *result) {
  uint8_t error = 0;

  error |= (value == NULL || value->mantissa == NULL || result == NULL ||
            result->mantissa == NULL);

  if (!error) {
    error |= s21_lazy_to_lazy_cp(value, result);
    error |= s21_lazy_normalization(result, 0);
  }

  return error;
}