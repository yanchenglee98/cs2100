#include <stdio.h>

struct Fraction {
   int num;
   int den;
};


void printFraction( struct Fraction *fptr )
{
    printf( "%d / %d", fptr->num, fptr->den );

    //Can also be written as
    //printf( "%d / %d", (*fptr).num, (*fptr).den );

}

void printFractionArray( struct Fraction fArray[], int size)
{
    //Your work here
    //Dont panic: work out the syntax step-by-step
    //Hint: Need 3-4 lines of code only. Remember to reuse printFraction() function

    for (int i = 0; i < size; i++) {
        printFraction(&(fArray[i]));
        printf(", ");
    }
    printf("\n");
}


int main()
{
    // size of fraction structure is 8
    struct Fraction fArray[3] = { {1, 2}, {3, 4}, {5, 6} };  //an array of 3 fractions

    printf("Fraction 1 = %d / %d\n", fArray[0].num, fArray[0].den);   //observe how to combine the syntax of array and structure

    printFractionArray( fArray, 3 );    //Why do we pass in the array size? Because when you pass an array into a function it decays to a pointer to the first element

     
    struct Fraction f = {1,2};

    printf("size of fArray is %d\n", sizeof(fArray) / sizeof(fArray[0]));

    return 0;
}
