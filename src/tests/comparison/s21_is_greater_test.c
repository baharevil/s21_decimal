#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal_test.h"
#include "s21_decimal.h"

START_TEST(test_greater_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater(decimal1, decimal2);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_greater_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 40000}};
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_greater_fail_manual18) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *greater_suite0(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=S21_IS_GREATER_0=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_greater_fail_manual1);
  tcase_add_test(tc_core, test_greater_fail_manual2);
  tcase_add_test(tc_core, test_greater_fail_manual3);
  tcase_add_test(tc_core, test_greater_fail_manual4);
  tcase_add_test(tc_core, test_greater_fail_manual5);
  tcase_add_test(tc_core, test_greater_fail_manual6);
  tcase_add_test(tc_core, test_greater_fail_manual7);
  tcase_add_test(tc_core, test_greater_fail_manual8);
  tcase_add_test(tc_core, test_greater_fail_manual9);
  tcase_add_test(tc_core, test_greater_fail_manual10);
  tcase_add_test(tc_core, test_greater_fail_manual11);
  tcase_add_test(tc_core, test_greater_fail_manual12);
  tcase_add_test(tc_core, test_greater_fail_manual13);
  tcase_add_test(tc_core, test_greater_fail_manual14);
  tcase_add_test(tc_core, test_greater_fail_manual15);
  tcase_add_test(tc_core, test_greater_fail_manual16);
  tcase_add_test(tc_core, test_greater_fail_manual17);
  tcase_add_test(tc_core, test_greater_fail_manual18);

  suite_add_tcase(s, tc_core);
  return s;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests all data (automatic)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(test_is_greater1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater6) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater12) {
  // -7922816251426433759354395035
  s21_decimal decimal1 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_greater48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_greater55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  int code = s21_is_greater(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

Suite *greater_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=s21_is_GREATER_1=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_greater1);
  tcase_add_test(tc_core, test_is_greater2);
  tcase_add_test(tc_core, test_is_greater3);
  tcase_add_test(tc_core, test_is_greater4);
  tcase_add_test(tc_core, test_is_greater5);
  tcase_add_test(tc_core, test_is_greater6);
  tcase_add_test(tc_core, test_is_greater7);
  tcase_add_test(tc_core, test_is_greater8);
  tcase_add_test(tc_core, test_is_greater9);
  tcase_add_test(tc_core, test_is_greater10);
  tcase_add_test(tc_core, test_is_greater11);
  tcase_add_test(tc_core, test_is_greater12);
  tcase_add_test(tc_core, test_is_greater13);
  tcase_add_test(tc_core, test_is_greater14);
  tcase_add_test(tc_core, test_is_greater15);
  tcase_add_test(tc_core, test_is_greater16);
  tcase_add_test(tc_core, test_is_greater17);
  tcase_add_test(tc_core, test_is_greater18);
  tcase_add_test(tc_core, test_is_greater19);
  tcase_add_test(tc_core, test_is_greater20);
  tcase_add_test(tc_core, test_is_greater21);
  tcase_add_test(tc_core, test_is_greater22);
  tcase_add_test(tc_core, test_is_greater23);
  tcase_add_test(tc_core, test_is_greater24);
  tcase_add_test(tc_core, test_is_greater25);
  tcase_add_test(tc_core, test_is_greater26);
  tcase_add_test(tc_core, test_is_greater27);
  tcase_add_test(tc_core, test_is_greater28);
  tcase_add_test(tc_core, test_is_greater29);
  tcase_add_test(tc_core, test_is_greater30);
  tcase_add_test(tc_core, test_is_greater31);
  tcase_add_test(tc_core, test_is_greater32);
  tcase_add_test(tc_core, test_is_greater33);
  tcase_add_test(tc_core, test_is_greater34);
  tcase_add_test(tc_core, test_is_greater35);
  tcase_add_test(tc_core, test_is_greater36);
  tcase_add_test(tc_core, test_is_greater37);
  tcase_add_test(tc_core, test_is_greater38);
  tcase_add_test(tc_core, test_is_greater39);
  tcase_add_test(tc_core, test_is_greater40);
  tcase_add_test(tc_core, test_is_greater41);
  tcase_add_test(tc_core, test_is_greater42);
  tcase_add_test(tc_core, test_is_greater43);
  tcase_add_test(tc_core, test_is_greater44);
  tcase_add_test(tc_core, test_is_greater45);
  tcase_add_test(tc_core, test_is_greater46);
  tcase_add_test(tc_core, test_is_greater47);
  tcase_add_test(tc_core, test_is_greater48);
  tcase_add_test(tc_core, test_is_greater49);
  tcase_add_test(tc_core, test_is_greater50);
  tcase_add_test(tc_core, test_is_greater51);
  tcase_add_test(tc_core, test_is_greater52);
  tcase_add_test(tc_core, test_is_greater53);
  tcase_add_test(tc_core, test_is_greater54);
  tcase_add_test(tc_core, test_is_greater55);

  suite_add_tcase(s, tc_core);
  return s;
}
