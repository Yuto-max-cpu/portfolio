#include <stdio.h>
#include <math.h>

//半径2の円の方程式

double circle_2(double x)
{
    return sqrt(4 - x * x);
}

int main(int argc, char* argv[])
{
    double a = 0.0;
    double b = 2.0;  //半径が2の円の1/4の部分の面積を求める。

    const double N = 100000000000.0;  //分割数
    double h = (b - a) / N;  //長方形の横の幅
    double s = 0.0;  //円の面積を格納する変数
    for(int i=0; i<N; i++)
    {
        s += h * circle_2(a + i * h);
    }

    printf("the Space of 1/4 area of circle is %.99f\n",s);
    return 0;
}
