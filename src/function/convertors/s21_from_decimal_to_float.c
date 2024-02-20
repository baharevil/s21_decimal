#include <math.h>

#include "s21_decimal.h"

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование числа из decimal в float

  @param[in] src Входящее число decimal
  @param[in] *dst Указатель на float
  @return 0 - конвертация успешна, 1 - ошибка конвертации
*/
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = conv_ok;
  double d = 0.0;
  s21_decimal_lazy tmp = {0};

  // Первичная валидация
  if (!dst) error = conv_false;

  //Инициализация переменных
  if (!error)
    error |= s21_lazy_init(&tmp, &src);

  if (!error) {
    // Цикл преобразования
    for (int32_t i = tmp.size - 1; i >= 0; i--) {
      d *= 0x100;
      d += *(tmp.mantissa + i);
    }

    // Приведение экспоненты
    if (tmp.exponent)
      d *= pow(10, (double) -(tmp.exponent));

    // Обработка знаков
    if (tmp.sign)
      d *= -1;

    // Экспорт
    *dst = (float) d;

    //Освобождение памяти
    s21_lazy_destroy(&tmp);
  }

  return error;
}