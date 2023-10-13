#include "s21_decimal.h"

/*
    Арифметические операторы. Сумма.
    Функции возвращают код ошибки:

    0 - OK
    1 - число слишком велико или равно бесконечности
    2 - число слишком мало или равно отрицательной бесконечности
    3 - деление на 0
*/

s21_uint96_t s21_add_uint96_v1(s21_uint96_t x, s21_uint96_t y) {
  s21_uint96_t result = {0};
  unsigned carry = 0;
  unsigned short i = sizeof(x.bits) / sizeof(x.bits[0]);

  while (i--) {
    // Считаем в 64 битной точности
    uint64_t tmp = (uint64_t)(x.bits[i] + y.bits[i] + carry);
    // Записываем в 32 бита отбрасывая хвост в 32 бита
    result.bits[i] = (uint32_t)tmp;
    /* Запоминаем перенос (хвост) */
    carry = tmp >> 32;
  }
  return result;
}

uint32_t s21_add_uint32_t(uint32_t *x, uint32_t *y) {
  unsigned long carry = 0;

  while (*y) {
    carry = *x & *y;
    *x = *x ^ *y;
    *y = carry << 1;
  }
  carry >>= 32;
  return (uint32_t)carry;
}

s21_uint96_t s21_add_uint96_v2(s21_uint96_t x, s21_uint96_t y) {
  s21_uint96_t result = {0};
  short i = sizeof(s21_uint96_t) / sizeof(uint32_t);
  unsigned carry = 0;

  while (i--) {
    carry = s21_add_uint32_t(&x.bits[i], &y.bits[i]);
    if (carry)
      carry = s21_add_uint32_t(
          &y.bits[(i - 1 >= 0) * (i - 1) + (i - 1 < 0) * 0], &carry);
  }
  result = x;
  return result;
}

// Здесь на выбор есть 2 функции: Простая и рабочая s21_add_uint96_v1() и
// полностью бинарная s21_add_uint96_v2()
//TODO: Перенос carry между 
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  result->value = s21_add_uint96_v2(value_1.value, value_2.value);

  return error;
}

// Вариант 1 - "В столбик"
// unsigned c1 = 255;
// unsigned c2 = 255;
// unsigned result = 0;
// unsigned carry = 0;
// unsigned mask = 1;
// unsigned one_bit_c1 = 0;
// unsigned one_bit_c2 = 0;
// unsigned rank = 0;
// while (c1 | c2) {
//   carry = 0;
//   printf("     mask: ");
//   bin_print(8, &mask, 0);
//   printf("       c1: ");
//   bin_print(8, &c1, 0);
//   printf("       c2: ");
//   bin_print(8, &c2, 0);

//   printf("c1 & mask: ");
//   one_bit_c1 = c1 & mask;
//   bin_print(8, &one_bit_c1, 0);

//   printf("c2 & mask: ");
//   one_bit_c2 = c2 & mask;
//   bin_print(8, &one_bit_c2, 0);

//   carry = (one_bit_c1 & one_bit_c2);
//   printf("    carry: ");
//   bin_print(8, &carry, 0);
//   result += (one_bit_c1 | one_bit_c2) << rank;
//   result += (carry << rank);
//   printf("   result: ");
//   bin_print(8, &result, 0);
//   c1 = c1 >> 1;
//   c2 = c2 >> 1;
//   printf("\n");
//   rank++;
// }
// printf("   result: %d\n", result);
