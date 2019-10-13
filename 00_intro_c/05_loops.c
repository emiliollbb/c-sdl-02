#include <stdio.h>

int main() 
{
	int i;

	i=0;
	do {
		printf("Dando vueltas. Repeticion %d\n", i);
		i++;
	} while(i<100);


	i=0;
	while(i<100) {
		printf("Dando vueltas 2. Repeticion %d\n", i);
		i++;
	};

	for(i=0; i<100; i++) {
		printf("Dando vueltas 3. Repeticion %d\n", i);
		i++;
	}
		

	return 0;
}
