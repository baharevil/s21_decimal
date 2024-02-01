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
  // s21_decimal value_1 = {{0xf, 0x0, 0x0, 0x80000000}};
  // s21_decimal value_2 = {{0xf, 0x0, 0x0, 0x80010000}};
  // s21_decimal dec_result = {0};

  // s21_add(value_1, value_2, &dec_result);
  // s21_decimal_print(&dec_result, "add: ");

  // s21_truncate(dec_result, &dec_result);
  // s21_decimal_print(&dec_result, "add: ");

  //2583 - A17
  //1010 0001 0111
  //258 - 1 02
  //1 0000 0010
  s21_decimal value_2 = {{0x00000A17, 0x0, 0x0, 0x00010000}}; 
  s21_decimal_print(&value_2, "value_2: "); 
  s21_decimal dec_result = {0}; 
  s21_decimal_lazy value_l; 
  s21_decimal_lazy value_rounded; 
  s21_lazy_init(&value_l, &value_2); 
  s21_lazy_init(&value_rounded, NULL); 
  s21_truncate_lazy(&value_l, &value_rounded); 
  s21_from_lazy_to_decimal(&value_rounded, &dec_result); 
  s21_decimal_print(&dec_result, "result: ");
  return 0;
}