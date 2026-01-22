#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double fp(double);

double func(double x)  //解く関数
{
    return -x*x + 10*x - 8 + sin(x)*sin(x);
}

double dfunc(double x)   //funcの微分
{
    return -2*x + 10 + 2*cos(x)*sin(x);
}

int newton(fp* func, fp* dfunc, double x_0, double &ans)
{
    int Max_iteration = 100;  //最大反復回数
    double x[Max_iteration] = {0};
    x[0] = x_0 - func(x_0) / dfunc(x_0);  //ニュートン法初項
    double EPS = 10e-6;    //収束判定値

    for(int i=0; i<Max_iteration-1; i++)
    {
        x[i+1] = x[i] - func(x[i]) / dfunc(x[i]);
        if(fabs(x[i+1] - x[i]) < EPS)
        {
            ans = x[i+1];
            return i+1;    //収束判定値で解けた場合は答えをansに格納し反復回数を返す。
        }
    }

    return -1;  //収束判定条件を満たさなかった場合は-1を返す。
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: a.exe number\n");
        exit(-1);
    }

    double x_0 = atof(argv[1]);
    double ans;
    int number_of_Iteration = newton(func,dfunc,x_0,ans);
    
    if(number_of_Iteration == -1)
    {
        printf("Cant solve by your number in EPS\n");
        exit(-2);
    }else{
        printf("Iteration number is %d\nanswer is %lf", number_of_Iteration,ans);
    }

    return 0;
}
