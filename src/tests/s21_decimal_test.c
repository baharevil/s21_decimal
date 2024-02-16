#include "s21_decimal_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal_test.h"

int main(void) {
  run_tests_s21_add();
  // run_tests_s21_div();
  run_tests_s21_sub();

  // run_tests_s21_round();
  // run_tests_s21_is_equal();
  // run_tests_s21_is_not_equal();
  // run_tests_s21_is_greater();
  // run_tests_s21_is_greater_or_equal();
  // run_tests_s21_is_less();
  // run_tests_s21_is_less_or_equal();
  return 0;
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  printf("\x1b[1;33mCURRENT TEST: %d \x1b[0m\n", counter_testcase);
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  // srunner_set_fork_status(sr, CK_NOFORK);
  srunner_set_fork_status(sr, CK_FORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

/**************************************************************************
                    Arifmetic
 *************************************************************************/

// S21_ADD_TEST
void run_tests_s21_add(void) {
  printf("\n\x1b[4;36m TEST S21_ADD \x1b[0m\n");
  Suite *list_cases[] = {add_suite0(), add_suite1(), add_suite2(), add_suite3(),
                         add_suite4(), add_suite5(), add_suite6(), add_suite7(),
                         add_suite8(), add_suite9(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_DIV_TEST
void run_tests_s21_div(void) {
  printf("\n\x1b[4;36m TEST S21_DIV \x1b[0m\n");
  Suite *list_cases[] = {div_suite0(), div_suite1(), div_suite2(), div_suite3(),
                         //  div_suite4(), div_suite5(), div_suite6(),
                         //  div_suite7(), div_suite8(), div_suite9(),
                         //  div_suite10(), div_suite11(), div_suite12(),
                         //  div_suite13(), div_suite14(), div_suite15(),
                         //  div_suite16(), div_suite17(), div_suite18(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_MOD_TEST

// S21_MUL_TEST

// S21_SUB_TEST
void run_tests_s21_sub(void) {
  printf("\n\x1b[4;36m TEST S21_SUB \x1b[0m\n");
  Suite *list_cases[] = {sub_suite0(), sub_suite1(), sub_suite2(), sub_suite3(),
                         sub_suite4(), sub_suite5(), sub_suite6(), sub_suite7(),
                         sub_suite8(), sub_suite9(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

/**************************************************************************
                    Compare
 *************************************************************************/

// S21_IS_EQUAL_TEST
void run_tests_s21_is_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {equal_suite0(), equal_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_NOT_EQUAL_TEST
void run_tests_s21_is_not_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_NOT_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {not_equal_suite0(), not_equal_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_GREATER_TEST
void run_tests_s21_is_greater(void) {
  printf("\n\x1b[4;36m TEST S21_IS_GREATER \x1b[0m\n");
  Suite *list_cases[] = {greater_suite0(), greater_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_GREATER_OR_EQUAL_TEST
void run_tests_s21_is_greater_or_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_GREATER_OR_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {greater_or_equal_suite0(), greater_or_equal_suite1(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_LESS_TEST
void run_tests_s21_is_less(void) {
  printf("\n\x1b[4;36m TEST S21_IS_LESS \x1b[0m\n");
  Suite *list_cases[] = {less_suite0(), less_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_LESS_OR_EQUAL_TEST
void run_tests_s21_is_less_or_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_LESS_OR_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {less_or_equal_suite0(), less_or_equal_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_ROUND_TEST
void run_tests_s21_round(void) {
  printf("\n\x1b[4;36m TEST S21_ROUND \x1b[0m\n");
  Suite *list_cases[] = {round_suite0(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}
