#include "s21_decimal.h"

void s21_decimal_suite_init(s21_decimal_suite *dec_suite) {
    dec_suite->init = s21_dec_init;
    dec_suite->destroy = s21_dec_destroy;
    dec_suite->resize = s21_dec_resize;
    dec_suite->init(&dec_suite->value);
}