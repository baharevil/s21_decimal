#include <stdlib.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Деструктор s21_decimal_lazy

  @param[in] *lazy Адрес s21_decimal_lazy
*/
void s21_lazy_destroy(s21_decimal_lazy *lazy) {
  lazy->exponent = lazy->sign = lazy->size = 0;
  if (lazy->mantissa != NULL) free(lazy->mantissa);
}