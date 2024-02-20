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
int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  s21_decimal_lazy lazy_result = {0}, lazy_value = {0};

  error |= !s21_decimal_ptr_is_valid(&value);
  error |= (result == NULL);

  if (!error) {
    error |= s21_lazy_init(&lazy_value, &value);
    error |= s21_lazy_init(&lazy_result, result);
  } 
  if (!error) error |= s21_floor_lazy(&lazy_value, &lazy_result);
  if (!error) error |= s21_from_lazy_to_decimal(&lazy_result, result);

  s21_lazy_destroy(&lazy_value);
  s21_lazy_destroy(&lazy_result);

  return error;
}