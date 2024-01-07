#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_uint96(char* str, s21_uint96_t x) {
  printf("%s = %08x%08x%08x\r\n", str, x.bits[0], x.bits[1], x.bits[2]);
}

void s21_decimal_lazy_print(s21_decimal_lazy x) {
  uint16_t size = 0;
  while (size < x.size) {
    printf("%hhu ", *(x.value + size));
    size++;
  }
  printf("\n");
}

void bin_print(unsigned int length, void* pointer, int options) {
  int rem = length % 8;
  int full = length / 8;
  int loops = full + !!rem;
  int last = rem ? full : 0;

  /*
    size: длинна строки с учетом пробелов
    index: точка записи бит в строку
    space: нужно ли вставлять пробел
  */
  int size = length + !!options * (full - 1), index = size - 8, space = 0;
  // Для корректного вывода бит
  char* tmp = calloc(size + 1, sizeof(char));
  // ptr: чтобы не потерять начало строки
  char* ptr = tmp;

  for (int i = 0; i < loops; i++) {
    /*
      j: маска для вывода
      k: доп. индекс
    */
    for (unsigned int j = 1 << 7, z = rem, k = 0; j > 0; j >>= 1, k++) {
      if (i == last && rem)
        if (z-- == 0) continue;
      *(ptr + index + k) = !!(*((char*)pointer + i) & j) + 48;
    }

    space = options && i != loops - 1;
    if (space) *(ptr + index - space) = ' ';

    index -= (8 + space);
  }

  printf("%s\n", tmp);
  if (tmp) free(tmp);
}

void s21_decimal_print(s21_decimal value, char* str) {
  // кол-во бит в 1 элементе
  size_t size = sizeof(value.mantissa.bits[0]) * CHAR_BIT;
  // определяем кол-во элементов
  size_t count = sizeof(value.mantissa.bits) / sizeof(value.mantissa.bits[0]);

  printf("\n\x1b[4;34m%s\x1b[0m", str);

  printf("\n\x1b[1;33m%s\x1b[0m", "sign & exp: ");
  bin_print(sizeof(uint32_t) * CHAR_BIT, &value.exponent, 1);

  for (size_t i = count; i != 0; i--) {
    printf("\x1b[1;33m%8s%lu]: \x1b[0m", "bits[", i - 1);
    bin_print(size, &value.mantissa.bits[i - 1], 1);
  }
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
  s21_decimal value_1 = {{{0x00000001, 0x00000000, 0x00000000}}, {4}};
  // s21_decimal value_2 = {{{0, 0xfffffff, 0xabcdef}}, {0}};
  // s21_decimal result = {0};

  printf("%d\n", s21_search_msb(&value_1));

  // s21_decimal_lazy x  = {0};
  // s21_decimal_lazy y  = {0};
  // s21_decimal_lazy result = {0};

  // x.size = 3;
  // x.value = calloc(sizeof(uint8_t), x.size);
  // *(x.value + 0) = 1;
  // *(x.value + 1) = 2;
  // *(x.value + 2) = 0xff;

  // y.size = 3;
  // y.value = calloc(sizeof(uint8_t), y.size);
  // *(y.value + 0) = 1;
  // *(y.value + 1) = 2;
  // *(y.value + 2) = 0xff;

  // s21_add_lazy(x, y, &result);

  // s21_decimal_lazy_print(result);

  // free (x.value);
  // free (y.value);
  // free (result.value);

  // s21_decimal x = {0};
  // s21_decimal y = {0};
  // s21_decimal result = {0};

  // *(x.value.bits + 0) = 1;
  // *(x.value.bits + 1) = 2;
  // *(x.value.bits + 2) = 0xffffffff;

  // *(y.value.bits + 0) = 1;
  // *(y.value.bits + 1) = 2;
  // *(y.value.bits + 2) = 0xffffffff;

  // s21_add(x, y, &result);

  // print_uint96("result: ", result.value);

  return 0;
}