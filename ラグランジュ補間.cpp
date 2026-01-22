#include <stdio.h>
#include <math.h>

double lagrange(double data_x[], double data_y[],double x, int n)  //ラグランジュ補間の関数
{
    double sum_1 = 1.0;  //総積記号（Π）用
    double sum_2 = 0.0;  //普通の総和（シグマ）用
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i == j) continue;

            sum_1 *= (x - data_x[j]) / (data_x[i] - data_x[j]);   //総積計算
        }
        sum_2 += sum_1 * data_y[i];  //総和（シグマ）計算
        sum_1 = 1.0;  //必ず1に初期化する。次の総積計算に影響を与える。
    }

    return sum_2;
}

int main(void)
{
    double x[3] = {0, 4, 8};
    double y[3] = {1.2, -2.3, 6.4};
    int n = 3;   //データの個数

    for(int i=0; i<=80; i++)  //0~8まで0.1刻みで補間する。
    {
        double a = i * 0.1;
        printf("%lf, %lf\n",a,lagrange(x,y,a,n));
    }

    return 0;
}