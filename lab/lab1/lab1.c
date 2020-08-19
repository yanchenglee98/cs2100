#include <stdio.h>

void printBinaryForm( int X )
//Purpose: Print parameter X in binary form
//Output: Binary representation of X directly printed
//Assumption: X is non-negative (i.e. >= 0)
{
	
    int binary[32]; 
  
    int i = 0; 
    while (X > 0) { 
  
        binary[i] = X % 2; 
        X /= 2; 
        i++; 
    } 
  
    for (int j = i - 1; j >= 0; j--) {
		// printf("j: %d ", j);
        printf("%d", binary[j]); 
	}

	printf("\n");

	/*
	// recrusive solution
	if (X == 0) {
		// base case
	} else {
		printBinaryForm(X / 2);
		printf("%d", X % 2);
	}
	*/

}

void printHexadecimalForm( int X )
//Purpose: Print parameter X in hexadecimal form
//Output: Hexadecimal representation of X directly printed
//Assumption: X is non-negative (i.e. >= 0)
{

	char hexadec[32]; 
  
    int i = 0; 
    while (X > 0) { 
  
        hexadec[i] = (X % 16 < 10) ? (X % 16 + 48) : (X % 16 + 55); 
        X /= 16; 
        i++; 
    } 
  
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hexadec[j]); 
	}

	printf("\n");

}
int main(void)
{
	int X; 	

	printf("Enter X: ");
	scanf("%d",&X);

	//print X in binary form
	printBinaryForm( X );

	//print X in hexadecimal form
	printHexadecimalForm( X );

	return 0;
}
