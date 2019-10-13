#include <stdio.h>

int main(int argc, char *argv)
{
	int entero=-5;
	long entero_largo=-123123123123;
	unsigned int natural=99999;
	unsigned long natural_largo=343434343434;
	double decimal=3.14159;

	entero = 5;
	
	printf("mi entero: %d\n", entero);
	printf("mi entero largo: %ld\n", entero_largo);
	printf("mi natural: %d\n", natural);
	printf("mi decimal: %f\n", decimal);

}
