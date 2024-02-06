#include <math.h>
#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование числа из float в decimal

  @param[in] src Входящее число float
  @param[in] *dst Указатель на decimal
  @return 0 - конвертация успешна, 1 - ошибка конвертации
  @version 3
*/
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = conv_ok;
  int exp = 0;
  s21_decimal_lazy tmp = {0}, result = {0};

  error |= !s21_decimal_ptr_is_valid(dst);

  // Превышение порядка e+28. Не понятно как работает.
  error |= ((uint8_t) exp2f(src) > 155);

  if (!error) error |= !s21_decimal_is_valid(dst);

  if (!error) error |= s21_lazy_init(&tmp, NULL);

  if (!error) error |= s21_lazy_init(&result, NULL);

  if (!error) {
    // Обработка знаков
    if (src < 0) {
      result.sign = tmp.sign = 1;
      src *= -1;
    }
    // Получаем мантиссу и порядок
    double mantissa = frexpf(src, &exp);
    // Место сброса целых чисел мантиссы
    double devnull = 0;
    // Мантисса всегда exp == 1
    result.exponent = 1;
    
    // Переводим мантиссу в результат, экспонента считается сама
    while (!error && mantissa) {
      mantissa *= 10.0;
      tmp.exponent = result.exponent;
      error |= s21_from_int_to_lazy((int) mantissa, &tmp);
      mantissa = modf(mantissa, &devnull);
      error |= s21_add_lazy(&tmp, &result, &result);
      error |= s21_mul_lazy_to_10(&result);
    }
    error |= s21_div_lazy_to_10(&result);
  }
  
  if (!error) {
    s21_decimal_lazy two = {0};
    error |= s21_lazy_init(&two, NULL);
    // Новый способ объявлять числа)
    error |= s21_from_int_to_lazy(2, &two);
    error |= s21_from_int_to_lazy(2, &tmp);

    // Обработка знаков
    two.sign = tmp.sign;

    // Порядок считаем целыми
    two.exponent = tmp.exponent = 0;

    // Возводим 2 в степень exp
    // Начинаем с --exp, потому что 2^1 уже захардкодили
    while (!error && --exp)
      s21_mul_lazy(&tmp, &two, &tmp);
    
    // Умножаем мантиссу на порядок в результате
    error |= s21_mul_lazy(&result, &tmp, &result);

    //! @todo Здесь должно быть округление до 7ми значащих цифр
    error |= s21_from_lazy_to_decimal(&result, dst);
  
    // Освобождаем память    
    s21_lazy_destroy(&two);
  }

  // Освобождаем память
  s21_lazy_destroy(&tmp);
  s21_lazy_destroy(&result);

  return error;
}