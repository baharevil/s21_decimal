#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


s21_uint96_t add_uint96_v1(s21_uint96_t x, s21_uint96_t y)
{
    s21_uint96_t result = {0};
    unsigned int carry = 0;
    int i = sizeof(x.value)/sizeof(x.value[0]);
    /* Start from LSB */
    while(i--)
    {
        uint64_t tmp = (uint64_t)x.value[i] + y.value[i] + carry;    
        result.value[i] = (uint32_t)tmp;
        /* Remember the carry */
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
  s21_decimal dec = {0};
  s21_dec_init(&dec);
  printf("%p\n", dec.data);
  void *p_end = s21_dec_end(&dec);
  printf("%p\n", p_end);
  s21_dec_resize(&dec);
  printf("%p\n", p_end);

  s21_uint96_t x = {{0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_uint96_t y = {{0x00, 0x00, 0xFF}};
  s21_uint96_t r1 = add_uint96_v1(x, y);
  s21_uint96_t r2 = add_uint96_v2(x, y);

  print_uint96("x", x);
  print_uint96("y", y);
  print_uint96("result", r1);
  print_uint96("result", r2);
  // printf("%d\n", *(unsigned char *)p_end);
  s21_dec_destroy(&dec);
  return 0;
}