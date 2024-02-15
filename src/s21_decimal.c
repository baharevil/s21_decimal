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
        1   |  400  |    2   |      99
    -------------------------------------
        2   |  400  |   10   |      97
    -------------------------------------
        3   |  400  |    3   |      99
    -------------------------------------
        4   |  400  |    3   |      99
    -------------------------------------
        5   |  400  |    7   |      98
    -------------------------------------
        6   |  400  |   10   |      97
    -------------------------------------
        7   |  400  |    3   |      99
    -------------------------------------
        8   |  400  |    5   |      98
    -------------------------------------
        9   |  400  |   14   |      96
    -------------------------------------
        all | 3618  |   57   |      98
    -------------------------------------

    real	0m20,446s
    user	0m19,692s
    sys	  0m0,551s
  */

  /*
    7922816251426433759354395033.000000000000000000
  -                  49704001422.391670881925172831
    -----------------------------------------------
    7922816251426433709650393610.608329118074827169
    7922816251426433709650393610.6

    in s21_lazy_to_decimal()
    --------------------------------------------------------
    tmp_v     = 7922816251426433709650393610.6
    src       = 7922816251426433709650393610.608329118074827169
    carry     =                             .008329118074827169
    lazy_five =                             .005000000000000000
    lazy_five =                             .050000000000000000 - а должно таким
  быть
    --------------------------------------------------------
  */
  // 1.2640938749860586450804312205
  s21_decimal decimal1 = {{0x1888888D, 0xBE250261, 0x28D856E6, 0x1C0000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 0.6320469374930293225402156102
  // 0.6320469374930293225402156102
  s21_decimal check = {{0x8C444446, 0x5F128130, 0x146C2B73, 0x1C0000}};
  s21_decimal result = {{0}};

  int error = 0;
  error = s21_div(decimal1, decimal2, &result);

  printf("error: %d\n", error);
  s21_decimal_print(&result, "result: ");
  s21_decimal_print(&check, " check: ");

  return 0;
}