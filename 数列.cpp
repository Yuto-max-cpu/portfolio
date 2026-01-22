#include <stdio.h>
#include <math.h>

int a_n(int n)
{
    if(n == 1) return 1;  //初項 a1 = 1;
    
    return a_n(n-1) + (n-1);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("%d", a_n(n));
    return 0;
}