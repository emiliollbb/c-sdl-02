#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, c, d;
  int *b;

  a = 7;
  b = &a;
  c = *b;
  d = b[0];

  printf("El valor de a es: %d\n", a);
  printf("El valor de b es: %u\n", b);
  printf("El valor de c es: %d\n", c);
  printf("El valor de d es: %d\n", d);

  return 0;
}