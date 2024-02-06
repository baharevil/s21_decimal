#include <math.h>
#include <stdlib.h>

#include "s21_decimal.h"

/// @todo Добавить коды ошибок

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief

  @param[in] *result Указатель значение
  @param[in] *result Указатель значение
  @return Код ошибки: -1: another error, 0: ОК, 1: inf, 2: neg_inf
*/
int s21_aritmetic_error(s21_decimal_lazy *value) {
  int error = arifm_ok, sign = 0;
  s21_decimal inf = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  s21_decimal_lazy l_inf = {0};

  error = -(s21_lazy_init(&l_inf, &inf));

  if (!error) {
    l_inf.sign = sign = value->sign;

    error = (s21_is_equal_lazy(value, &l_inf));
    if (error != -2 && error != 0)
      error = ((int)(pow(2, sign)) * (error == (int)pow(-1, sign)));
    else
      error = -(error == -2);
  }

  s21_lazy_destroy(&l_inf);
  return error;
}