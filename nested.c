#include <stdio.h>

int main(void) {
  double a[][3] = {{1, 2, 3}, {4, 5, 6}};
  double* b[] = {(double[]){1, 2, 3}, (double[]){4, 5, 6}};
  printf("%zu\n", sizeof(a));
  printf("%zu\n", sizeof(b));
}
