#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/*!
  @ingroup Support Функции для служебного пользования
  @brief Изменение размера мантиссы s21_decimal_lazy.

  Функция приведения размера мантиссы к параметру new_size

  @param[in] *lazy Адрес значения
  @param[in] new_size Новый размер мантиссы
  @return Код ошибки: 0 - OK, 1 - ERROR
*/
uint8_t s21_lazy_resize(s21_decimal_lazy *lazy, uint16_t new_size) {
  uint8_t result = 0;
  uint8_t *temp = NULL;
  int32_t diff = 0;

  // Первичная валидация
  if (lazy == NULL || new_size < 1 || new_size > UINT16_MAX - 1) result = 1;

  // Выделение необходимого объема памяти
  if (!result) {
    diff = new_size - lazy->size;
    temp = realloc(lazy->mantissa, sizeof(uint8_t) * new_size);
    result = (temp == NULL);
  }

  // Если объем положительный, то зануляем новые байты
  if (!result) {
    lazy->mantissa = temp;
    if (diff > 0) memset((lazy->mantissa + lazy->size), 0, diff);
    lazy->size = new_size;
  }

  return result;
}