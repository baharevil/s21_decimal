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
        0   |   18  |    3   |      91
    --------------------------------------
        1   |  400  |   14   |      96
    -------------------------------------
        2   |  400  |   37   |      90
    -------------------------------------
        3   |  400  |   33   |      91
    -------------------------------------
        4   |  400  |  106   |      73
    -------------------------------------
        5   |  400  |   87   |      87
    -------------------------------------
        6   |  400  |  106   |      73
    -------------------------------------
        7   |  400  |  168   |      58
    -------------------------------------
        8   |  400  |  162   |      59
    -------------------------------------
        9   |  164  |   26   |      84
    -------------------------------------
      all   | 3374  |  742   |      78
    -------------------------------------

    real	0m25,809s
    user	0m24,253s
    sys	  0m1,364s

  */

   // -0.0000000000000005
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80100000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -13204693752377.389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x800F0000}};
  s21_decimal result = {{0}};

  int error = 0, code_check = 0;
  error = s21_mul(decimal1, decimal2, &result);

  printf("error: %d, code_check: %d\n", error, code_check);
  s21_decimal_print(&result, "result: ");
  s21_decimal_print(&decimal_check, " check: ");

  return 0;
}