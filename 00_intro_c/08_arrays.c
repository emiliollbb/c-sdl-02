#include <stdio.h>

int main(int argc, char *argv[])
{
  int a[100], i;

  for(i=0; i<100; i++)
  {
    a[i]=i*2+5;
  }

  for(i=0; i<100; i++)
  {
    printf("%d ", a[i]);
  }
  printf("\n");
}