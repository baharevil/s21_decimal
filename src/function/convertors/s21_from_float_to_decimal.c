#include <math.h>
#include <stddef.h>

#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = conv_ok;
  float src_copy = 0, round = 0, div = 0;
  s21_decimal_lazy tmp = {0}, result = {0};

  error |= (dst == NULL);

  if (!error) error |= !s21_decimal_is_valid(dst);

  if (!error) error |= s21_lazy_init(&tmp, NULL);

  if (!error) error |= s21_lazy_init(&result, NULL);

  if (!error) {
    src_copy = src;
    // Установка знаков
    if (src_copy < 0) {
      tmp.sign++;
      src_copy *= -1;
    }
    // Разделяем float на целую и дробную части
    div = modff(src_copy, &round);

    // Копируем целую часть в decimal
    error |= s21_from_int_to_lazy((int)round, &tmp);
    error |= s21_add_lazy(&tmp, &result, &result);
  }

  // Если есть дробная часть
  if (!error && div) {
    // Для фильтрации шума вида 0.12340001527257
    float epsilon = 1e-4;
    uint8_t size = 28, exp = 0;

    // Считаем разряды целой части
    while (round > 1) {
      round /= 10;
      size--;
    }

    // Домножаем дробную часть и суммируем с результатом
    for (uint8_t i = 0; !error && div > epsilon && i < size; i++, exp++) {
      error |= s21_mul_lazy_to_10(&result);
      tmp.exponent = result.exponent;
      div = modff(div * 10, &round);
      error |= s21_from_int_to_lazy((int)round, &tmp);
      error |= s21_add_lazy(&tmp, &result, &result);
    }
    s21_from_lazy_to_decimal(&result, dst);
  }

  s21_lazy_destroy(&tmp);
  s21_lazy_destroy(&result);

  return error;
}