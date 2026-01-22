#include <stdio.h>
#include <math.h>
#include <stdlib.h>  //atof関数

// ∫x＾2(1-x)dxを考える
typedef double fp(double);  //関数ポインタ

double func(double x)
{
    return -x*x + 10*x - 8 + sin(x)*sin(x);
}

double integral(fp* func, double a, double b, int N)  //区分求積法
{
    double h = (b - a) / N;
    double sum = 0.0;

    for(int i=0; i<N; i++)
    {
        sum += h * func(a + i * h);
    }

    return sum;
}

double trapezoid(fp* func, double a, double b, int N)  //台形則
{
    double h = (b - a) / N;
    double sum = 0.0;

    for(int i=0; i<N; i++)
    {
        double jotei = func(a + i * h);  //台形の上底
        double katei = func(a + (i + 1) * h);  // 台形の下底
        double takasa = h;  //台形の高さ

        sum += (jotei + katei) * takasa /2;
    }

    return sum;
}

double sympson(fp* func, double a, double b, int N)  //シンプソン則
{
    double h = (b - a) / N;
    double sum = 0.0;

    for(int i=0; i<N; i++)
    {
        double x_0 = a + i * h;
        double x_1 = a + (i + 0.5) * h;
        double x_2 = a + (i + 1) * h;

        sum += h / 6 * ( func(x_0) + 4 * func(x_1) + func(x_2) );
    }

    return sum;
}   

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: a.exe (iteration number)\n");
        exit(1);
    }

    double a = 0.813361;  //積分範囲
    double b = 9.133120;
    int N = atoi(argv[1]);
    printf("分割数は %d です。\n", N);

    double s_integral = integral(func,a,b,N);
    printf("区分求積法による解析結果は %f です。\n",s_integral);

    double s_trapezoid = trapezoid(func,a,b,N);
    printf("台形則による解析結果は %f です。\n", s_trapezoid);

    double s_sympson = sympson(func,a,b,N);
    printf("シンプソン則による解析結果は %f です。\n",s_sympson);

    return 0;
}


