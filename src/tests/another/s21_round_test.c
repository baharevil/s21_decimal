#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal_test.h"
#include "s21_decimal.h"

void test_round(s21_decimal decimal1, s21_decimal decim_chk, int code_chk) {
  s21_decimal result = {0};
  int code = s21_round(decimal1, &result);
  ck_assert_int_eq(code, code_chk);
  ck_assert_int_eq(s21_is_equal(result, decim_chk), 1);
}

START_TEST(test_round_fail_manual1) {
  // 79228162514264337593.543950335
  // 4 4b82fa09 b5a52cba
  // ba2ca5b5 09fa824b 4
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  s21_decimal check = {{0xb5a52cba, 0x4b82fa09, 0x4, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 1000000000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{-1, 0x0, 0x0, 0x1D0000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x1D0000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0x0, 0x0, 0x1C0001}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0x0, 0x0, 0x1C8000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual10) {
  // 792281625142643375935439.50335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
  // a7c5 ac471b47 84230fd0
  s21_decimal check = {{0x84230fd0, 0xac471b47, 0xa7c5, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual11) {
  // 792281625142643375935.43950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  // 1873bf3f f31dc461 2a
  s21_decimal check = {{0x1873bf3f, 0xf31dc461, 0x2a, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual12) {
  // 7922816251426433759354395.0335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  // 295e9e1b bac710cb 68db8
  // 6 8db8 bac7 10cb 295e 9e1b
  s21_decimal check = {{0x295e9e1b, 0xbac710cb, 0x68db8, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual13) {
  // 792281625142643375935.43950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  // 1873bf3f f31dc461 2a
  s21_decimal check = {{0x1873bf3f, 0xf31dc461, 0x2a, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual14) {
  // 79228162514264337593543950.335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  // 9db22d0e 4bc6a7ef 418937
  s21_decimal check = {{0x9db22d0e, 0x4bc6a7ef, 0x418937, 0x0}};
  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round_fail_manual15) {
  // 792281625142643375935439.50335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50010}};
  // a7c5 ac471b47 84230fd0
  s21_decimal check = {0};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual16) {
  // 79228162514264337593543950335
  // степень 6 (что корректно), но биты 5-12 не нули
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60FF0}};
  s21_decimal check = {0};
  test_round(decimal1, check, 1);
}
END_TEST

START_TEST(test_round_fail_manual17) {
  // 792281.62514264337593543950335
  // степень 6 (что корректно), но биты 24-27 не нули
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF060000}};
  s21_decimal check = {0};
  test_round(decimal1, check, 1);
}
END_TEST

Suite *round_suite0(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=S21_ROUND_0=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_round_fail_manual1);
  tcase_add_test(tc_core, test_round_fail_manual2);
  tcase_add_test(tc_core, test_round_fail_manual3);
  tcase_add_test(tc_core, test_round_fail_manual4);
  tcase_add_test(tc_core, test_round_fail_manual5);
  tcase_add_test(tc_core, test_round_fail_manual6);
  tcase_add_test(tc_core, test_round_fail_manual7);
  tcase_add_test(tc_core, test_round_fail_manual8);
  tcase_add_test(tc_core, test_round_fail_manual9);
  tcase_add_test(tc_core, test_round_fail_manual10);
  tcase_add_test(tc_core, test_round_fail_manual11);
  tcase_add_test(tc_core, test_round_fail_manual12);
  tcase_add_test(tc_core, test_round_fail_manual13);
  tcase_add_test(tc_core, test_round_fail_manual14);
  tcase_add_test(tc_core, test_round_fail_manual15);
  tcase_add_test(tc_core, test_round_fail_manual16);
  tcase_add_test(tc_core, test_round_fail_manual17);

  suite_add_tcase(s, tc_core);
  return s;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests all data (automatic)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(test_round1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395035
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.704754779197847983445
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 26409387
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -26409387
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7.9228162514264337593543950335
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7.9228162514264337593543950335
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x0}};
  // 8
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -8
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 3.6336660283201536
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

START_TEST(test_round55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -3.6336660283201536
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_round(decimal1, check, 0);
}
END_TEST

Suite *round_suite1(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\x1b[1;33m-=S21_ROUND_1=-\x1b[0m");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_round1);
  tcase_add_test(tc_core, test_round2);
  tcase_add_test(tc_core, test_round3);
  tcase_add_test(tc_core, test_round4);
  tcase_add_test(tc_core, test_round5);
  tcase_add_test(tc_core, test_round6);
  tcase_add_test(tc_core, test_round7);
  tcase_add_test(tc_core, test_round8);
  tcase_add_test(tc_core, test_round9);
  tcase_add_test(tc_core, test_round10);
  tcase_add_test(tc_core, test_round11);
  tcase_add_test(tc_core, test_round12);
  tcase_add_test(tc_core, test_round13);
  tcase_add_test(tc_core, test_round14);
  tcase_add_test(tc_core, test_round15);
  tcase_add_test(tc_core, test_round16);
  tcase_add_test(tc_core, test_round17);
  tcase_add_test(tc_core, test_round18);
  tcase_add_test(tc_core, test_round19);
  tcase_add_test(tc_core, test_round20);
  tcase_add_test(tc_core, test_round21);
  tcase_add_test(tc_core, test_round22);
  tcase_add_test(tc_core, test_round23);
  tcase_add_test(tc_core, test_round24);
  tcase_add_test(tc_core, test_round25);
  tcase_add_test(tc_core, test_round26);
  tcase_add_test(tc_core, test_round27);
  tcase_add_test(tc_core, test_round28);
  tcase_add_test(tc_core, test_round29);
  tcase_add_test(tc_core, test_round30);
  tcase_add_test(tc_core, test_round31);
  tcase_add_test(tc_core, test_round32);
  tcase_add_test(tc_core, test_round33);
  tcase_add_test(tc_core, test_round34);
  tcase_add_test(tc_core, test_round35);
  tcase_add_test(tc_core, test_round36);
  tcase_add_test(tc_core, test_round37);
  tcase_add_test(tc_core, test_round38);
  tcase_add_test(tc_core, test_round39);
  tcase_add_test(tc_core, test_round40);
  tcase_add_test(tc_core, test_round41);
  tcase_add_test(tc_core, test_round42);
  tcase_add_test(tc_core, test_round43);
  tcase_add_test(tc_core, test_round44);
  tcase_add_test(tc_core, test_round45);
  tcase_add_test(tc_core, test_round46);
  tcase_add_test(tc_core, test_round47);
  tcase_add_test(tc_core, test_round48);
  tcase_add_test(tc_core, test_round49);
  tcase_add_test(tc_core, test_round50);
  tcase_add_test(tc_core, test_round51);
  tcase_add_test(tc_core, test_round52);
  tcase_add_test(tc_core, test_round53);
  tcase_add_test(tc_core, test_round54);
  tcase_add_test(tc_core, test_round55);

  suite_add_tcase(s, tc_core);
  return s;
}
