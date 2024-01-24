#include "s21_decimal.h"

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование числа из decimal в integer

  @param[in] src Входящее число decimal
  @param[in] *dst Указатель на integer
  @return 0 - конвертация успешна, 1 - ошибка конвертации
*/
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = conv_ok;
  if (dst != S21_NULL) {
    while (src.exponent.bits.exponent > 0) {
      s21_decimal tmp10 = {0};
      s21_decimal tmp = {0};
      s21_from_int_to_decimal(10, &tmp10);
      s21_div(src, tmp10, &tmp);
      src = tmp;
    }
    if (!src.exponent.bits.sign) {
      if (src.mantissa.bits > INT32_MAX)
        status = conv_false;
      else
        *dst = src.mantissa.bytes[0];
    } else {
      src.mantissa.bytes[0] = ~src.mantissa.bytes[0] + 1;
      if (src.mantissa.bits > INT32_MIN)
        status = conv_false;
      else
        *dst = src.mantissa.bytes[0];
    }
  }
  return status;
}