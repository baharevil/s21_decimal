#include <stdlib.h>

#include "s21_decimal.h"

void s21_decimal_right_shift(s21_decimal* value, uint32_t shift) {
  // старшие и младшие биты
  uint32_t senior_bits = 0, junior_bits = 0;
  // кол-во бит в 1 элементе
  size_t size = sizeof(value->mantissa.bits[0]) * CHAR_BIT;
  // определяем кол-во элементов
  size_t count = sizeof(value->mantissa.bits) / sizeof(value->mantissa.bits[0]);

  // максимально допустимый сдвиг == size * count - 1 бит
  if (shift <= size * count - 1) {
    // Пока сдвиг больше кол-ва бит в 1 элементе младшие биты должны равняться
    // старшим
    while (shift >= size) {
      for (size_t i = 0; i != count - 1; i++)
        value->mantissa.bits[i] = value->mantissa.bits[i + 1];
      // Самые старшие зануляем
      value->mantissa.bits[count - 1] = 0;
      shift -= size;
    }

    // Если сдвиг еще остался, то производим точечный перевод бит
    for (size_t i = count; (i != 0) && shift; i--) {
      // запомнили младшие биты
      junior_bits = value->mantissa.bits[i - 1] << (size - shift);
      // сдвинули и записали приходящие биты
      value->mantissa.bits[i - 1] =
          value->mantissa.bits[i - 1] >> shift | senior_bits;
      senior_bits = junior_bits;
    }
  }
}

void s21_decimal_left_shift(s21_decimal* value, uint32_t shift) {
  // старшие и младшие биты
  uint32_t senior_bits = 0, junior_bits = 0;
  // кол-во бит в 1 элементе
  size_t size = sizeof(value->mantissa.bits[0]) * CHAR_BIT;
  // определяем кол-во элементов
  size_t count = sizeof(value->mantissa.bits) / sizeof(value->mantissa.bits[0]);

  // максимально допустимый сдвиг == 95 бит
  if (shift <= size * count - 1) {
    // Пока сдвиг больше кол-ва бит в 1 элементе старшие биты должны равняться
    // младгим
    while (shift >= size) {
      for (size_t i = count - 1; i != 0; i--)
        value->mantissa.bits[i] = value->mantissa.bits[i - 1];
      // Самые младшие зануляем
      value->mantissa.bits[0] = 0;
      shift -= size;
    }

    // Если сдвиг еще остался, то производим точечный перевод бит
    for (size_t i = 0; i != count && shift; i++) {
      // запомнили старшие биты
      senior_bits = value->mantissa.bits[i] >> (size - shift);
      // сдвинули и записали приходящие биты
      value->mantissa.bits[i] = value->mantissa.bits[i] << shift | junior_bits;
      junior_bits = senior_bits;
    }
  }
}

#include <math.h>

int s21_lazy_left_shift(s21_decimal_lazy* value, s21_decimal_lazy* result,
                        uint32_t shift) {
  int error = 0;
  s21_decimal_lazy res = {0};

  uint8_t senior_bits = 0, junior_bits = 0;
  size_t size = sizeof(*value->mantissa) * CHAR_BIT;
  if (!error) error = s21_lazy_to_lazy_cp(value, &res);

  size_t resize = (int)round((2 * shift + 1) / size);
  resize = (resize > res.size) * resize + (resize <= res.size) * res.size;
  if (!error) error = s21_lazy_resize(&res, resize * 2);

  // определяем кол-во элементов
  size_t count = res.size;

  // Пока сдвиг больше кол-ва бит в 1 элементе старшие биты должны равняться
  // младшим
  while (!error && shift >= size) {
    for (size_t i = count - 1; i != 0; i--)
      res.mantissa[i] = res.mantissa[i - 1];
    // Самые младшие зануляем
    res.mantissa[0] = 0;
    shift -= size;
  }

  // Если сдвиг еще остался, то производим точечный перевод бит
  for (size_t i = 0; !error && i != count && shift; i++) {
    // запомнили старшие биты
    senior_bits = res.mantissa[i] >> (size - shift);
    // сдвинули и записали приходящие биты
    res.mantissa[i] = res.mantissa[i] << shift | junior_bits;
    junior_bits = senior_bits;
  }

  if (!error) error = s21_lazy_to_lazy_cp(&res, result);
  s21_lazy_destroy(&res);

  return error;
}

// int s21_lazy_right_shift(s21_decimal_lazy* value, uint16_t shift) {
//   int error = 0;

//   return error;
// }