#include <stdlib.h>

#include "s21_decimal.h"

/*
    Арифметические операторы. Сумма.
    Функции возвращают код ошибки:

    0 - OK
    1 - число слишком велико или равно бесконечности
    2 - число слишком мало или равно отрицательной бесконечности
    3 - деление на 0
*/

// TODO: коды ошибок
//! BUG: обработка знака
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_decimal_lazy lazy1, lazy2, res;

  s21_lazy_init(&lazy1);
  s21_lazy_init(&lazy2);
  s21_lazy_init(&res);

  s21_dec_to_lazy_cp(&value_1, &lazy1);
  s21_dec_to_lazy_cp(&value_2, &lazy2);

  error = s21_add_lazy(&lazy1, &lazy2, &res);

  // Функция обратного копирования s21_lazy_to_dec()
  // копирует только 12 байт или менее, в зависимости от размера src->size
  s21_lazy_to_dec(&res, result);

  if (lazy1.mantissa) free(lazy1.mantissa);
  if (lazy2.mantissa) free(lazy2.mantissa);
  if (res.mantissa) free(res.mantissa);


  return error;
}
