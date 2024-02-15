#include "s21_decimal_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  printf("\x1b[1;33mCURRENT TEST: %d \x1b[0m\n", counter_testcase);
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

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

void run_tests_s21_is_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {equal_suite0(), equal_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_tests_s21_is_not_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_NOT_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {not_equal_suite0(), not_equal_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_tests_s21_is_greater(void) {
  printf("\n\x1b[4;36m TEST S21_IS_GREATER \x1b[0m\n");
  Suite *list_cases[] = {greater_suite0(), greater_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_tests_s21_is_greater_or_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_GREATER_OR_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {greater_or_equal_suite0(), greater_or_equal_suite1(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_tests_s21_is_less(void) {
  printf("\n\x1b[4;36m TEST S21_IS_LESS \x1b[0m\n");
  Suite *list_cases[] = {less_suite0(), less_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_tests_s21_is_less_or_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_LESS_OR_EQUAL \x1b[0m\n");
  Suite *list_cases[] = {less_or_equal_suite0(), less_or_equal_suite1(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_tests_s21_round(void) {
  printf("\n\x1b[4;36m TEST S21_ROUND \x1b[0m\n");
  Suite *list_cases[] = {round_suite0(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

int main(void) {
  run_tests_s21_round();
  run_tests_s21_is_equal();
  run_tests_s21_is_not_equal();
  run_tests_s21_is_greater();
  run_tests_s21_is_greater_or_equal();
  run_tests_s21_is_less();
  run_tests_s21_is_less_or_equal();
  run_tests_s21_add();

  return 0;
}