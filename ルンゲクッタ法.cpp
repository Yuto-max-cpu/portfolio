#include <stdio.h>
#include <math.h>

double DT = 0.0001;

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
    double omega_0 = 0.01;  // 初期条件 (θ_0 = 0, ω_0 = 0.1)

    double theta = theta_0;
    double omega = omega_0;  //時間変数に初期条件を代入
    double time = 0.0;

    int i = 0;
    while( time <= 5.0)  //0秒から5秒までの時間で微分方程式を解析する
    {
        double k1 = f1(omega);        //t=tでのθの傾き
        double l1 = f2(theta,omega);  //t=tでのωの傾き
        
        //k1,l1を使って t=t+dt/2 におけるθ,ωの傾きを求める。
        double k2 = f1(omega + l1 * DT / 2);
        double l2 = f2(theta + k1 * DT / 2, omega + l1 * DT / 2);

        //k2,l2を使って t=t+dt/2 におけるθ,ωの傾きを求める。
        double k3 = f1(omega + l2 * DT / 2);
        double l3 = f2(theta + k2 * DT / 2, omega + l2 * DT / 2);

        //k3,l3を使ってt=t+dtにおけるθ,ωの傾きを求める。
        double k4 = f1(omega + l3 * DT);
        double l4 = f2(theta + k3 * DT, omega + l3 * DT);

        //四つの重み平均づけ
        theta += (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0 * DT;
        omega += (l1 + 2.0*l2 + 2.0*l3 + l4) / 6.0 * DT;
        time += DT;

        if(i%100 == 0) printf("%f,%f,%f\n",time,theta,omega);
        i++;
    }

    return 0;
}