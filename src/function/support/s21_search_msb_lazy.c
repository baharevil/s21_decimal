#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Поиск MSB (Most Significant Bit) в s21_decimal_lazy

  Функция поиска старшего значащего бита (Most Significant Bit) в числе
  s21_decimal Возвращает целочисленное количество байт от старшего значащего
  бита до конца мантиссы, т.е. реальный размер в байтах.

  @param[in] *decimal Адрес значения
  @return Размер мантиссы в байтах
*/
uint8_t s21_search_msb_lazy(s21_decimal_lazy *lazy) {
  int result = 0;

  // счетчик бит в байте
  int8_t bit_count = 0;

  // определяем кол-во элементов в массиве
  size_t bytes_max = lazy->size;
  size_t byte = 0;

  // Указатель на последний байт в массиве
  uint8_t *ptr = (lazy->mantissa + bytes_max - 1);
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
  // Возвращаем в качестве результата сколько байт фактически заполнено, от
  // младших
  result = bytes_max - byte;

  return result;
}