#include <stdio.h>

void display(int age) 
{
	printf("%d\n", age);
}

int main() 
{
	int ageArray[] = { 2, 15, 4 };
	
	display(ageArray[0]);

	printf("%d array elements\n", sizeof(ageArray) / sizeof(ageArray[0]));

	return 0;
}