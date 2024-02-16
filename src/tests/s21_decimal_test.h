#ifndef S21_DECIMAL_TEST_H
#define S21_DECIMAL_TEST_H

#include <check.h>

#include "s21_decimal.h"

/**************************************************************************
                    Arifmetic
 *************************************************************************/

// S21_ADD_TEST
Suite *add_suite0(void);
Suite *add_suite1(void);
Suite *add_suite2(void);
Suite *add_suite3(void);
Suite *add_suite4(void);
Suite *add_suite5(void);
Suite *add_suite6(void);
Suite *add_suite7(void);
Suite *add_suite8(void);
Suite *add_suite9(void);

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void run_tests_s21_add(void);

// S21_DIV_TEST
Suite *div_suite0(void);
Suite *div_suite1(void);
Suite *div_suite2(void);
Suite *div_suite3(void);
Suite *div_suite4(void);
Suite *div_suite5(void);
Suite *div_suite6(void);
Suite *div_suite7(void);
Suite *div_suite8(void);
Suite *div_suite9(void);
Suite *div_suite10(void);
Suite *div_suite11(void);
Suite *div_suite12(void);
Suite *div_suite13(void);
Suite *div_suite14(void);
Suite *div_suite15(void);
Suite *div_suite16(void);
Suite *div_suite17(void);
Suite *div_suite18(void);

void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void run_tests_s21_div(void);

// S21_MOD_TEST
void test_mod(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mod_fail(s21_decimal decimal1, s21_decimal decimal2, int code_check);

// S21_MUL_TEST
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);

// S21_SUB_TEST
Suite *sub_suite0(void);
Suite *sub_suite1(void);
Suite *sub_suite2(void);
Suite *sub_suite3(void);
Suite *sub_suite4(void);
Suite *sub_suite5(void);
Suite *sub_suite6(void);
Suite *sub_suite7(void);
Suite *sub_suite8(void);
Suite *sub_suite9(void);

void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void run_tests_s21_sub(void);

/**************************************************************************
                    Compare
 *************************************************************************/

// S21_IS_EQUAL_TEST
Suite *equal_suite0(void);
Suite *equal_suite1(void);

// S21_IS_NOT_EQUAL_TEST
Suite *not_equal_suite0(void);
Suite *not_equal_suite1(void);

// S21_IS_GREATER_TEST
Suite *greater_suite0(void);
Suite *greater_suite1(void);

// S21_IS_GREATER_OR_EQUAL_TEST
Suite *greater_or_equal_suite0(void);
Suite *greater_or_equal_suite1(void);

// S21_IS_LESS_TEST
Suite *less_suite0(void);
Suite *less_suite1(void);

// S21_IS_LESS_OR_EQUAL_TEST
Suite *less_or_equal_suite0(void);
Suite *less_or_equal_suite1(void);

/**************************************************************************
                    another
 *************************************************************************/

// S21_FLOOR_TEST
void test_floor(s21_decimal decimal, s21_decimal decimal_check);

// S21_NEGATE_TEST
void test_negate(s21_decimal decimal, s21_decimal decimal_check);

// S21_TRUNCATE_TEST
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);

// S21_ROUND_TEST
Suite *round_suite0(void);
// Suite *round_suite1(void);
void s21_test_round(s21_decimal decimal, s21_decimal decimal_check);

#endif