#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

// TODO: Вынести в s21_decimal.h + *.с
int8_t s21_decimal_lazy_cmp(s21_decimal_lazy *value_1,
                            s21_decimal_lazy *value_2) {
  int8_t result = 0;

  if (value_1->size == value_2->size) {
    uint16_t count = value_1->size;
    while (count > 0) {
      if (*(value_1->mantissa + count - 1) != *(value_2->mantissa + count - 1))
        result = (*(value_1->mantissa + count - 1) >
                  *(value_2->mantissa + count - 1)) -
                 (*(value_1->mantissa + count - 1) <
                  *(value_2->mantissa + count - 1));
      count--;
    }

  } else
    result = (value_1->size > value_2->size) - (value_1->size < value_2->size);

  return result;
}

// инверсия бит
void s21_inverse(s21_decimal_lazy *value) {
  for (uint16_t size = 0; size < value->size; size++)
    *((*value).mantissa + size) = ~*((*value).mantissa + size);
}

// TODO: коды ошибок
// TODO: -0
int s21_sub_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {
  // Возвращаемое значение
  int error = 0;

  // Первичная валидация
  error |= (value_1 == NULL || value_1->mantissa == NULL);
  error |= (value_2 == NULL || value_2->mantissa == NULL);

  // создание lazy_one (это просто 1 записанная в форме decimal)
  s21_decimal one = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal_lazy lazy_one;

  if (!error) {
    error |= s21_lazy_init(&lazy_one);
    error |= s21_dec_to_lazy_cp(&one, &lazy_one);
  }

  // нормализация + выравнивание размеров
  if (!error) {
    s21_decimal_lazy *ptr = NULL;
    uint16_t size = 0;
    uint8_t exp = 0;

    // На сколько нормализовывать
    exp = (value_1->exponent > value_2->exponent) * value_1->exponent +
          (value_1->exponent <= value_2->exponent) * value_2->exponent;

    // Выбор что будем номрмализовывать
    if (value_1->exponent > value_2->exponent)
      ptr = value_2;
    else
      ptr = value_1;

    // Нормализуем
    error |= s21_lazy_normalization(ptr, exp);

    // На сколько увеличить размер
    size = (value_1->size > value_2->size) * value_1->size +
           (value_1->size <= value_2->size) * value_2->size;

    // Выбор что будем увеличивать
    if (value_1->size > value_2->size)
      ptr = value_2;
    else
      ptr = value_1;

    // Увеличиваем
    error |= s21_lazy_resize(ptr, size);

    // Увеличиваем и единицу
    ptr = &lazy_one;
    error |= s21_lazy_resize(ptr, size);

    if (result->size != size) s21_lazy_zeroing(result, size);
  }

  // Рассчет
  if (!error) {
    // Сравниваем нормализованные мантиссы (size у них одинаковый)
    int8_t cmp = s21_decimal_lazy_cmp(value_1, value_2);

    // если слева "+", а справа "-", то это просто сложение (5 - (-1) = 5 + 1)
    if (value_1->sign == 0 && value_2->sign == 1)
      s21_add_uint8_t(value_1->mantissa, value_2->mantissa, result->mantissa,
                      value_1->size);

    // если слева "-", а справа "+", то это "отрицательное" сложение (-5 - 1 =
    // -6)
    else if (value_1->sign == 1 && value_2->sign == 0) {
      s21_add_uint8_t(value_1->mantissa, value_2->mantissa, result->mantissa,
                      value_1->size);
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
      result->size = value_1->size;
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
      result->size = value_1->size;
      result->sign = !value_1->sign;
    }

    else {
      result->exponent = result->sign = 0;
    }
  }

  if (lazy_one.mantissa != NULL) free(lazy_one.mantissa);
  return error;
}