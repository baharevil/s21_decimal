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

    №   |  all  |  fail  |  % complete
    ----------------------------------
    1   |   18  |    1   |     94
    ---------------------------------
    2   |  400  |   86   |     78
    ---------------------------------
    3   |  400  |  148   |     63
    ---------------------------------
    4   |  400  |  241   |     39
    ---------------------------------
    5   |  400  |  160   |     60
    ---------------------------------
    all | 1618  |  636   |     61
    ---------------------------------

    real	0m1,821s
    user	0m1,465s
    sys	0m0,250s

  */

  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};
  s21_decimal result = {{0}};

  int error = 0;
  error = s21_add(decimal1, decimal2, &result);

  printf("error: %d\n", error);
  s21_decimal_print(&result, "result: ");
  s21_decimal_print(&check, " check: ");

  // 242326349807616
  // 15499999999
  return 0;
}