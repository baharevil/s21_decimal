#ifndef S21_DECIMAL_TEST_H
#define S21_DECIMAL_TEST_H

#include <check.h>

#include "s21_decimal.h"

/**************************************************************************
                    ARITHMETIC
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

// S21_MUL_TEST
Suite *mul_suite0(void);
Suite *mul_suite1(void);
Suite *mul_suite2(void);
Suite *mul_suite3(void);
Suite *mul_suite4(void);
Suite *mul_suite5(void);
Suite *mul_suite6(void);
Suite *mul_suite7(void);
Suite *mul_suite8(void);
Suite *mul_suite9(void);
Suite *mul_suite10(void);
Suite *mul_suite11(void);
Suite *mul_suite12(void);
Suite *mul_suite13(void);
Suite *mul_suite14(void);
Suite *mul_suite15(void);
Suite *mul_suite16(void);
Suite *mul_suite17(void);
Suite *mul_suite18(void);

void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void run_tests_s21_mul(void);

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

/**************************************************************************
                    COMPARISON
 *************************************************************************/
// S21_IS_LESS_TEST
Suite *is_less_suite1(void);
Suite *is_less_suite2(void);
Suite *is_less_suite3(void);
Suite *is_less_suite4(void);
Suite *is_less_suite5(void);
Suite *is_less_suite6(void);
Suite *is_less_suite7(void);
Suite *is_less_suite8(void);
Suite *is_less_suite9(void);
Suite *is_less_suite10(void);
Suite *is_less_suite11(void);
Suite *is_less_suite12(void);
Suite *is_less_suite13(void);
Suite *is_less_suite14(void);
Suite *is_less_suite15(void);
Suite *is_less_suite16(void);

void test_is_less(s21_decimal decimal1, s21_decimal decimal2, int check);
void run_tests_s21_is_less(void);

// S21_IS_LESS_OR_EQUAL_TEST
Suite *is_less_or_equal_suite1(void);
Suite *is_less_or_equal_suite2(void);
Suite *is_less_or_equal_suite3(void);
Suite *is_less_or_equal_suite4(void);
Suite *is_less_or_equal_suite5(void);
Suite *is_less_or_equal_suite6(void);
Suite *is_less_or_equal_suite7(void);
Suite *is_less_or_equal_suite8(void);
Suite *is_less_or_equal_suite9(void);
Suite *is_less_or_equal_suite10(void);
Suite *is_less_or_equal_suite11(void);
Suite *is_less_or_equal_suite12(void);
Suite *is_less_or_equal_suite13(void);
Suite *is_less_or_equal_suite14(void);
Suite *is_less_or_equal_suite15(void);
Suite *is_less_or_equal_suite16(void);

void test_is_less_or_equal(s21_decimal decimal1, s21_decimal decimal2,
                           int check);
void run_tests_s21_is_less_or_equal(void);

// S21_IS_GREATER_TEST
Suite *is_greater_suite1(void);
Suite *is_greater_suite2(void);
Suite *is_greater_suite3(void);
Suite *is_greater_suite4(void);
Suite *is_greater_suite5(void);
Suite *is_greater_suite6(void);
Suite *is_greater_suite7(void);
Suite *is_greater_suite8(void);
Suite *is_greater_suite9(void);
Suite *is_greater_suite10(void);
Suite *is_greater_suite11(void);
Suite *is_greater_suite12(void);
Suite *is_greater_suite13(void);
Suite *is_greater_suite14(void);
Suite *is_greater_suite15(void);
Suite *is_greater_suite16(void);

void test_is_greater(s21_decimal decimal1, s21_decimal decimal2, int check);
void run_tests_s21_is_greater(void);

