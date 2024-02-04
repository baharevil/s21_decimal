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

  if (!error) {
    // если экспонента не нулевая отбрасываем остаток делением на 10
    error |= s21_truncate(src, &tmp);
  }
  if (!error) {
    // провека остуствия значимых чисел в старшей мантиссе и помещаемся ли в
    // знаковый INT
    if (tmp.mantissa.bits[0] <= INT32_MAX && tmp.mantissa.bits[1] == 0 &&
        tmp.mantissa.bits[2] == 0) {
      // копируем или копируем с инверсией, в зависимости от знака
      if (tmp.exponent.bits.sign)
        *dst = ~tmp.mantissa.bits[0] + 1;
      else
        *dst = tmp.mantissa.bits[0];
    }
  } else
    error = conv_false;
  return error;
}