#include "s21_decimal.h"

void s21_decimal_suite_init(s21_decimal_suite *dec_suite) {
    dec_suite->init = s21_dec_init;
    dec_suite->destroy = s21_dec_destroy;
    dec_suite->resize = s21_dec_resize;
    dec_suite->init(&dec_suite->value);
}

void s21_decimal_suite_destroy(s21_decimal_suite *dec_suite) {
    dec_suite->destroy(&dec_suite->value);
    dec_suite->init = S21_NULL;
    dec_suite->destroy = S21_NULL;
    dec_suite->resize = S21_NULL;
}
