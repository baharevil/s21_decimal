#include "s21_decimal.h"

/*
    Арифметические операторы. Сумма.
    Функции возвращают код ошибки:

    0 - OK
    1 - число слишком велико или равно бесконечности
    2 - число слишком мало или равно отрицательной бесконечности
    3 - деление на 0
*/

// ! заглушка
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int error = 0;

    *result = value_1;
    *result = value_2;

    return error;
}