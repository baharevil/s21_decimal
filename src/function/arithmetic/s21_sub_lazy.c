#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

// инверсия бит
void s21_inverse(s21_decimal_lazy *value) {
  for (uint16_t size = 0; size < value->size; size++)
    *((*value).mantissa + size) = ~*((*value).mantissa + size);
}

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция вычитания s21_decimal_lazy.

  Функция нормализует и выравнивает по размеру значения
  s21_decimal_lazy. Далее происходит вычетания через
  инверсию бит и дальнейшее их сложение в функции
  s21_add_uint8_t().

  @param[in] *value_1,*value_2 Указатели на вычитаемые знаачения
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - ошибка
*/
int s21_sub_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  // Возвращаемое значение
  int error = 0;
  int8_t is_normal = 0;

  // создание lazy_one (это просто 1 записанная в форме decimal)
  s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal_lazy lazy_one = {0};

  // Первичная валидация
  error |= (value_1 == NULL || value_1->mantissa == NULL);
  error |= (value_2 == NULL || value_2->mantissa == NULL);

  if (!error) {
    is_normal = s21_is_normal_lazy(value_1, value_2);
    error |= s21_lazy_init(&lazy_one, &one);
  }

  // нормализация + выравнивание размеров
  if (is_normal == 0) {
    error |= s21_lazy_normalize_greater(value_1, value_2);
    error |= s21_lazy_upsize(value_1, value_2);
  }

  else if (is_normal == 1)
    error |= s21_lazy_upsize(value_1, value_2);

  // Увеличиваем и единицу
  if (!error) {
    error |= s21_lazy_upsize(&lazy_one, value_1);
    if (result->size != value_1->size) s21_lazy_zeroing(result, value_1->size);
  }

  // Рассчет
  if (!error) {
    // Сравниваем нормализованные мантиссы (size у них одинаковый)
    int8_t cmp =
        s21_memrevcmp(value_1->mantissa, value_2->mantissa, result->size);

    // если слева "+", а справа "-", то это просто сложение (5 - (-1) = 5 + 1)
    if (value_1->sign == 0 && value_2->sign == 1) {
      value_2->sign = 0;
      s21_add_lazy(value_1, value_2, result);
    }

    // если слева "-", а справа "+", то это "отрицательное" сложение (-5 - 1 =
    // -6)
    else if (value_1->sign == 1 && value_2->sign == 0) {
      value_2->sign = value_1->sign = 0;
      s21_add_lazy(value_1, value_2, result);
      result->sign = 1;
    }

    // Метод через дополнительный код
    // пример случаев: (5 - 1) или (-5 - (-1) == -5 + 1)
    else if (cmp == 1) {
      s21_inverse(value_2);
      s21_add_uint8_t(value_2->mantissa, lazy_one.mantissa, value_2->mantissa,
                      value_2->size);
      s21_add_uint8_t(value_1->mantissa, value_2->mantissa, result->mantissa,
                      value_1->size);

      result->exponent = value_1->exponent;
      result->sign = value_1->sign;
    }

    // метод через инверсию
    // пример случаев: (1 - 5) или (-1 - (-5) == -1 + 5)
    else if (cmp == -1) {
      s21_inverse(value_2);
      s21_add_uint8_t(value_1->mantissa, value_2->mantissa, result->mantissa,
                      value_1->size);
      s21_inverse(result);

      result->exponent = value_1->exponent;
      result->sign = !value_1->sign;
    }

    else {
      result->exponent = 0;
      result->sign = value_1->sign;
      if (result->size != 1) error |= s21_lazy_resize(result, 1);
    }
  }

  if (lazy_one.mantissa != NULL) free(lazy_one.mantissa);

  return error;
}