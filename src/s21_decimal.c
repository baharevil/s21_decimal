#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>


s21_uint96_t add_uint96_v1(s21_uint96_t x, s21_uint96_t y)
{
    s21_uint96_t result = {0};
    unsigned int carry = 0;
    int i = sizeof(x.value)/sizeof(x.value[0]);
    /* Start from LSB */
    while(i--)
    {
        // Считаем в 64 битной точности
        uint64_t tmp = (uint64_t)(x.value[i] + y.value[i] + carry);
        // Записываем в 32 бита отбрасывая хвост в 32 бита
        result.value[i] = (uint32_t)tmp;
        /* Запоминаем перенос (хвост) */
        carry = tmp >> 32;
    }
    return result;
}

s21_uint96_t add_uint96_v2(s21_uint96_t x, s21_uint96_t y)
{
    s21_uint96_t result = {0};
    int i = sizeof(x.value)/sizeof(x.value[0]);
    /* Start from LSB */
    while(i--)
    {
      unsigned carry = 0;
      while(y.value[i] != 0x00)
      {
        /*Выставить флаг под разрядами с установленными битами.*/
        carry	= (x.value[i] & y.value[i]);
        /*Снять с первого слагаемого биты, разряд по которым уже учтен.*/
        x.value[i] = x.value[i] ^ y.value[i];
        /*Перенос переводится в старший разряд.*/
        y.value[i] = (carry << 1);
	    }
    }
    result = x;
    return result;
}

void print_uint96(char *str, s21_uint96_t x)
{
    printf("%s = %08x%08x%08x\r\n", str, x.value[0], x.value[1], x.value[2]);
}

void bin_print(unsigned int length, void *pointer, int options) {
  int rem = length % 8;
  int full = length / 8;
  int loops = full + !!rem;
  int last = rem ? full : 0;

  for (int i = 0; i < loops; i++) {
    for (unsigned int j = 1 << 7, z = rem; j > 0; j >>= 1) {
      if (i == last && rem)
        if (z-- == 0) continue;
      printf("%d", !!(*((char *)pointer + i) & j));
    }
    if (options & 1 && i != loops - 1) printf(" ");
  }

  printf("\n");
}

int main() {
  // s21_decimal d = {0};
  
  // Вариант 2 - "Все число сразу"

  unsigned summand = 15;
  printf("  summand: ");
  bin_print(32, &summand, 1);

  unsigned addend = 1; 
  printf("   addend: ");
  bin_print(32, &addend, 1);
  
  /*Перенос.*/
	unsigned carry = 0x00;

	/*Итерировать до тех пор, пока не закончится перенос на старший разряд.*/
	while(addend != 0x00) {
		/*Выставить флаг под разрядами с установленными битами.*/
    carry = (summand & addend);
    printf("    carry: ");
    bin_print(32, &carry, 1);

		/*Снять с первого слагаемого биты, разряд по которым уже учтен.*/
		summand	= summand ^ addend;
    printf("summand_a: ");
    bin_print(32, &summand, 1);

    /*Перенос переводится в старший разряд.*/
		addend = (carry << 1);
    printf(" addend_a: ");
    bin_print(32, &addend, 1);
	}

  printf("result: %u\n", summand);

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

  return 0;
}