#include "s21_decimal.h"

/*!
  @ingroup ArifmeticOperators Арифметические операторы
  @brief Функция деления двух decimal.

  Данная функция является оберткой над функцией s21_div_lazy()

  @param[in] *value_1,*value_2 Делисое и делитель
  @param[in] *result Указатель на результат
  @return Код ошибки: 0 - ОК, 1 - inf, 2 - min_inf, 3 - деление на 0
*/