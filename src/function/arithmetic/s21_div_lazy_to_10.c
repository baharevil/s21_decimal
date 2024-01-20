#include <stdint.h>
#include <stdlib.h>

#include "s21_decimal.h"

/// @todo Сделать оберткой над s21_div_lazy()

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция деления s21_decimal_lazy на мантиссы и
  эксоненты на 10.

  @param[in] *lazy Указатели на значение
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
uint8_t s21_div_lazy_to_10(s21_decimal_lazy *lazy) {
  uint8_t result = 0;
  uint16_t count = 0;
  uint16_t *tmp = NULL;

  // Грязно. Тащу по половине байта, при этом выхожу за границу мантиссы.
  // Переделать.
  while (count < lazy->size) {
    tmp = (uint16_t *)(lazy->mantissa + count);
    *(lazy->mantissa + count) = *tmp / 16;
    count++;
  }

  // Уменьшаем экспоненту на 1, снаружи этого делать не надо
  if (!result) lazy->exponent -= (lazy->exponent > 0);

  return result;
}