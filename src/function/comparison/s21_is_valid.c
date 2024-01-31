#include <execinfo.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

typedef struct expression {
  void *value;
  int (*is_valid)(const void *);
} expression;

uint8_t s21_getexp(char **begin_ptr, char **exp_str);
uint8_t s21_constructor(char *exp_str, expression **exp, va_list *runtime);

int s21_decimal_ptr_is_valid(const void *lazy);
int s21_lazy_ptr_is_valid(const void *lazy);

/// @note Очень сырая, нужно больше проверок

/*!
  @ingroup Support Функции для служебного пользования
  @brief Проверяет корректность переменных

  %p - *s21_decimal
  %lp - *s21_decimal_lazy

  @param[in] *format - тип данных
  @param[in] ... - сами параметры
  @return 0 - OK, 1 - неккорктные данные
*/
uint8_t s21_is_valid(char *format, ...) {
  uint8_t error = 0;
  va_list arg_ptr;
  size_t slen = 0;

  expression *exp = NULL;
  char *offset = NULL, *exp_str = NULL;

  va_start(arg_ptr, format);

  while (!error && *format) {
    unsigned short flag = 0;
    offset = strchr(format, '%');

    if (flag |= (format == offset)) {
      error |= s21_getexp(&format, &exp_str);
      error |= s21_constructor(exp_str, &exp, &arg_ptr);
      if (!error) error = exp->is_valid(exp->value);
    }

    else {
      slen = (offset != NULL) * (offset - format) +
             (offset == NULL) * (strlen(format));
    }

    if (!flag) format += slen;
    if (flag && exp && exp->value) free(exp->value);
  }
  va_end(arg_ptr);

  if (exp) free(exp);
  if (exp_str) free(exp_str);

  return error;
}

uint8_t s21_getexp(char **begin_ptr, char **exp_str) {
  if (!*begin_ptr && !exp_str) return -1;

  uint8_t stop = 0;
  size_t size = 1;

  size += strcspn((*begin_ptr + size), "dp");
  stop = -((size == strlen(*begin_ptr)) ||
           (*exp_str = realloc(*exp_str, sizeof(char) * size + 2)) == NULL);

  if (*exp_str && !stop) {
    strncpy(*exp_str, *begin_ptr, size + 1);
    *(*exp_str + size + 1) = 0;
    *begin_ptr += size + 1;
  }

  return stop;
}

uint8_t s21_constructor(char *exp_str, expression **exp, va_list *runtime) {
  uint8_t error = 0;

  // Если первый вызов
  if (*exp == NULL) *exp = malloc(sizeof(expression));

  // Проверка что malloc отработал нормально
  if (*exp) {
    memset(*exp, 0, sizeof(expression));

    if (strcmp(exp_str, "%p") == 0) {
      (*exp)->value = malloc(sizeof(long *));
      *(long *)(*exp)->value = (long)va_arg(*runtime, void *);
      (*exp)->is_valid = s21_decimal_ptr_is_valid;
    }

    else if (strcmp(exp_str, "%lp") == 0) {
      (*exp)->value = malloc(sizeof(long *));
      *(long *)(*exp)->value = (long)va_arg(*runtime, void *);
      (*exp)->is_valid = s21_lazy_ptr_is_valid;
    }

  } else
    error = 1;

  return error;
}

int s21_decimal_is_valid(const void *decimal) {
  return ((*(s21_decimal *)decimal).exponent.bits.empty0 ||
          (*(s21_decimal *)decimal).exponent.bits.empty1);
}

int s21_decimal_ptr_is_valid(const void *decimal) {
  return (((s21_decimal *)*(long *)decimal)->exponent.bits.empty0 ||
          ((s21_decimal *)*(long *)decimal)->exponent.bits.empty1);
}

int s21_lazy_is_valid(const void *lazy) {
  return (((s21_decimal_lazy *)lazy)->mantissa == NULL);
}

int s21_lazy_ptr_is_valid(const void *lazy) {
  return ((s21_decimal_lazy *)*(long *)lazy == NULL ||
          ((s21_decimal_lazy *)*(long *)lazy)->mantissa == NULL);
}