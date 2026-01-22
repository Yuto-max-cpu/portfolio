#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("Usage: a.exe TXT\n");
        exit(-1);
    }

    char c;   //大文字変換用

    for(int i=0; argv[1][i] != '\0'; i++)  //\0はnull（文字列の終端）
    {
        c = argv[1][i];
        c -= 32;
        printf("%c", c);
    }

    printf("\n");

    for(int i=0; argv[1][i] != '\0'; i++)
    {
        c = argv[1][i];
        printf("%c -> %X\n", c,c);
    }

    return 0;
}