#include <stdio.h>

int main(int argc, char *argv[])
{
  int a, c;
  int *b;

  a = 7;
  b = &a;
  c = *b;

  printf("El valor de a es: %d\n", a);
  printf("El valor de b es: %u\n", b);
  printf("El valor de c es: %d\n", c);
}