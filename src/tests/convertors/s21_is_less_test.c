#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal_test.h"
#include "s21_decimal.h"

START_TEST(test_less_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_less(decimal1, decimal2);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_less_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_less_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_less_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_less_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_less_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual10) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual11) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1D0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual12) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 40000}};
  s21_decimal decimal2 = {{0, 0, 0, 0x1D0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual13) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C0001}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual14) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x1C8000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual15) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x11C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual16) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual17) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_less_fail_manual18) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x140000}};
  s21_decimal decimal2 = {{-1, 0, 0, 0x401C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

Suite *less_suite0(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=S21_IS_less_0=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_less_fail_manual1);
  tcase_add_test(tc_core, test_less_fail_manual2);
  tcase_add_test(tc_core, test_less_fail_manual3);
  tcase_add_test(tc_core, test_less_fail_manual4);
  tcase_add_test(tc_core, test_less_fail_manual5);
  tcase_add_test(tc_core, test_less_fail_manual6);
  tcase_add_test(tc_core, test_less_fail_manual7);
  tcase_add_test(tc_core, test_less_fail_manual8);
  tcase_add_test(tc_core, test_less_fail_manual9);
  tcase_add_test(tc_core, test_less_fail_manual10);
  tcase_add_test(tc_core, test_less_fail_manual11);
  tcase_add_test(tc_core, test_less_fail_manual12);
  tcase_add_test(tc_core, test_less_fail_manual13);
  tcase_add_test(tc_core, test_less_fail_manual14);
  tcase_add_test(tc_core, test_less_fail_manual15);
  tcase_add_test(tc_core, test_less_fail_manual16);
  tcase_add_test(tc_core, test_less_fail_manual17);
  tcase_add_test(tc_core, test_less_fail_manual18);

  suite_add_tcase(s, tc_core);
  return s;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests all data (automatic)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(test_is_less1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less6) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_less7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less12) {
  // -7922816251426433759354395035
  s21_decimal decimal1 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_is_less13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_is_less55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  int code = s21_is_less(decimal1, decimal2);

  ck_assert_int_eq(code, 0);
}
END_TEST

Suite *less_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=s21_is_less_1=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_is_less1);
  tcase_add_test(tc_core, test_is_less2);
  tcase_add_test(tc_core, test_is_less3);
  tcase_add_test(tc_core, test_is_less4);
  tcase_add_test(tc_core, test_is_less5);
  tcase_add_test(tc_core, test_is_less6);
  tcase_add_test(tc_core, test_is_less7);
  tcase_add_test(tc_core, test_is_less8);
  tcase_add_test(tc_core, test_is_less9);
  tcase_add_test(tc_core, test_is_less10);
  tcase_add_test(tc_core, test_is_less11);
  tcase_add_test(tc_core, test_is_less12);
  tcase_add_test(tc_core, test_is_less13);
  tcase_add_test(tc_core, test_is_less14);
  tcase_add_test(tc_core, test_is_less15);
  tcase_add_test(tc_core, test_is_less16);
  tcase_add_test(tc_core, test_is_less17);
  tcase_add_test(tc_core, test_is_less18);
  tcase_add_test(tc_core, test_is_less19);
  tcase_add_test(tc_core, test_is_less20);
  tcase_add_test(tc_core, test_is_less21);
  tcase_add_test(tc_core, test_is_less22);
  tcase_add_test(tc_core, test_is_less23);
  tcase_add_test(tc_core, test_is_less24);
  tcase_add_test(tc_core, test_is_less25);
  tcase_add_test(tc_core, test_is_less26);
  tcase_add_test(tc_core, test_is_less27);
  tcase_add_test(tc_core, test_is_less28);
  tcase_add_test(tc_core, test_is_less29);
  tcase_add_test(tc_core, test_is_less30);
  tcase_add_test(tc_core, test_is_less31);
  tcase_add_test(tc_core, test_is_less32);
  tcase_add_test(tc_core, test_is_less33);
  tcase_add_test(tc_core, test_is_less34);
  tcase_add_test(tc_core, test_is_less35);
  tcase_add_test(tc_core, test_is_less36);
  tcase_add_test(tc_core, test_is_less37);
  tcase_add_test(tc_core, test_is_less38);
  tcase_add_test(tc_core, test_is_less39);
  tcase_add_test(tc_core, test_is_less40);
  tcase_add_test(tc_core, test_is_less41);
  tcase_add_test(tc_core, test_is_less42);
  tcase_add_test(tc_core, test_is_less43);
  tcase_add_test(tc_core, test_is_less44);
  tcase_add_test(tc_core, test_is_less45);
  tcase_add_test(tc_core, test_is_less46);
  tcase_add_test(tc_core, test_is_less47);
  tcase_add_test(tc_core, test_is_less48);
  tcase_add_test(tc_core, test_is_less49);
  tcase_add_test(tc_core, test_is_less50);
  tcase_add_test(tc_core, test_is_less51);
  tcase_add_test(tc_core, test_is_less52);
  tcase_add_test(tc_core, test_is_less53);
  tcase_add_test(tc_core, test_is_less54);
  tcase_add_test(tc_core, test_is_less55);

  suite_add_tcase(s, tc_core);
  return s;
}
