#ifndef S21_DECIMAL_TEST_H
#define S21_DECIMAL_TEST_H

#include <check.h>

#include "s21_decimal.h"

/**************************************************************************
                    Arifmetic
 *************************************************************************/

// S21_ADD_TEST
Suite *add_suite1(void);
Suite *add_suite2(void);
Suite *add_suite3(void);
Suite *add_suite4(void);
Suite *add_suite5(void);
Suite *add_suite6(void);
Suite *add_suite7(void);
Suite *add_suite8(void);
Suite *add_suite9(void);
Suite *add_suite0(void);

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void run_tests_s21_add(void);

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

// S21_IS_LESS_OR_EQUAL_TEST
Suite *less_or_equal_suite0(void);
Suite *less_or_equal_suite1(void);

/**************************************************************************
                    another
 *************************************************************************/

// S21_ROUND_TEST
Suite *round_suite0(void);
// Suite *round_suite1(void);

#endif