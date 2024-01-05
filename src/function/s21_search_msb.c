#include "s21_decimal.h"

#include <stddef.h>

/*
Функция поиска старшего значащего бита (Most Significant Bit) в числе s21_decimal
Возвращает целочисленное количество байт от старшего значащего бита до конца мантиссы,
т.е. реальный размер в байтах.
*/
unsigned s21_search_msb(s21_decimal *decimal) {
  int result = 0;
    
  // счетчик бит в байте
  int8_t bit_count = CHAR_BIT - 1;

  // определяем кол-во элементов
  size_t bytes_max = sizeof(decimal->mantissa.bits);
  size_t byte = bytes_max;

  // Проверка на пустой decimal, пока выключено
  //if (s21_decimal_is_null(decimal))
  //    result = -1;

  uint8_t *ptr = (uint8_t *) &decimal->mantissa.bits;
  ptr += bytes_max;
  uint8_t mask = 0;

  while (!result && byte >= bytes_max) {
      while (!result && bit_count >= 0)
      {
          mask = (uint8_t) 1 << bit_count--;
          result = (*(ptr + byte) & mask);
      }
      byte -= (result == 0);
  }
  result = byte;

  return result;
}