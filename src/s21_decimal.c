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

  // s21_decimal result = {{0}};

  // // 2
  // s21_decimal decimal1 = {{0x2, 0x0, 0x0, 0x0}};
  // // 1.2640938749860586450804312205
  // s21_decimal decimal2 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // // 1.5821609767882606564463392905
  // s21_decimal check = {{0x8B80B889, 0x20B8279E, 0x331F5430, 0x1C0000}};

  // int error = 0, code_check = 0;
  // error = s21_div(decimal1, decimal2, &result);

  // printf("error: %d, code_check: %d\n", error, code_check);
  // printf("is_equal: %d\n", s21_is_equal(result, check));

  // s21_decimal_print(&result, "result: ");
  // s21_decimal_print(&check, " check: ");

  // -2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
  int check = -2147483648, result = 0;
  int error = 0;
  
  error = s21_from_decimal_to_int(decimal, &result);

  printf("error:  %d\n", error);
  printf("is_equal: %d\n", check == result);
  printf("check:  %d\n", check);
  printf("result: %d\n", result);

  return 0;
}