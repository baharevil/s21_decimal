#include <stddef.h>

#include "s21_decimal.h"

/// @todo добавить в конце s21_from_decimal_to_lazy

/*!
  @ingroup Support Функции для служебного пользования
  @brief Функция инициализации s21_decimal_lazy

  @param[in] *lazy Адрес инициализируемого значения
  @return Код ошибки: 0 - OK, 1 - ERROR
*/
uint8_t s21_lazy_init(s21_decimal_lazy *lazy) {
  uint8_t error = 0;
  error |= (lazy == NULL);

  if (!error) {
    lazy->sign = 0;
    lazy->exponent = 0;
    lazy->size = 0;
    lazy->mantissa = NULL;
    // error |= s21_lazy_zeroing(lazy, 1);
    error |= s21_lazy_resize(lazy, 1);
  }

  return error;
}