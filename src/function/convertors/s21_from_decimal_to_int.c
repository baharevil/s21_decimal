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
    if (!((src.mantissa.bytes[0] >> 31) & 1)) {
      if (src.exponent.bits.sign)
        *dst = ~src.mantissa.bytes[0] + 1;
      else
        *dst = src.mantissa.bytes[0];

    } else
      status = conv_false;
    // if (src < 0) {
    //   dst->exponent.bits.sign = 1;
    //   src = ~src + 1;
    // }
    // dst->mantissa.bytes[0] = src;

  } else
    status = conv_false;
  return status;
}