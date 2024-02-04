#include <stdio.h>
#include <stdlib.h>

#include "s21_decimal.h"
#include "../s21_decimal_test.h"

START_TEST(test_equal_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_equal_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,40000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_equal_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_equal(decimal1, decimal2);  

  ck_assert_int_eq(code, 0);
}
END_TEST

Suite *equal_suite0(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=S21_IS_EQUAL_0=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_equal_fail_manual1);
  tcase_add_test(tc_core, test_equal_fail_manual2);
  tcase_add_test(tc_core, test_equal_fail_manual3);
  tcase_add_test(tc_core, test_equal_fail_manual4);
  tcase_add_test(tc_core, test_equal_fail_manual5);
  tcase_add_test(tc_core, test_equal_fail_manual6);
  tcase_add_test(tc_core, test_equal_fail_manual7);
  tcase_add_test(tc_core, test_equal_fail_manual8);
  tcase_add_test(tc_core, test_equal_fail_manual9);
  tcase_add_test(tc_core, test_equal_fail_manual10);
  tcase_add_test(tc_core, test_equal_fail_manual11);
  tcase_add_test(tc_core, test_equal_fail_manual12);
  tcase_add_test(tc_core, test_equal_fail_manual13);
  tcase_add_test(tc_core, test_equal_fail_manual14);
  tcase_add_test(tc_core, test_equal_fail_manual15);
  tcase_add_test(tc_core, test_equal_fail_manual16);
  tcase_add_test(tc_core, test_equal_fail_manual17);

  suite_add_tcase(s, tc_core);
  return s;
}

// void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
// //   int code = s21_add(decimal1, decimal2, &result);

// #if defined(__DEBUG)
//   printf("---------------------------------\n");
//   printf("\n\nTests:\n");
//   s21_print_decimal_bits(decimal1);
//   s21_print_decimal_string(decimal1);
//   s21_print_decimal_bits(decimal2);
//   s21_print_decimal_string(decimal2);
//   printf("\ncheck:\n");
//   s21_print_decimal_bits(check);
//   s21_print_decimal_string(check);
//   printf("\nres:\n");
//   s21_print_decimal_bits(result);
//   s21_print_decimal_string(result);
//   printf("---------------------------------\n\n\n\n");
// #endif

//   ck_assert_int_eq(s21_is_equal(result, check), 1);
//   ck_assert_int_eq(code, 0);
// }

// void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
// //   int code = s21_add(decimal1, decimal2, &result);

// #if defined(__DEBUG)
//   printf("---------------------------------\n");
//   printf("\n\nTests:\n");
//   s21_print_decimal_bits(decimal1);
//   s21_print_decimal_string(decimal1);
//   s21_print_decimal_bits(decimal2);
//   s21_print_decimal_string(decimal2);
//   printf("Check: %d\n", check);
//   printf("Result: %d\n", code);
//   printf("---------------------------------\n\n\n\n");
// #endif

//   ck_assert_int_eq(code, check);
// }