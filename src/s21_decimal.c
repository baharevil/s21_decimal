#include "s21_decimal.h"

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_decimal_lazy_print(s21_decimal_lazy *x) {
  uint16_t size = 0;
  while (size < x->size) {
    // printf("%hhu ", *(x->mantissa + size));
    printf("%hhu ", *(x->mantissa + size));
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
  // s21_decimal value_1 = {{0xff, 0x0, 0x0, 0x0}};
  // value_1.exponent.bits.exponent = 1;
  s21_decimal value_2 = {{0x7fffffff, 0x0, 0x0, 0x00000000}};
  s21_decimal_print(&value_2, "value_2: ");

  int i = 0, error = 0;
  error = s21_from_decimal_to_int(value_2, &i);

  printf("%d\n", i);
  printf("%d\n", error);

  return 0;
}