#include <stdio.h>
#include <stdlib.h>

int main() {
    char hex[17];  // 最大16桁の16進数（64ビット分）+ '\0'
    printf("16進数を入力してください（最大16桁）: ");
    scanf("%s", hex);

    // 16進数文字列 → 10進数に変換
    unsigned long decimal = strtoul(hex, NULL, 16);
    
    // 10進数表示
    printf("10進数: %lu\n", decimal);

    // 2進数表示（上位ビットから1つずつチェック）
    printf("2進数: ");
    int leading_zero = 1;
    for (int i = sizeof(unsigned long) * 8 - 1; i >= 0; i--) {
        int bit = (decimal >> i) & 1;
        if (bit == 1) leading_zero = 0;
        if (!leading_zero) printf("%d", bit);
    }
    if (leading_zero) printf("0"); // 入力が0だったとき
    printf("\n");

    return 0;
}
