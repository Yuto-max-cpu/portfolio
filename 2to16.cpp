//＆（AND）演算子は0を優先するにょーん
//|（OR)演算子は1を優先するにょーん
//～（NOT)は1と0を入れ替えるだけだにょーん
//上の３つを踏まえて解く

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char binary[65];
    printf("2進数を入力してください（最大64桁）: ");
    scanf("%s", binary);

    // 2進数文字列 → 10進数に変換
    unsigned long decimal = strtoul(binary, NULL, 2);

    // 10進数と16進数に変換して表示
    printf("10進数: %lu\n", decimal);
    printf("16進数: %lX\n", decimal);

    return 0;
}


