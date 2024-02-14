#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Подсчитывает кол-во разрядов в 10 виде в s21_decimal_lazy

  @param[in] *lazy Адрес значения
  @param[in] *res Адрес куда записать результат
  @return Код ошибки: 0 - OK, 1 - ERROR
*/
int s21_lazy_ranking(s21_decimal_lazy *value, int *res) {
  int error = 0;

  s21_decimal_lazy tmp_value = {0}, tmp_res = {0}, ten = {0};

  error |= !s21_lazy_ptr_is_valid(value);
  error |= (res == NULL);

  error |= s21_lazy_init(&tmp_value, NULL);
  error |= s21_lazy_init(&tmp_res, NULL);
  error |= s21_lazy_init(&ten, NULL);

  if (!error) s21_from_int_to_lazy(0xa, &ten);
  if (!error) error |= s21_lazy_to_lazy_cp(value, &tmp_value);
  if (!error) tmp_value.exponent = tmp_value.sign = 0;

  // Пока мантисса не 0, делим ее на 10
  while (!error && !s21_is_null_lazy(&tmp_value)) {
    error |= s21_div_lazy_core(&tmp_value, &ten, &tmp_res);
    error |= s21_lazy_to_lazy_cp(&tmp_res, &tmp_value);
    (*res)++;
  }

  s21_lazy_destroy(&tmp_value);
  s21_lazy_destroy(&tmp_res);
  s21_lazy_destroy(&ten);

  return error;
}