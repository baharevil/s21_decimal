#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"

int s21_mul_lazy(s21_decimal_lazy *value_1, s21_decimal_lazy *value_2,
                 s21_decimal_lazy *result) {

 int error = 0;
 uint16_t i = 0, j = 0;

 uint8_t *temp = realloc(result->mantissa, value_1->size + value_2->size);
 if (temp) {
    result->mantissa = temp;
    result->size = value_1->size + value_2->size;
    memset(result->mantissa, 0, result->size);
 } else
    error = 1;

 if (!error) {
    uint16_t res = 0;
    uint8_t carry = 0;
    while (i < value_1->size) {
        while (j < value_2->size) {
            res = (uint16_t) *(result->mantissa + i + j) + *(value_1->mantissa + i) * *(value_2->mantissa + j);
            carry =  res >> sizeof(uint8_t) * CHAR_BIT;
            *(result->mantissa + i + j + 1) += carry;
            *(result->mantissa + i + j) = (uint8_t) res;
            j++;
        }
        j = carry = 0;
        i++;
    }

    // Если остался перенос, доаллоцируем себе массив
   // if (carry)
   //    *(result->mantissa + i + j) += (uint8_t) carry;
    //     result->size++;
    //     uint8_t *temp = realloc(result->mantissa, result->size);
    //     if (temp) {
    //     result->mantissa = temp;
    //     result->mantissa[result->size - 1] = carry;
    //     } else
    //     error = 1;
    // }
 }
 

 return error;
}