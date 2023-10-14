#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_uint96(char *str, s21_uint96_t x) {
  printf("%s = %08x%08x%08x\r\n", str, x.bits[0], x.bits[1], x.bits[2]);
}

void s21_decimal_lazy_print(s21_decimal_lazy x) {
  uint16_t size = 0;
  while (size < x.size)
  {
    printf("%hhu ", *(x.value + size));
    size++;
  }
  printf("\n");
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
  s21_decimal_lazy x  = {0};
  s21_decimal_lazy y  = {0};
  s21_decimal_lazy result = {0};
  
  x.size = 3;
  x.value = calloc(sizeof(uint8_t), x.size);
  *(x.value + 0) = 1;
  *(x.value + 1) = 2;
  *(x.value + 2) = 0xff;

  y.size = 3;
  y.value = calloc(sizeof(uint8_t), y.size);
  *(y.value + 0) = 1;
  *(y.value + 1) = 2;
  *(y.value + 2) = 0xff;

  s21_add_lazy(x, y, &result);

  s21_decimal_lazy_print(result);

  free (x.value);
  free (y.value);
  free (result.value);

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