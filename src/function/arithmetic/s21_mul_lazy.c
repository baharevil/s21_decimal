#include <stddef.h>

#include "s21_decimal.h"

/// @todo передача по значению для облегчения работы функций

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция вычитания s21_decimal_lazy.

  Функция нормализует значения s21_decimal_lazy и далее
  проиходит умножение в столбик.

  @param[in] *value_1,*value_2 Указатели на умножаемые значения
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
int s21_mul_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  int error = 0;
  uint16_t result_size = 0;
  s21_decimal_lazy tmp = {0}, tmp_res = {0};

  error |= !s21_lazy_ptr_is_valid(value_1);
  error |= !s21_lazy_ptr_is_valid(value_2);
  error |= !s21_lazy_ptr_is_valid(result);

  if (!error) {
    result_size = value_1->size + value_2->size;
    error |= s21_lazy_init(&tmp, NULL);
    error |= s21_lazy_init(&tmp_res, NULL);
    error |= s21_lazy_resize(&tmp_res, result_size);
    error |= s21_lazy_resize(result, result_size);
  }

  if (!error) {
    uint16_t res = 0;
    uint8_t carry = 0;

    for (uint16_t i = 0; i < value_1->size && !error; i++) {
      for (uint16_t j = 0; j < value_2->size && !error; j++) {
        res = (uint16_t)(*(value_1->mantissa + i) * *(value_2->mantissa + j));
        res += carry;
        *(tmp.mantissa + i + j) = (uint8_t)res;

        carry = res >> sizeof(uint8_t) * CHAR_BIT;
        if (i + j + 1 >= tmp.size) s21_lazy_resize(&tmp, tmp.size + 1);
        *(tmp.mantissa + i + j + 1) = carry;
      }
      carry = 0;
      error |= s21_add_lazy(&tmp, &tmp_res, &tmp_res);
      s21_lazy_destroy(&tmp);
      error |= s21_lazy_init(&tmp, NULL);
      if (!error) error |= s21_lazy_resize(&tmp, result_size);
    }

    tmp_res.exponent = value_1->exponent + value_2->exponent;
    tmp_res.sign = (value_1->sign != value_2->sign);

    if (!error) s21_lazy_to_lazy_cp(&tmp_res, result);
  }

  s21_lazy_destroy(&tmp);
  s21_lazy_destroy(&tmp_res);

  return error;
}