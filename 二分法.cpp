#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double fp(double);   //関数ポインタ

double func(double x)
{
    return 2*x*x*x - 4*x + 1;
}

int solve_bisection(fp* func, double low, double high, double &ans)   //二分法により解を求める関数
{
    int max_iteration = 100;  //反復回数の上限
    double EPS = 10e-6;  //収束判定値

    for(int i=0; i<max_iteration; i++)
    {
        double mid = (low + high) / 2.0;  //中点を計算
        if(func(mid) < 0)
        {
            low = mid;
        }else{
            high = mid;
        }

        if(fabs(low - high) < 10e-6)
        {
            ans = mid;
            return i+1;   //収束判定値に収まれば、解をansに格納し反復回数を返す。
        }
    }
    return -1;  //解が収束判定値に収まらなければ-1を返す。
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: a.exe number number");
        exit(-1);
    }
    double ans = 0.0;
    double num_1 = atof(argv[1]);
    double num_2 = atof(argv[2]);
    double low,high;

    if(func(num_1) * func(num_2) > 0)  //f(num_1)*f(num_2) > 0の場合は解けない。
    {
        printf("Cant solve in that scope\n");
        exit(-2);
    }else{
        if(func(num_1) < 0)
        {
            low = num_1;
            high = num_2;
        }else{
            low = num_2;
            high = num_1;
        }
    }

    int number_of_iteration = solve_bisection(func,low,high,ans);  //反復回数を格納する変数
    if(number_of_iteration == -1)
    {
        printf("Max iteration number is too small to slove this Eqation\n");
        exit(-3);
    }

    printf("Iteration number is %d\nThe answer of (f(x) = 0) is %lf\n", number_of_iteration, ans);
    return 0;
}