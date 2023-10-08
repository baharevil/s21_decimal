#include "s21_decimal.h"

#include <stdlib.h>

void s21_dec_init(s21_decimal* dec) {
    unsigned char *temp = calloc(sizeof(char), 1);
    if (temp) {
        dec->data = temp;
        dec->size = 1;
    }
}
