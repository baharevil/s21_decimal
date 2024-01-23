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

typedef union s21_exponent {
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

typedef union s21_decimal {
  int bits[4];
  struct {
#if __BYTE_ORDER == __BIG_ENDIAN
    s21_exponent exponent;
    s21_uint96_t mantissa;
#endif /* Big endian.  */
#if __BYTE_ORDER == __LITTLE_ENDIAN
    s21_uint96_t mantissa;
    s21_exponent exponent;
#endif /* Little endian.  */
  };
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

/*!
  @defgroup ArifmeticOperators Арифметические операторы
  @brief Модуль арифметических операций над s21_decimal

  @return Функции возвращают код ошибки:
    0 - OK
    1 - число слишком велико или равно бесконечности
    2 - число слишком мало или равно отрицательной бесконечности
    3 - деление на 0
*/
typedef enum arifmetic_error {
  arifm_ok = 0,
  inf,
  min_inf,
  div_by_0
} arifmetic_error;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result);
int s21_sub_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result);
int s21_mul_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result);
int s21_div_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result);
uint16_t s21_add_uint8_t(uint8_t *v1, uint8_t *v2, uint8_t *result,
                         uint8_t size);
uint8_t s21_mul_lazy_to_10(s21_decimal_lazy *lazy);
uint8_t s21_div_lazy_to_10(s21_decimal_lazy *lazy);

/*!
  @defgroup ComparisonOperators Операторы сравнение
  @brief Модуль функций сравнения значений s21_decimal

  @return Функции возвращают код ошибки:
    0 - FALSE
    1 - TRUE
*/
typedef enum comparison_error { false = 0, true } comparison_error;

int s21_is_less(s21_decimal, s21_decimal);              // -
int s21_is_less_or_equal(s21_decimal, s21_decimal);     // -
int s21_is_greater(s21_decimal, s21_decimal);           // -
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // -
int s21_is_equal(s21_decimal, s21_decimal);             // -
int s21_is_not_equal(s21_decimal, s21_decimal);         // -
int s21_is_equal_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2);
uint8_t s21_is_null(s21_decimal *decimal);
int8_t s21_is_normal_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2);

/*!
  @defgroup ConverterOperators Преобразователи
  @brief Конвертация s21_decimal в другой тип

  @return Функции возвращают код ошибки:
    0 - OK
    1 - ошибка конвертации

  @bug А зачем функция s21_decimal_to_lazy ?
*/
typedef enum converter_error { conv_ok = 0, conv_false } converter_error;

int s21_from_int_to_decimal(int src, s21_decimal *dst);      // +
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // -
int s21_from_decimal_to_int(s21_decimal src, int *dst);      // -
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // -
uint8_t s21_from_decimal_to_lazy(s21_decimal *src, s21_decimal_lazy *dest);
uint8_t s21_from_lazy_to_decimal(s21_decimal_lazy *src, s21_decimal *dest);
s21_decimal_lazy s21_decimal_to_lazy(s21_decimal value);

/*!
  @defgroup AnotherFunction Другие функции
  @brief Модуль других функций над s21_decimal

  @return Функции возвращают код ошибки:
    0 - OK
    1 - ошибка вычисления
*/
typedef enum another_error { ok = 0, calc_error } other_error;

int s21_floor(s21_decimal value, s21_decimal *result);     // -
int s21_negate(s21_decimal value, s21_decimal *result);    // -
int s21_round(s21_decimal value, s21_decimal *result);     // -
int s21_truncate(s21_decimal value, s21_decimal *result);  // -

/*!
  @defgroup Support Функции для служебного пользования
  @brief Вспомогательные функции

  @return Функции возвращают код ошибки:
    0 - OK
    1 - ошибка

  @bug Задвоение функций. s21_lazy_zeroing & s21_lazy_resize
*/
/// @todo удалить s21_lazy_zeroing
uint8_t s21_lazy_init(s21_decimal_lazy *lazy, s21_decimal *decimal);
void s21_lazy_destroy(s21_decimal_lazy *lazy);
uint8_t s21_lazy_normalization(s21_decimal_lazy *lazy, uint8_t exp);
uint8_t s21_lazy_normalize_greater(s21_decimal_lazy *value_1,
                                   s21_decimal_lazy *value_2);
uint8_t s21_lazy_normalize_less(s21_decimal_lazy *value_1,
                                s21_decimal_lazy *value_2);
uint8_t s21_lazy_resize(s21_decimal_lazy *lazy, uint16_t new_size);
uint8_t s21_lazy_upsize(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2);
uint8_t s21_lazy_downsize(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2);
uint8_t s21_lazy_to_lazy_cp(s21_decimal_lazy *src, s21_decimal_lazy *dest);
uint8_t s21_search_msb(s21_decimal *decimal);
int s21_memrevcmp(const void *s1, const void *s2, uint16_t size);

#endif