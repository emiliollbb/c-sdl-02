#include <stdio.h>

void function_a();
void function_b();

void function_a()
{
  int a=5;
  printf("el valor de a es: %d\n", a);
}

void function_b()
{
  int b;
  printf("el valor de b es: %d\n", b);
}


int main(int argc, char *argv[])
{
  function_a();
  function_b();
}