#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_decimal_lazy_print(s21_decimal_lazy *x, char *str) {
  printf("\n%s", str);

  uint16_t size = 0;
  while (size < x->size) {
    // printf("%hhu ", *(x->mantissa + size));
    printf("%hhx ", *(x->mantissa + size));
    size++;
  }
  printf(" exp: %u", x->exponent);
  printf(" sign: %u\n", x->sign);
}

void s21_decimal_print(s21_decimal *x, char *str) {
  printf("\n%s", str);

  uint8_t size = 0;
  while (size < sizeof(x->mantissa.bytes)) {
    printf("%hhx ", *(x->mantissa.bytes + size));
    size++;
  }

  printf(" exp: %u", x->exponent.bits.exponent);
  printf(" sign: %u\n", x->exponent.bits.sign);
}

// Исслеованеи по бэктрейсу
#include <execinfo.h>

void handler(char *caller) {
  void *array[10];
  size_t size;
  printf("Stack Trace Start for %s\n", caller);
  size = backtrace(array, 10);
  backtrace_symbols_fd(array, size, 2);
  printf("Stack Trace End\n");
}

void car() {
  handler("car()");
  printf("Continue Execution");
}
void baz() { car(); }

void bar() { baz(); }
void foo() { bar(); }

int main() {
  /*
    s21_add

    № suite |  all  |  fail  |  % complete
    -------------------------------------
        0   |   18  |    0   |     100
    --------------------------------------
        1   |  400  |    0   |     100
    -------------------------------------
        2   |  400  |    0   |      97
    -------------------------------------
        3   |  400  |    0   |      99
    -------------------------------------
        4   |  400  |    0   |      96
    -------------------------------------
        5   |  400  |    0   |      96
    -------------------------------------
        6   |  400  |    0   |      97
    -------------------------------------
        7   |  400  |    0   |      97
    -------------------------------------
        8   |  400  |    0   |      99
    -------------------------------------
        9   |  400  |    0   |      95
    -------------------------------------
        all | 3618  |    0   |      95
    -------------------------------------

    real	0m20,328s
    user	0m19,139s
    sys	  0m1,115s

  */

  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -0.0000000000000000000000000000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x801C0000}};
  s21_decimal result = {{0}};

  int error = 0;
  error = s21_sub(decimal1, decimal2, &result);

  printf("error: %d\n", error);
  s21_decimal_print(&result, "result: ");
  s21_decimal_print(&check, " check: ");

  return 0;
}