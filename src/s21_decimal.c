#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void s21_decimal_lazy_print(s21_decimal_lazy* x) {
  uint16_t size = 0;
  while (size < x->size) {
    printf("%hhu ", *(x->mantissa + size));
    size++;
  }
  printf("\n");
}

void s21_decimal_right_shift(s21_decimal* value, uint32_t shift) {
  // старшие и младшие биты
  uint32_t senior_bits = 0, junior_bits = 0;
  // кол-во бит в 1 элементе
  size_t size = sizeof(value->mantissa.bits[0]) * CHAR_BIT;
  // определяем кол-во элементов
  size_t count = sizeof(value->mantissa.bits) / sizeof(value->mantissa.bits[0]);

  // максимально допустимый сдвиг == size * count - 1 бит
  // если больше, то ничего не должно произойти
  if (shift > size * count - 1) return;

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

void s21_decimal_left_shift(s21_decimal* value, uint32_t shift) {
  // старшие и младшие биты
  uint32_t senior_bits = 0, junior_bits = 0;
  // кол-во бит в 1 элементе
  size_t size = sizeof(value->mantissa.bits[0]) * CHAR_BIT;
  // определяем кол-во элементов
  size_t count = sizeof(value->mantissa.bits) / sizeof(value->mantissa.bits[0]);

  // максимально допустимый сдвиг == 95 бит
  // если больше, то ничего не должно произойти
  if (shift > size * count - 1) return;

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

int main() {
  s21_decimal value_1 = {{{0x00000111, 0x00000000, 0x00000000}}, {4}};
  // s21_decimal value_2 = {{{0, 0xfffffff, 0xabcdef}}, {0}};
  // s21_decimal result = {0};

  // s21_decimal_lazy x  = {0};
  // s21_decimal_lazy y  = {0};
  s21_decimal_lazy result = {0};

  s21_dec_to_lazy_cp(&value_1, &result);
  // s21_lazy_to_lazy_cp(&x, &result);

  s21_decimal_lazy_print(&result);
  s21_div_lazy_to_10(&result);
  s21_decimal_lazy_print(&result);
  // free (x.mantissa);
  // free (y.value);
  free(result.mantissa);

  return 0;
}