// S21_IS_GREATER_OR_EQUAL_TEST
Suite *is_greater_or_equal_suite1(void);
Suite *is_greater_or_equal_suite2(void);
Suite *is_greater_or_equal_suite3(void);
Suite *is_greater_or_equal_suite4(void);
Suite *is_greater_or_equal_suite5(void);
Suite *is_greater_or_equal_suite6(void);
Suite *is_greater_or_equal_suite7(void);
Suite *is_greater_or_equal_suite8(void);
Suite *is_greater_or_equal_suite9(void);
Suite *is_greater_or_equal_suite10(void);
Suite *is_greater_or_equal_suite11(void);
Suite *is_greater_or_equal_suite12(void);
Suite *is_greater_or_equal_suite13(void);
Suite *is_greater_or_equal_suite14(void);
Suite *is_greater_or_equal_suite15(void);
Suite *is_greater_or_equal_suite16(void);

void test_is_greater_or_equal(s21_decimal decimal1, s21_decimal decimal2,
                              int check);
void run_tests_s21_is_greater_or_equal(void);

// S21_IS_EQUAL_TEST
Suite *is_equal_suite1(void);
Suite *is_equal_suite2(void);
Suite *is_equal_suite3(void);
Suite *is_equal_suite4(void);
Suite *is_equal_suite5(void);
Suite *is_equal_suite6(void);
Suite *is_equal_suite7(void);
Suite *is_equal_suite8(void);
Suite *is_equal_suite9(void);
Suite *is_equal_suite10(void);
Suite *is_equal_suite11(void);
Suite *is_equal_suite12(void);
Suite *is_equal_suite13(void);
Suite *is_equal_suite14(void);
Suite *is_equal_suite15(void);
Suite *is_equal_suite16(void);

void test_is_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void run_tests_s21_is_equal(void);

// S21_IS_NOT_EQUAL_TEST
Suite *is_not_equal_suite1(void);
Suite *is_not_equal_suite2(void);
Suite *is_not_equal_suite3(void);
Suite *is_not_equal_suite4(void);
Suite *is_not_equal_suite5(void);
Suite *is_not_equal_suite6(void);
Suite *is_not_equal_suite7(void);
Suite *is_not_equal_suite8(void);
Suite *is_not_equal_suite9(void);
Suite *is_not_equal_suite10(void);
Suite *is_not_equal_suite11(void);
Suite *is_not_equal_suite12(void);
Suite *is_not_equal_suite13(void);
Suite *is_not_equal_suite14(void);
Suite *is_not_equal_suite15(void);
Suite *is_not_equal_suite16(void);

void test_is_not_equal(s21_decimal decimal1, s21_decimal decimal2, int check);
void run_tests_s21_is_not_equal(void);

/**************************************************************************
                    CONVERTORS
 *************************************************************************/
// S21_INT_TO_DECIMAL

// S21_FLOAT_TO_DECIMAL

// S21_DECIMAL_TO_INT

// S21_DECIMAL_TO_FLOAT

/**************************************************************************
                    ANOTHER
 *************************************************************************/

// S21_FLOOR_TEST
Suite *floor_suite0(void);
Suite *floor_suite1(void);
Suite *floor_suite2(void);
Suite *floor_suite3(void);

void run_tests_s21_floor(void);
void test_floor(s21_decimal decimal, s21_decimal decimal_check);

// S21_ROUND_TEST
Suite *round_suite0(void);
Suite *round_suite1(void);
Suite *round_suite2(void);
Suite *round_suite3(void);

void run_tests_s21_round(void);
void s21_test_round(s21_decimal decimal, s21_decimal decimal_check);

// S21_TRUNCATE_TEST
Suite *truncate_suite0(void);
Suite *truncate_suite1(void);
Suite *truncate_suite2(void);
Suite *truncate_suite3(void);

void run_tests_s21_truncate(void);
void test_truncate(s21_decimal decimal, s21_decimal decimal_check);

// S21_NEGATE_TEST
Suite *negate_suite0(void);
Suite *negate_suite1(void);
Suite *negate_suite2(void);
Suite *negate_suite3(void);

void run_tests_s21_negate(void);
void test_negate(s21_decimal decimal, s21_decimal decimal_check);

#endif