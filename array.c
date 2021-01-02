#include <stdio.h>

typedef double Val;

int main(void) {
  Val a[][3] = {{1, 2, 3}, {4, 5, 6}};
  Val* b[] = {(Val[]){1, 2, 3}, (Val[]){4, 5, 6}};
  printf("sizeof _ / sizeof(Val)\n");
  printf("%td\n", sizeof a / sizeof(Val));
  printf("%td\n", sizeof b / sizeof(Val));
  printf("(Val*)_[0] - (Val*)_\n");
  printf("%td\n", (Val*)a[0] - (Val*)a);
  printf("%td\n", (Val*)b[0] - (Val*)b);
  printf("(Val*)_[1] - (Val*)_\n");
  printf("%td\n", (Val*)a[1] - (Val*)a);
  printf("%td\n", (Val*)b[1] - (Val*)b);
  printf("_[1] - _[0]\n");
  printf("%td\n", a[1] - a[0]);
  printf("%td\n", b[1] - b[0]);
  printf("&_[0][1] - &_[0][0]\n");
  printf("%td\n", &a[0][1] - &a[0][0]);
  printf("%td\n", &b[0][1] - &b[0][0]);
  printf("Contents\n");
  for (size_t i = 0; i < sizeof a / sizeof(Val); i += 1) {
    printf("%f %f\n", ((Val*)a)[i], ((Val*)b)[i]);
  }
}
