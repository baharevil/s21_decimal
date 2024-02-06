#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup AnotherFunction Другие функции
  @brief Округляет указанное Decimal число до ближайшего целого числа в сторону
  отрицательной бесконечности.

  @param[in] value Указатели на массивы
  @param[in] result Указатель на результат
  @return 0 - OK 1 - ошибка вычисления
*/
int s21_floor_lazy(s21_decimal_lazy *value, s21_decimal_lazy *result) {
  int error = 0;

  error |= (value == NULL || value->mantissa == NULL || result == NULL ||
            result->mantissa == NULL);

  if (!error) {
    error |= s21_truncate_lazy(value, result);
    if (!error && result->sign) {
      s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
      s21_decimal_lazy lazy_one;
      error |= s21_lazy_init(&lazy_one, &one);
      if (!error) error |= s21_sub_lazy(result, &lazy_one, result);
      s21_lazy_destroy(&lazy_one);
    }
  }

  return error;
}