#include <stdio.h>

int main(void) {
  double a[][3] = {{1, 2, 3}, {4, 5, 6}};
  double* b[] = {(double[]){1, 2, 3}, (double[]){4, 5, 6}};
  printf("sizeof _ / sizeof(double)\n");
  printf("%zu\n", sizeof a / sizeof(double));
  printf("%zu\n", sizeof b / sizeof(double));
  printf("(double*)_[0] - (double*)_\n");
  printf("%zu\n", (double*)a[0] - (double*)a);
  printf("%zu\n", (double*)b[0] - (double*)b);
  printf("(double*)_[1] - (double*)_\n");
  printf("%zu\n", (double*)a[1] - (double*)a);
  printf("%zu\n", (double*)b[1] - (double*)b);
  printf("_[1] - _[0]\n");
  printf("%zu\n", a[1] - a[0]);
  printf("%zu\n", b[1] - b[0]);
  printf("&_[0][1] - &_[0][0]\n");
  printf("%zu\n", &a[0][1] - &a[0][0]);
  printf("%zu\n", &b[0][1] - &b[0][0]);
  printf("Contents\n");
  for (size_t i = 0; i < sizeof a / sizeof(double); i += 1) {
    printf("%lf %lf\n", ((double*)a)[i], ((double*)b)[i]);
  }
}
