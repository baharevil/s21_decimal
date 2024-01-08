#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <endian.h>
#include <limits.h>
#include <stdint.h>

#define S21_NULL 0x0
typedef unsigned long s21_size_t;

typedef union s21_uint96_t {
  uint32_t bits[3];
  uint8_t bytes[12];
} s21_uint96_t;

typedef union {
  uint32_t raw;
  struct {
#if __BYTE_ORDER == __BIG_ENDIAN
    uint8_t sign : 1;
    uint8_t empty1 : 7;
    uint8_t exponent : 8;
    uint16_t empty0 : 16;
#endif /* Big endian.  */
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint16_t empty0 : 16;
    uint8_t exponent : 8;
    uint8_t empty1 : 7;
    uint8_t sign : 1;
#endif /* Little endian.  */
  } bits;
} s21_exponent;

typedef struct s21_decimal {
#if __BYTE_ORDER == __BIG_ENDIAN
  s21_exponent exponent;
  s21_uint96_t mantissa;
#endif /* Big endian.  */
#if __BYTE_ORDER == __LITTLE_ENDIAN
  s21_uint96_t mantissa;
  s21_exponent exponent;
#endif /* Little endian.  */
} s21_decimal;

typedef struct s21_decimal_lazy {
#if __BYTE_ORDER == __BIG_ENDIAN
  uint8_t sign : 1;
  uint8_t empty1 : 7;
  uint8_t exponent : 8;
  uint16_t size : 16;
  uint8_t *mantissa;
#endif /* Big endian.  */
#if __BYTE_ORDER == __LITTLE_ENDIAN
  uint8_t *mantissa;
  uint16_t size : 16;
  uint8_t exponent : 8;
  uint8_t empty1 : 7;
  uint8_t sign : 1;
#endif /* Little endian.  */
} s21_decimal_lazy;

/*
    Функции для служебного пользования
*/
void bin_print(unsigned int length, void *pointer, int options);

/*
Функция поиска старшего значащего бита (Most Significant Bit) в числе
s21_decimal. Возвращает целочисленное количество байт от старшего значащего бита
до конца мантиссы, т.е. реальный размер в байтах.
*/
uint8_t s21_search_msb(s21_decimal *decimal);

/*Функция копирования обычного числа s21_decimal в s21_decimal_lazy*/
uint8_t s21_dec_to_lazy_cp(s21_decimal *src, s21_decimal_lazy *dest);

/*Функция приведения мантиссы числа s21_decimal_lazy к заданной экспоненте*/
uint8_t s21_lazy_normalization(s21_decimal_lazy *lazy, uint8_t exp);

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

int s21_add_lazy(s21_decimal_lazy value_1, s21_decimal_lazy value_2,
                 s21_decimal_lazy *result);
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