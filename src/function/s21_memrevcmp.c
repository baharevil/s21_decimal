#include <stdint.h>

/*Функция создана и работает приближено к memcmp(), но реверсивно*/
int s21_memrevcmp(const void *s1, const void *s2, uint16_t size) {
  int result = 0;
  const uint8_t *s1_ptr = s1;
  const uint8_t *s2_ptr = s2;

  if (size == 0) size = 12;

  while (size > 0 && !result) {
    if (*(s1_ptr + size - 1) > *(s2_ptr + size - 1))
      result = 1;
    else if (*(s1_ptr + size - 1) < *(s2_ptr + size - 1))
      result = -1;
    size--;
  }
  return result;
}