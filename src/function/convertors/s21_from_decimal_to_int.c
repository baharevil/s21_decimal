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
    // если экспонента не нулевая отбрасываем остаток делением на 10
    while (src.exponent.bits.exponent > 0) {
      s21_decimal tmp10 = {0};
      s21_decimal tmp = {0};
      s21_from_int_to_decimal(10, &tmp10);
      s21_div(src, tmp10, &tmp);
      src = tmp;
      src.exponent.bits.exponent--;
    }
    // провека остуствия значимых чисел в старшей мантиссе
    if (src.mantissa.bits[1] == 0 && src.mantissa.bits[2] == 0) {
      // проверяем знак
      if (!src.exponent.bits.sign) {
        // проверяем влазит ли положительный инт
        if (src.mantissa.bits[0] <= INT32_MAX)
          *dst = src.mantissa.bits[0];
        else
          status = conv_false;
      } else {
        // проверяем влазит ли отрицательный инт
        if (src.mantissa.bits[0] < INT32_MAX)
          *dst = !src.mantissa.bits[0] + 1;
        else
          status = conv_false;
      }
    } else
      status = conv_false;
  } else
    status = conv_false;
  return status;
}