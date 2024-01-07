#include <stddef.h>

#include "s21_decimal.h"

/*
Функция поиска старшего значащего бита (Most Significant Bit) в числе
s21_decimal Возвращает целочисленное количество байт от старшего значащего бита
до конца мантиссы, т.е. реальный размер в байтах.
*/
uint8_t s21_search_msb(s21_decimal *decimal) {
  int result = 0;

  // счетчик бит в байте
  int8_t bit_count = 0;

  // определяем кол-во элементов в массиве
  size_t bytes_max = sizeof(decimal->mantissa.bytes);
  size_t byte = 0;

  // Проверка на пустой decimal, пока выключено
  // if (s21_decimal_is_null(decimal))
  //    result = -1;

  // Указатель на последний байт в массиве
  uint8_t *ptr = (decimal->mantissa.bytes + bytes_max - 1);
  uint8_t mask = 0;

  // Идем от последнего байта назад
  while (!result && byte < bytes_max) {
    bit_count = CHAR_BIT - 1;
    // Двигаем маску и ищем первый поднятый бит от старших к младшим
    while (!result && bit_count >= 0) {
      mask = (uint8_t)1 << bit_count--;
      result = (*(ptr - byte) & mask);
    }
    // Сдвигаем байт, если не достигли результата
    byte += (result == 0);
  }
  // Возвращаем в качестве результата сколько байт фактически заполнено, от младших
  result = bytes_max - byte;

  return result;
}