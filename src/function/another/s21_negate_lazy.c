#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup AnotherFunction Другие функции
  @brief Возвращает результат умножения указанного Decimal на -1.

  @param[in] value Указатели на массивы
  @param[in] result Указатель на результат
  @return 0 - OK 1 - ошибка вычисления
*/
uint8_t s21_negate_lazy(s21_decimal_lazy *value) {
  uint8_t error = 0;

  error |= (value == NULL || value->mantissa == NULL);

  if (!error) {
    value->sign = !value->sign;
  }

  return error;
}