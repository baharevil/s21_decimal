#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование числа из decimal в integer

  @param[in] src Входящее число decimal
  @param[in] *dst Указатель на integer
  @return 0 - конвертация успешна, 1 - ошибка конвертации
*/
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = conv_ok;
  s21_decimal tmp = {0};

  if (!dst) error = conv_false;

  // если экспонента не нулевая отбрасываем остаток делением на 10
  if (!error && src.exponent.bits.exponent)
    error |= s21_truncate(src, &tmp);
  else
    tmp = src;

  // провека остуствия значимых чисел в старшей мантиссе
  if (!error) error = (tmp.mantissa.bits[1] != 0 || tmp.mantissa.bits[2] != 0);
  
  // chek on int32_min value
  if (!error && tmp.exponent.bits.sign 
      && tmp.mantissa.bits[0] <= ((int64_t)INT32_MAX + 1))
    *dst = ~tmp.mantissa.bits[0] + 1;
  
  // chek on int32_max value
  else if (!error && tmp.mantissa.bits[0] <= INT32_MAX)
    *dst = tmp.mantissa.bits[0];
  
  // else error
  else
    error = conv_false;
  
  return error;
}