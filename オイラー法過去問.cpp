#include <stdio.h>
#include <math.h>

double DT = 0.0001;  //時間刻み幅

double f1(double omega)  // dθ/dt = omega → θの傾きを求める関数
{
    return omega;
}

double f2(double theta, double omega)  //  dω/dt = 1-(2cosθ)*ω-10*θ → ωの傾きを求める関数
{
    return 1 - (2*cos(theta)) * omega - 10*theta;
}

int main(void)
{
    double theta_0 = 0.1;
    double omega_0 = 0.01;  // 初期角速度をわずかに変更 (例: 0.0 -> 0.01)

    double theta = theta_0;
    double omega = omega_0;  //時間変数に初期条件を代入
    double time = 0.0;

    int i = 0;
    while( time <= 5.0)  //0秒から5秒までの時間で微分方程式を解析する
    {
        double d_theta = f1(omega);
        double d_omega = f2(theta,omega);
        theta += d_theta * DT;
        omega += d_omega * DT;

        if(i%100 == 0) printf("%4.2f\t% 5.3f\t% 5.3f\n", time, theta, omega);
        i++;
        time += DT;
    }

    return 0;
}