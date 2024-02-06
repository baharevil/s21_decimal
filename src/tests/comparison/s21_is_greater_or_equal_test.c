#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal_test.h"
#include "s21_decimal.h"

START_TEST(test_greater_or_equal_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 40000}};
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_or_equal_fail_manual18) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *greater_or_equal_suite0(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=S21_IS_GREATER_OR_EQUAL_0=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual1);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual2);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual3);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual4);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual5);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual6);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual7);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual8);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual9);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual10);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual11);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual12);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual13);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual14);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual15);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual16);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual17);
  tcase_add_test(tc_core, test_greater_or_equal_fail_manual18);

  suite_add_tcase(s, tc_core);
  return s;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests all data (automatic)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(test_is_greater_or_equal1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal6) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal12) {
  // -7922816251426433759354395035
  s21_decimal decimal1 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  int code = s21_is_greater_or_equal(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *greater_or_equal_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=S21_IS_GREATER_OR_EQUAL_1=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_greater_or_equal1);
  tcase_add_test(tc_core, test_is_greater_or_equal2);
  tcase_add_test(tc_core, test_is_greater_or_equal3);
  tcase_add_test(tc_core, test_is_greater_or_equal4);
  tcase_add_test(tc_core, test_is_greater_or_equal5);
  tcase_add_test(tc_core, test_is_greater_or_equal6);
  tcase_add_test(tc_core, test_is_greater_or_equal7);
  tcase_add_test(tc_core, test_is_greater_or_equal8);
  tcase_add_test(tc_core, test_is_greater_or_equal9);
  tcase_add_test(tc_core, test_is_greater_or_equal10);
  tcase_add_test(tc_core, test_is_greater_or_equal11);
  tcase_add_test(tc_core, test_is_greater_or_equal12);
  tcase_add_test(tc_core, test_is_greater_or_equal13);
  tcase_add_test(tc_core, test_is_greater_or_equal14);
  tcase_add_test(tc_core, test_is_greater_or_equal15);
  tcase_add_test(tc_core, test_is_greater_or_equal16);
  tcase_add_test(tc_core, test_is_greater_or_equal17);
  tcase_add_test(tc_core, test_is_greater_or_equal18);
  tcase_add_test(tc_core, test_is_greater_or_equal19);
  tcase_add_test(tc_core, test_is_greater_or_equal20);
  tcase_add_test(tc_core, test_is_greater_or_equal21);
  tcase_add_test(tc_core, test_is_greater_or_equal22);
  tcase_add_test(tc_core, test_is_greater_or_equal23);
  tcase_add_test(tc_core, test_is_greater_or_equal24);
  tcase_add_test(tc_core, test_is_greater_or_equal25);
  tcase_add_test(tc_core, test_is_greater_or_equal26);
  tcase_add_test(tc_core, test_is_greater_or_equal27);
  tcase_add_test(tc_core, test_is_greater_or_equal28);
  tcase_add_test(tc_core, test_is_greater_or_equal29);
  tcase_add_test(tc_core, test_is_greater_or_equal30);
  tcase_add_test(tc_core, test_is_greater_or_equal31);
  tcase_add_test(tc_core, test_is_greater_or_equal32);
  tcase_add_test(tc_core, test_is_greater_or_equal33);
  tcase_add_test(tc_core, test_is_greater_or_equal34);
  tcase_add_test(tc_core, test_is_greater_or_equal35);
  tcase_add_test(tc_core, test_is_greater_or_equal36);
  tcase_add_test(tc_core, test_is_greater_or_equal37);
  tcase_add_test(tc_core, test_is_greater_or_equal38);
  tcase_add_test(tc_core, test_is_greater_or_equal39);
  tcase_add_test(tc_core, test_is_greater_or_equal40);
  tcase_add_test(tc_core, test_is_greater_or_equal41);
  tcase_add_test(tc_core, test_is_greater_or_equal42);
  tcase_add_test(tc_core, test_is_greater_or_equal43);
  tcase_add_test(tc_core, test_is_greater_or_equal44);
  tcase_add_test(tc_core, test_is_greater_or_equal45);
  tcase_add_test(tc_core, test_is_greater_or_equal46);
  tcase_add_test(tc_core, test_is_greater_or_equal47);
  tcase_add_test(tc_core, test_is_greater_or_equal48);
  tcase_add_test(tc_core, test_is_greater_or_equal49);
  tcase_add_test(tc_core, test_is_greater_or_equal50);
  tcase_add_test(tc_core, test_is_greater_or_equal51);
  tcase_add_test(tc_core, test_is_greater_or_equal52);
  tcase_add_test(tc_core, test_is_greater_or_equal53);
  tcase_add_test(tc_core, test_is_greater_or_equal54);
  tcase_add_test(tc_core, test_is_greater_or_equal55);

  suite_add_tcase(s, tc_core);
  return s;
}
