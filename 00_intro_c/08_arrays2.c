#include <stdio.h>

int main(int argc, char *argv[])
{
  int a[100], i, d;

  for(i=0; i<100; i++)
  {
    a[i]=i*2+5;
  }

  for(i=0; i<100; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");

  d = *a;

  printf("El valor de d es: %d\n", d);

}