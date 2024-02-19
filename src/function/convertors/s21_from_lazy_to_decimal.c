#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/// @todo Если size > 12 ---> Нормализация

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование s21_decimal_lazy в s21_decimal

  @param[in] src Указатель на s21_decimal_lazy
  @param[in] *dst Указатель на s21_decimal
  @return 0 - ок, 1 - ошибка
*/
int s21_from_lazy_to_decimal(s21_decimal_lazy *src, s21_decimal *dest) {
  int error = 0, cmp = -1, small = 0;

  uint8_t dec_size = 0, size = 0;
  s21_decimal_lazy carry = {0}, tmp_v = {0};
  s21_decimal_lazy lazy_one = {0}, lazy_five = {0}, lazy_two = {0};

  error = (!src || !dest || !src->mantissa);

  // init
  if (!error) {
    error |= s21_lazy_init(&carry, NULL);
    error |= s21_lazy_init(&lazy_five, NULL);
    error |= s21_lazy_init(&lazy_two, NULL);
    error |= s21_lazy_init(&lazy_one, NULL);
    error |= s21_lazy_init(&tmp_v, NULL);
    dec_size = sizeof(dest->mantissa.bytes);
  }

  // set value
  if (!error) {
    error = s21_lazy_to_lazy_cp(src, &tmp_v);
    error = s21_from_int_to_lazy(1, &lazy_one);
    error = s21_from_int_to_lazy(2, &lazy_two);
    error = s21_from_int_to_lazy(5, &lazy_five);
    lazy_five.exponent = (error == 0);
  }

  // normalize
  while (!error && tmp_v.size > dec_size && tmp_v.exponent != 0)
    error |= s21_lazy_normalization(&tmp_v, tmp_v.exponent - 1);

  // check error
  if (!error && (tmp_v.size > dec_size)) error = inf + tmp_v.sign;

  // ? мб и не надо
  if (!error && tmp_v.exponent > 28) {
    error |= s21_lazy_normalization(&tmp_v, 28);
    small = !s21_is_null_lazy(src);
  }

  /*
    Если tmp_v.exponent != 0, значит работаем с дробной частью
    и нужно выравнять значение 5 в нужный ранг.

    Например пришло число 123.5000051234 == 1235000051234 / 10^10, и new_exp
    == 5.

    После вызова функции расчета получаем:
    tmp_v = 12350000 / 10^5  = 123.500000000
    carry     =    51234 / 10^10 = 000.0000051234

    Значит будем сравнивать со значением 000.0000050000 = 50000 / 10^10


    Если tmp_v.exponent == 0, необходимо сравнить carry с 0,5
  */
  // rounding
  if (!error && tmp_v.exponent != src->exponent) {
    // вычесляем остаток
    s21_sub_lazy(src, &tmp_v, &carry);

    if (tmp_v.exponent) lazy_five.exponent = tmp_v.exponent + 1;
    lazy_one.exponent = tmp_v.exponent;
    lazy_one.sign = tmp_v.sign;
    carry.sign = 0;
  }

  // compare
  if (!error) {
    cmp = s21_is_equal_lazy(&carry, &lazy_five);

    // Если cmp == 0, значит банковское окргление
    if (cmp == 0) {
      error |= s21_div_lazy(&tmp_v, &lazy_two, &carry);
      if (carry.exponent != tmp_v.exponent)
        error |= s21_add_lazy(&tmp_v, &lazy_one, &tmp_v);
    }

    // Если cmp == 1, значит математическое окргление
    else if (cmp == 1) {
      error |= s21_add_lazy(&tmp_v, &lazy_one, &tmp_v);
    }

    // Иначе проверям на код ошибки
    else
      error = (cmp == -2);
  }

  // check to inf or -inf
  if (!error) error = s21_aritmetic_error(&tmp_v);

  if (!error) {
    size = tmp_v.size * (tmp_v.size <= dec_size) +
           dec_size * (tmp_v.size > dec_size);

    dest->exponent.bits.sign = tmp_v.sign;
    dest->exponent.bits.exponent = tmp_v.exponent;
    error = (memcpy(dest->mantissa.bytes, tmp_v.mantissa + tmp_v.size - size,
                    size) == NULL);

    if (!error && size != dec_size)
      memset(dest->mantissa.bytes + size, 0, dec_size - size);
  }

  if (!error && small) error = 2 * s21_is_null_lazy(&tmp_v);

  s21_lazy_destroy(&tmp_v);
  s21_lazy_destroy(&carry);
  s21_lazy_destroy(&lazy_five);
  s21_lazy_destroy(&lazy_one);
  s21_lazy_destroy(&lazy_two);

  return error;
}