#include <stdio.h>

typedef double Scalar;

int main(void) {
  Scalar a[][3] = {{1, 2, 3}, {4, 5, 6}};
  Scalar* b[] = {(Scalar[]){1, 2, 3}, (Scalar[]){4, 5, 6}};
  printf("sizeof _ / sizeof(Scalar)\n");
  printf("%td\n", sizeof a / sizeof(Scalar));
  printf("%td\n", sizeof b / sizeof(Scalar));
  printf("(Scalar*)_[0] - (Scalar*)_\n");
  printf("%td\n", (Scalar*)a[0] - (Scalar*)a);
  printf("%td\n", (Scalar*)b[0] - (Scalar*)b);
  printf("(Scalar*)_[1] - (Scalar*)_\n");
  printf("%td\n", (Scalar*)a[1] - (Scalar*)a);
  printf("%td\n", (Scalar*)b[1] - (Scalar*)b);
  printf("_[1] - _[0]\n");
  printf("%td\n", a[1] - a[0]);
  printf("%td\n", b[1] - b[0]);
  printf("&_[0][1] - &_[0][0]\n");
  printf("%td\n", &a[0][1] - &a[0][0]);
  printf("%td\n", &b[0][1] - &b[0][0]);
  printf("Contents\n");
  for (size_t i = 0; i < sizeof a / sizeof(Scalar); i += 1) {
    printf("%f %f\n", ((Scalar*)a)[i], ((Scalar*)b)[i]);
  }
}
