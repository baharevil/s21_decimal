#include <stddef.h>

#include "s21_decimal.h"

/*!
  @ingroup ConverterOperators Преобразователи
  @brief Конвертирование числа из integer в decimal

  @param[in] src Входящее число integer
  @param[in] *dst Указатель на decimal
  @return 0 - конвертация успешна, 1 - ошибка конвертации
*/
uint8_t s21_from_int_to_lazy(int src, s21_decimal_lazy *dst) {
  int error = conv_ok;
  // Валидируем реквизиты
  if (!s21_decimal_ptr_is_valid(dst))
    error = conv_false;
  // Изменяем размер к 1 int (4 байта)
  if (!error) error |= s21_lazy_resize(dst, 4);
  // Обрабатываем знаки
  if (!error && src < 0) {
    dst->sign = 1;
    src = ~src + 1;
  }
  // Пишем в мантиссу
  if (!error) {
    *(int *)dst->mantissa = src;
    uint16_t size = s21_search_msb_lazy(dst);
    size = (size > 0) * size + (size == 0) * 1;
    error |= s21_lazy_resize(dst, size);
  }
  return error;
}