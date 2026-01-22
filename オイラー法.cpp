#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//振り子の運動方程式について解くプログラム//
typedef struct 
{
    double StartTime;  //シミュレーションの開始時間
    double EndTime;    //シミュレーションの終了時間
    double TimeStep;   //時間刻み幅
    int MaxIteration;  //最大繰り返し回数
} const SimCondition;  //シミュレーション条件に関する構造体

typedef struct 
{
    double length;    //振り子の紐の長さ
    double gravity;  //重力加速度
} const ModelInfo;

typedef struct 
{
    double theta;  //角度
    double omega;  //角速度
} const InitState; //初期条件

typedef struct 
{
    double time;   //時間
    double theta;  //角度
    double omega;  //角速度
} State;           //時間変数に関する構造体

double f1(double omega)  //dθ/dt = omega → dθ/dtを求める関数
{
    return omega;
}

double f2(double theta, ModelInfo model)  // dω/dt = -g/l * sin(theta) → dω/dtを求める関数
{
    return -model.gravity / model.length * sin(theta);
}
 
void Print_State(State state)  //状態量の表示
{
    printf("%6.4f\t% 6.4f\t% 6.4f\n", state.time, state.theta, state.omega);
}

int main(void)
{
    SimCondition sim_condition = { 0.0, 0.50, 0.00001, 1000000 };
    ModelInfo model = { 0.50, 9.81 };
    InitState init_state = {0.57, 0.0};

    State state = { sim_condition.StartTime, init_state.theta, init_state.omega};
    int i = 0;

    printf("Time\tTheta\tOmega\n");  //表示画面の初期化

    while (state.time <= sim_condition.EndTime && i < sim_condition.MaxIteration)
    {
        if(i%1000==0) Print_State(state);  //表示データの間引き

        //オイラー法
        double k_theta = f1(state.omega);
        double k_omega = f2(state.theta, model);
        state.theta += k_theta * sim_condition.TimeStep;
        state.omega += k_omega * sim_condition.TimeStep;

        state.time += sim_condition.TimeStep;
        i++;
    }

    //終了時刻の状態を表示
    Print_State(state);
    return 0;
}



