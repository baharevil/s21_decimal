#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

/*
    Арифметические операторы. Сумма.
    Функции возвращают код ошибки:

    0 - OK
    1 - число слишком велико или равно бесконечности
    2 - число слишком мало или равно отрицательной бесконечности
    3 - деление на 0
*/

// инверсия бит
void s21_inverse(s21_decimal_lazy *value) {
  for (uint16_t size = 0; size < value->size; size++)
    *((*value).mantissa + size) = ~*((*value).mantissa + size);
}

// resize и зануление с сохранением старого значения
int s21_resize_and_set(s21_decimal_lazy *ptr, uint8_t size) {
  int error = 0;
  uint16_t tmp_size = 0;

  tmp_size = ptr->size;
  ptr->size = size;
  error |= s21_lazy_resize(&ptr);
  memset((ptr->mantissa + tmp_size), 0, size - tmp_size);

  return error;
}

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
    error |= s21_resize_and_set(ptr, size);

    // Увеличиваем и единицу
    ptr = &lazy_one;
    error |= s21_resize_and_set(ptr, size);

    if (result->size != size) s21_lazy_zeroing(result, size);
  }

  // Рассчет
  if (!error) {
    // Сравниваем нормализованные мантиссы (size у них одинаковый)
    // ! Вот тут баг, memcmp врет. Нужна функция сравнения s21_decimal_lazy
    /*
      Если ему дать, напрмер, числа v1 = 0х10 & v2 = 0x1,
      то получим положительное число (v1 > v2).

      Но если ему дать, напрмер, числа v1 = 0х100 & v2 = 0x1,
      то получим отрицательное число (v1 < v2).
    */
    int8_t cmp = memcmp(value_1->mantissa, value_2->mantissa, value_1->size);
    cmp = (cmp > 0) - (cmp < 0);

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

    // TODO: изменить 2 низних условия, они не логичены
    // Метод через дополнительный код
    // пример случаев: (5 - 1) или (-1 - (-5) == -1 + 5)
    else if ((cmp == 1 && value_1->sign == value_2->sign) ||
             (cmp == -1 && value_1->sign != value_2->sign)) {
      s21_decimal_lazy *ptr = NULL;

      if (value_1->sign == value_2->sign)
        ptr = value_2;
      else
        ptr = value_1;

      s21_inverse(ptr);
      s21_add_uint8_t(ptr->mantissa, lazy_one.mantissa, ptr->mantissa,
                      ptr->size);
      s21_add_uint8_t(value_1->mantissa, value_2->mantissa, result->mantissa,
                      value_1->size);

      result->exponent = value_1->exponent;
      result->size = value_1->size;
      result->sign = 0;
    }

    // метод через инверсию
    // пример случаев: (1 - 5) или (-5 - (-1) == -5 + 1)
    else if ((cmp == -1 && value_1->sign == value_2->sign) ||
             (cmp == 1 && value_1->sign != value_2->sign)) {
      s21_decimal_lazy *ptr = NULL;

      if (value_1->sign == value_2->sign)
        ptr = value_2;
      else
        ptr = value_1;

      s21_inverse(ptr);
      s21_add_uint8_t(value_1->mantissa, value_2->mantissa, result->mantissa,
                      value_1->size);
      s21_inverse(result);

      result->exponent = value_1->exponent;
      result->size = value_1->size;
      result->sign = 1;
    }

    else {
      result->exponent = result->sign = 0;
    }
  }

  if (lazy_one.mantissa != NULL) free(lazy_one.mantissa);
  return error;
}