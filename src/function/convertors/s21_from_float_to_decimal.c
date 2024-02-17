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
  error |= ((uint8_t)exp2f(src) > 155);

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

    // Переводим мантиссу в результат, экспонента считается сама
    while (!error && mantissa) {
      mantissa *= 10.0;
      error |= s21_mul_lazy_to_10(&result);
      tmp.exponent = result.exponent;
      error |= s21_from_int_to_lazy((int)mantissa, &tmp);
      mantissa = modf(mantissa, &devnull);
      error |= s21_add_lazy(&tmp, &result, &result);
    }
  }

  if (!error) {
    int8_t direction = (exp > 0) - (exp < 0);
    s21_decimal_lazy two = {0};
    error |= s21_lazy_init(&two, NULL);
    // Новый способ объявлять числа)
    error |= s21_from_int_to_lazy(2, &two);
    error |= s21_from_int_to_lazy(1, &tmp);

    // Обработка знаков
    two.sign = tmp.sign;

    // Порядок считаем целыми
    two.exponent = tmp.exponent = 0;

    if (!error && exp < 0) {
      exp *= -1;
    }

    int (*func)(s21_decimal_lazy *, s21_decimal_lazy *, s21_decimal_lazy *) =
    ((int (*)(s21_decimal_lazy *, s21_decimal_lazy *, s21_decimal_lazy *))(
        (direction >= 0) * (uintptr_t)s21_mul_lazy +
        (direction < 0) * (uintptr_t)s21_div_lazy));

    // Возводим 2 в степень exp
    while (!error && (exp-- > 0)) error |= func(&tmp, &two, &tmp);

    // Умножаем/делим мантиссу на порядок в результате
    error |= s21_mul_lazy(&result, &tmp, &result);

    // Освобождаем память
    s21_lazy_destroy(&two);
  }
  
  // Сначала проверяем то, что у нас получилось на +-inf
  if (!error) {
    s21_decimal_lazy null = {0};
    s21_lazy_init(&null, NULL);

    error = s21_aritmetic_error(&result);

    if (error == min_inf) {
      s21_from_lazy_to_decimal(&null, dst);
    }

    if (error != arifm_ok)
      error = conv_false;
    
    s21_lazy_destroy(&null);
  }
  
  // А потом округляем стандартно (в т.ч. банковским, правильно ли это?)
  if (!error && result.exponent > 7) {
    result.exponent -= 7;
    error |= s21_round_lazy(&result, &result);
    result.exponent += 7;
  }
  
  if (!error) {
    error = s21_from_lazy_to_decimal(&result, dst);
  }

  // Освобождаем память
  s21_lazy_destroy(&tmp);
  s21_lazy_destroy(&result);

  return error;
}
