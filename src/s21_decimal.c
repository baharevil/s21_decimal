#include "s21_decimal.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
  s21_decimal value = {0};
  uint32_t bits[4] = {0};

  for (size_t i = 0; i < 4; i++) *(bits + i) = 0b11111111;

  value.i = *(uint128_t *)bits;

  bin_print(sizeof(s21_decimal) * CHAR_BIT, &(value.i), 1);

  return 0;
}