#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция деления s21_decimal_lazy на мантиссы и
  эксоненты на 10.

  @param[in] *lazy Указатели на значение
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
uint8_t s21_div_lazy_to_10(s21_decimal_lazy *lazy) {
  uint8_t error = 0, carry = 0;
  int16_t count = lazy->size - 1, tmp = 0;

  error |= !s21_lazy_ptr_is_valid(lazy);

  // Идем по существующим байтам и умножаем их с переносом старших бит
  while (!error && count >= 0) {
    tmp = (lazy->mantissa[count] + carry * 256) / 10;
    carry = lazy->mantissa[count] - 10 * tmp;
    lazy->mantissa[count] = tmp;
    count--;
  }

  // Уменьшаем экспоненту на 1, снаружи этого делать не надо
  if (!error) lazy->exponent -= (lazy->exponent != 0);

  return error;
}