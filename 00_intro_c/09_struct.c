#include <stdio.h>
#include <string.h>

struct persona
{
  int edad, ano_nacimiento;
  char nombre[100];
};

void show(struct persona p);
void calcular_edad(struct persona *p);


int main()
{
  struct persona p;
  p.ano_nacimiento=1984;
  strcpy(p.nombre, "Emilio");
  calcular_edad(&p);
  show(p);

  return 0;
}

void calcular_edad(struct persona *p)
{
  p->edad=2019-p->ano_nacimiento;
}


void show(struct persona p)
{
  printf("%s nacido en %d, edad %d\n", p.nombre, p.ano_nacimiento, p.edad);
}