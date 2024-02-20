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
    ----------======TESTS======-----------
    --------------------------------------
            function: s21_mul()
    --------------------------------------
    № suite |  all  |  fail  |  % complete
    --------------------------------------
        0   |   37  |    0   |      100
    ---------------------------------------
        1   |  400  |    0   |      100
    --------------------------------------
        2   |  400  |    4   |      99
    --------------------------------------
        3   |  400  |    8   |      98
    --------------------------------------
        4   |  400  |    4   |      99
    --------------------------------------
        5   |  400  |    4   |      99
    --------------------------------------
        6   |  400  |    2   |      99
    --------------------------------------
        7   |  400  |   44   |      89
    --------------------------------------
        8   |  400  |   12   |      97
    --------------------------------------
        9   |  164  |    0   |      100
    --------------------------------------
      all   | 3401  |   78   |      98
    --------------------------------------
    ----------======TESTS======-----------

    -----------======TIME======-----------
           ALL_TESTS  48269
                real	0m5,212s
                user	0m2,117s
                sys	  0m3,016s
    -----------======TIME======-----------

    ---------======VALGRIND======---------
      HEAP SUMMARY: 
      in use 
      at exit:       0 bytes in 0 blocks
      total 
      heap usage:    4,288,793 allocs, 
                     4,288,793 frees, 
                     665,801,084 bytes
      ERROR SUMMARY: 0 errors from 0 contexts 
                     (suppressed: 0 from 0)
    ---------======VALGRIND======---------

  */

  s21_decimal result = {{0}};

  // 7.922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x1B0000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 11.884224377139650639031592551
  s21_decimal check = {{0x66666667, 0x66666666, 0x26666666, 0x1B0000}};

  int error = 0, code_check = 0;
  error = s21_add(decimal1, decimal2, &result);

  printf("error: %d, code_check: %d\n", error, code_check);
  printf("is_equal: %d\n", s21_is_equal(result, check));

  s21_decimal_print(&result, "result: ");
  s21_decimal_print(&check, " check: ");

  return 0;
}