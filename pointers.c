#include <stdio.h>

int main()
{
	int a = 1;
	int *p = &a;

	printf("\n");	
	printf("Direccion de memoria 'p': %p\n", p);
	printf("Direccion de memoria 'a' con &a: %p\n", &a);
	printf("Direccion de memoria '&p': %p\n", &p);
	printf("Valor de 'a': %i\n", *p);

	//Pointer Arithmetic
	printf("%p\n", &p);
	printf("%p\n", &p+2);
	//printf("%p\n", &p+2);
	printf("The size of Interger is %ld bytes\n", sizeof(int));
	//printf("%p\n", &p+3);
	//printf("%p\n", &p+4);
	//printf("%p\n", &p+5);

}
