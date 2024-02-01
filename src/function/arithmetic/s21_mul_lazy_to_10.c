#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция умножения s21_decimal_lazy на мантиссы и
  эксоненты на 10.

  @param[in] *lazy Указатели на значение
  @return 0 - ОК, 1 - ошибка
*/
uint8_t s21_mul_lazy_to_10(s21_decimal_lazy *lazy) {
  uint8_t error = 0, carry = 0;
  uint16_t count = 0, tmp = 0;

  error |= !s21_lazy_ptr_is_valid(lazy);

  // Идем по существующим байтам и умножаем их с переносом старших бит
  while (!error && count < lazy->size) {
    tmp = (uint16_t)lazy->mantissa[count] * 10 + carry;
    lazy->mantissa[count] = (uint8_t)tmp;
    carry = tmp >> 8;
    count++;
  }

  // Если остался перенос, доаллоцируем себе массив
  if (carry != 0) {
    error |= s21_lazy_resize(lazy, lazy->size + 1);
    if (!error) lazy->mantissa[lazy->size - 1] = carry;
  }

  // Увеличиваем экспоненту на 1, снаружи этого делать не надо
  if (!error) lazy->exponent++;

  return error;
}