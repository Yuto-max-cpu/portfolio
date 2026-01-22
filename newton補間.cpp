#include <stdio.h>

// ニュートン補間の係数を計算して表示
double newton(double x[], double y[], const int n,double x_)
{
    double w[1000];   // 作業用配列（差分を使う）
    double a[1000];
    double f_x = 0;
    double term;

    // y を w にコピー
    for (int i = 0; i < n; i++) 
    {
        w[i] = y[i];
    }

    // a[0] は y[0]
    a[0] = w[0];

    // 階差を使って a[1]～a[n-1] を求める
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            w[j] = (w[j] - w[j - 1]) / (x[j] - x[j - i]);
        }
        a[i] = w[i];
    }

    for(int i=0; i<n; i++)
    {
        term = 1.0;
        for(int j=0; j<i; j++)
        {
            term *= (x_ - x[j]);
        }

        f_x += a[i] * term;
    }

    return f_x;

}

int main(void)
{
    double x[3] = {0, 4, 8};
    double y[3] =  {1.2, -2.3, 6.4};
    int n = 3;
    double a[1000];

    for(double i = 0; i<=8.0; i += 0.1)
    {
        printf("x = %f ; f(x) = %f\n", i,newton(x,y,n,i));
    }

    return 0;
}
