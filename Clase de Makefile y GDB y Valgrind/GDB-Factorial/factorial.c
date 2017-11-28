#include <stdio.h>


double factorial(int n) 
{
    double result = 1;
    
    while(n--)
        result *= n;
    
    return result;
}
 
int main()
{
    int n = 4;
    printf("El factorial de %d es %.0lf.\n", n, factorial(n));
    
    return 0;
}
 
