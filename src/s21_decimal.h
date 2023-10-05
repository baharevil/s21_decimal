#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H


#include <bits/endian.h>
#include <stdint.h>
#include <limits.h>

#define S21_NULL 0x0
typedef unsigned long s21_size_t;

typedef struct mantissa {
  char *data;
} mantissa;

typedef struct exponent {
#if __BYTE_ORDER == __BIG_ENDIAN
  uint8_t sign : 1;
  uint8_t empty1 : 7;
  uint8_t exponent : 8;
  uint16_t n_digits : 16;
#endif /* Big endian.  */
#if __BYTE_ORDER == __LITTLE_ENDIAN
  uint16_t n_digits : 16;
  uint8_t exponent : 8;
  uint8_t empty1 : 7;
  uint8_t sign : 1;
#endif /* Little endian.  */
} exponent;

typedef struct s21_decimal {
#if __BYTE_ORDER == __BIG_ENDIAN
  exponent exp;
  mantissa mantissa;
#endif /* Big endian.  */
#if __BYTE_ORDER == __LITTLE_ENDIAN
  mantissa mantissa;
  exponent exp;
#endif /* Little endian.  */
} s21_decimal;

typedef struct s21_decimal_suite {
  s21_size_t size;
  s21_decimal value;

  void (*init)(s21_decimal*);
  void (*destroy)(s21_decimal*);
  void (*resize)(s21_decimal*, s21_size_t);
  void (*normalize)(s21_decimal);

  int (*is_normal)(s21_decimal);
  int (*is_zero)(s21_decimal);
  int (*id_inf)(s21_decimal);

  int (*dec_to_int)(s21_decimal, int*);
  int (*dec_to_float)(s21_decimal, float*);
  int (*int_to_dec)(s21_decimal, int*);
  int (*float_to_dec)(s21_decimal, float*);
} s21_decimal_suite;

/*
    Функции для служебного пользования
*/

void s21_decimal_suite_init(s21_decimal_suite *);
void s21_dec_init(s21_decimal*);
void s21_dec_destroy(s21_decimal*);
void s21_dec_resize(s21_decimal*, s21_size_t);



/*
    Арифметические операторы.
    Функции возвращают код ошибки:

    0 - OK
    1 - число слишком велико или равно бесконечности
    2 - число слишком мало или равно отрицательной бесконечности
    3 - деление на 0
*/
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // -
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // -
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // -
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // -

/*
    Операторы сравнение.
    Возвращаемое значение:

    0 - FALSE
    1 - TRUE
*/
int s21_is_less(s21_decimal, s21_decimal);              // -
int s21_is_less_or_equal(s21_decimal, s21_decimal);     // -
int s21_is_greater(s21_decimal, s21_decimal);           // -
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // -
int s21_is_equal(s21_decimal, s21_decimal);             // -
int s21_is_not_equal(s21_decimal, s21_decimal);         // -

/*
    Преобразователи.
    Возвращаемое значение - код ошибки:

    0 - OK
    1 - ошибка конвертации
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);      // -
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // -
int s21_from_decimal_to_int(s21_decimal src, int *dst);      // -
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // -

/*
    Другие функции.
    Возвращаемое значение - код ошибки:

    0 - OK
    1 - ошибка вычисления
*/
int s21_floor(s21_decimal value, s21_decimal *result);     // -
int s21_round(s21_decimal value, s21_decimal *result);     // -
int s21_truncate(s21_decimal value, s21_decimal *result);  // -
int s21_negate(s21_decimal value, s21_decimal *result);    // -

#endif