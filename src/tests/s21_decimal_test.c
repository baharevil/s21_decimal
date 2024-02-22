#include "s21_decimal_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal_test.h"

int main(void) {
  //----------------------------------------------
  // run_tests_s21_add();                 // | + |
  // run_tests_s21_sub();                 // | + |
  // run_tests_s21_mul();                 // | + |
  run_tests_s21_div();                 // | - |
  //----------------------------------------------
  //----------------------------------------------
  // run_tests_s21_is_less();             // | + |
  // run_tests_s21_is_less_or_equal();    // | + |
  // run_tests_s21_is_greater();          // | + |
  // run_tests_s21_is_greater_or_equal(); // | + |
  // run_tests_s21_is_equal();            // | + |
  // run_tests_s21_is_not_equal();        // | + |
  //----------------------------------------------
  //----------------------------------------------
  // run_tests_s21_floor();               // | + |
  // run_tests_s21_round();               // | + |
  // run_tests_s21_truncate();            // | + |
  // run_tests_s21_negate();              // | + |
  //----------------------------------------------

  return 0;
}

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

/**************************************************************************
                    ARITHMETIC
 *************************************************************************/

// S21_ADD_TEST
void run_tests_s21_add(void) {
  printf("\n\x1b[4;36m TEST S21_ADD \x1b[0m");
  Suite *list_cases[] = {add_suite0(), add_suite1(), add_suite2(), add_suite3(),
                         add_suite4(), add_suite5(), add_suite6(), add_suite7(),
                         add_suite8(), add_suite9(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_SUB_TEST
void run_tests_s21_sub(void) {
  printf("\n\x1b[4;36m TEST S21_SUB \x1b[0m");
  Suite *list_cases[] = {sub_suite0(), sub_suite1(), sub_suite2(), sub_suite3(),
                         sub_suite4(), sub_suite5(), sub_suite6(), sub_suite7(),
                         sub_suite8(), sub_suite9(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_MUL_TEST
void run_tests_s21_mul(void) {
  printf("\n\x1b[4;36m TEST S21_MUL \x1b[0m");
  Suite *list_cases[] = {mul_suite0(), mul_suite1(), mul_suite2(), mul_suite3(),
                         mul_suite4(), mul_suite5(), mul_suite6(), mul_suite7(),
                         mul_suite8(), mul_suite9(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_DIV_TEST
void run_tests_s21_div(void) {
  printf("\n\x1b[4;36m TEST S21_DIV \x1b[0m");
  Suite *list_cases[] = {
      div_suite0(),  div_suite1(),  div_suite2(),  div_suite3(),  div_suite4(),
      div_suite5(),  div_suite6(),  div_suite7(),  div_suite8(),  div_suite9(),
      div_suite10(), div_suite11(), div_suite12(), div_suite13(), div_suite14(),
      div_suite15(), div_suite16(), div_suite17(), div_suite18(), 
      NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

/**************************************************************************
                    COMPARISON
 *************************************************************************/

// S21_IS_LESS_TEST
void run_tests_s21_is_less(void) {
  printf("\n\x1b[4;36m TEST S21_IS_LESS \x1b[0m");
  Suite *list_cases[] = {is_less_suite1(),
                         is_less_suite2(),
                         is_less_suite3(),
                         is_less_suite4(),
                         is_less_suite5(),
                         is_less_suite6(),
                         is_less_suite7(),
                         is_less_suite8(),
                         is_less_suite9(),
                         is_less_suite10(),
                         is_less_suite11(),
                         is_less_suite12(),
                         is_less_suite13(),
                         is_less_suite14(),
                         is_less_suite15(),
                         is_less_suite16(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_LESS_OR_EQUAL_TEST
void run_tests_s21_is_less_or_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_LESS_OR_EQUAL \x1b[0m");
  Suite *list_cases[] = {is_less_or_equal_suite1(),
                         is_less_or_equal_suite2(),
                         is_less_or_equal_suite3(),
                         is_less_or_equal_suite4(),
                         is_less_or_equal_suite5(),
                         is_less_or_equal_suite6(),
                         is_less_or_equal_suite7(),
                         is_less_or_equal_suite8(),
                         is_less_or_equal_suite9(),
                         is_less_or_equal_suite10(),
                         is_less_or_equal_suite11(),
                         is_less_or_equal_suite12(),
                         is_less_or_equal_suite13(),
                         is_less_or_equal_suite14(),
                         is_less_or_equal_suite15(),
                         is_less_or_equal_suite16(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_GREATER_TEST
void run_tests_s21_is_greater(void) {
  printf("\n\x1b[4;36m TEST S21_IS_GREATER \x1b[0m");
  Suite *list_cases[] = {is_greater_suite1(),
                         is_greater_suite2(),
                         is_greater_suite3(),
                         is_greater_suite4(),
                         is_greater_suite5(),
                         is_greater_suite6(),
                         is_greater_suite7(),
                         is_greater_suite8(),
                         is_greater_suite9(),
                         is_greater_suite10(),
                         is_greater_suite11(),
                         is_greater_suite12(),
                         is_greater_suite13(),
                         is_greater_suite14(),
                         is_greater_suite15(),
                         is_greater_suite16(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_GREATER_OR_EQUAL_TEST
void run_tests_s21_is_greater_or_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_GREATER_OR_EQUAL \x1b[0m");
  Suite *list_cases[] = {is_greater_or_equal_suite1(),
                         is_greater_or_equal_suite2(),
                         is_greater_or_equal_suite3(),
                         is_greater_or_equal_suite4(),
                         is_greater_or_equal_suite5(),
                         is_greater_or_equal_suite6(),
                         is_greater_or_equal_suite7(),
                         is_greater_or_equal_suite8(),
                         is_greater_or_equal_suite9(),
                         is_greater_or_equal_suite10(),
                         is_greater_or_equal_suite11(),
                         is_greater_or_equal_suite12(),
                         is_greater_or_equal_suite13(),
                         is_greater_or_equal_suite14(),
                         is_greater_or_equal_suite15(),
                         is_greater_or_equal_suite16(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_EQUAL_TEST
void run_tests_s21_is_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_EQUAL \x1b[0m");
  Suite *list_cases[] = {is_equal_suite1(),
                         is_equal_suite2(),
                         is_equal_suite3(),
                         is_equal_suite4(),
                         is_equal_suite5(),
                         is_equal_suite6(),
                         is_equal_suite7(),
                         is_equal_suite8(),
                         is_equal_suite9(),
                         is_equal_suite10(),
                         is_equal_suite11(),
                         is_equal_suite12(),
                         is_equal_suite13(),
                         is_equal_suite14(),
                         is_equal_suite15(),
                         is_equal_suite16(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_IS_NOT_EQUAL_TEST
void run_tests_s21_is_not_equal(void) {
  printf("\n\x1b[4;36m TEST S21_IS_NOT_EQUAL \x1b[0m");
  Suite *list_cases[] = {is_not_equal_suite1(),
                         is_not_equal_suite2(),
                         is_not_equal_suite3(),
                         is_not_equal_suite4(),
                         is_not_equal_suite5(),
                         is_not_equal_suite6(),
                         is_not_equal_suite7(),
                         is_not_equal_suite8(),
                         is_not_equal_suite9(),
                         is_not_equal_suite10(),
                         is_not_equal_suite11(),
                         is_not_equal_suite12(),
                         is_not_equal_suite13(),
                         is_not_equal_suite14(),
                         is_not_equal_suite15(),
                         is_not_equal_suite16(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

/**************************************************************************
                    CONVERTORS
 *************************************************************************/
// S21_INT_TO_DECIMAL
void run_tests_s21_from_int_to_decimal(void) {
  printf("\n\x1b[4;36m TEST S21_FROM_INT_TO_DECIMAL \x1b[0m");
  Suite *list_cases[] = {from_int_to_decimal_suite(),  NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_FLOAT_TO_DECIMAL
void run_tests_s21_from_float_to_decimal(void) {
  printf("\n\x1b[4;36m TEST S21_FROM_FLOAT_TO_DECIMAL \x1b[0m");
  Suite *list_cases[] = {from_float_to_decimal_suite0(), 
                         from_float_to_decimal_suite1(), 
                         from_float_to_decimal_suite2(),
                         from_float_to_decimal_suite3(), 
                         from_float_to_decimal_suite4(), 
                         from_float_to_decimal_suite5(), 
                         from_float_to_decimal_suite6(),
                         from_float_to_decimal_suite7(), 
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_DECIMAL_TO_INT
void run_tests_s21_from_decimal_to_int(void) {
  printf("\n\x1b[4;36m TEST S21_FROM_DECIMAL_TO_INT \x1b[0m");
  Suite *list_cases[] = {from_decimal_to_int_suite0(), 
                         from_decimal_to_int_suite1(), 
                         from_decimal_to_int_suite2(),
                         from_decimal_to_int_suite3(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_DECIMAL_TO_FLOAT
void run_tests_s21_from_decimal_to_float(void) {
  printf("\n\x1b[4;36m TEST S21_FROM_DECIMAL_TO_FLOAT \x1b[0m");
  Suite *list_cases[] = {from_decimal_to_float_suite0(), 
                         from_decimal_to_float_suite1(), 
                         from_decimal_to_float_suite2(),
                         from_decimal_to_float_suite3(), 
                         from_decimal_to_float_suite4(), 
                         from_decimal_to_float_suite5(), 
                         from_decimal_to_float_suite6(),
                         from_decimal_to_float_suite7(), 
                         from_decimal_to_float_suite8(), 
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

/**************************************************************************
                    ANOTHER
 *************************************************************************/
// S21_FLOOR_TEST
void run_tests_s21_floor(void) {
  printf("\n\x1b[4;36m TEST S21_FLOOR \x1b[0m");
  Suite *list_cases[] = {floor_suite0(), floor_suite1(), floor_suite2(),
                         floor_suite3(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_ROUND_TEST
void run_tests_s21_round(void) {
  printf("\n\x1b[4;36m TEST S21_ROUND \x1b[0m");
  Suite *list_cases[] = {round_suite0(), round_suite1(), round_suite2(), 
                         round_suite3(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_TRUNCATE_TEST
void run_tests_s21_truncate(void) {
  printf("\n\x1b[4;36m TEST S21_TRUNCATE \x1b[0m");
  Suite *list_cases[] = {truncate_suite0(), truncate_suite1(),
                         truncate_suite2(), truncate_suite3(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

// S21_NEGATE_TEST
void run_tests_s21_negate(void) {
  printf("\n\x1b[4;36m TEST S21_NEGATE \x1b[0m");
  Suite *list_cases[] = {negate_suite0(), negate_suite1(), negate_suite2(),
                         negate_suite3(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}
