#include <stdio.h>
#include <stdlib.h>

void dec2bin(int x)
{
    const int BitSize = 8;  //整数型ビットサイズを算出
    const int bit = 1;
    int i;
    char c[BitSize];

    //2心数表示のための計算
    for(int i = 0; i<BitSize; i++)
    {
        c[i] = x & bit;  //最下位ビットを取り出せる操作
        x >>= 1;
    }

    //計算結果の表示
    printf(" Binary: ");
    for(int i = BitSize-1; i>=0; i--)
    {
        printf("%d",c[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s integer_number\n", argv[0]);
        exit(1);
    }
    int x = atoi(argv[1]);

    printf("Input integer number: %d\n\n", x);
    printf(" Hexadecimal: %x\n", x);
    printf(" Decimal: %d\n", x);
    dec2bin(x);
    return 0;
}