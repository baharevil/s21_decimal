#include "s21_decimal.h"

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование числа из integer в decimal

  @param[in] src Входящее число integer
  @param[in] *dst Указатель на decimal
  @return 0 - конвертация успешна, 1 - ошибка конвертации
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = conv_ok;
  if (dst != S21_NULL) {
    if (src < 0) {
      dst->exponent.bits.sign = 1;
      src = ~src + 1;
    }
    dst->mantissa.bytes[0] = src;
  } else
    status = conv_false;
  return status;
}