#include <stdio.h>
#include <math.h>

const int N = 10000;   //サンプリング周波数1000Hzで10秒記録 → N = 10000個のデータ

double File_read(double data[], int N)
{
    FILE* fp = fopen("acc_data.txt", "r"); 
    if(fp == NULL)  //ファイルが開けなかったら-1を返す。
    {
        return -1;
    }

    for(int i=0; i<N; i++)   //data[i]にデータを格納
    {
        fscanf(fp, "%lf\n", &data[i]);
    }

    fclose(fp);
    return 0;    //正常に開けたら0を返す。
}

int main(void)
{
    double data[N] = {0};
    if(File_read(data, N) == -1)
    {
        printf("Cant Open File\n");
        exit(1);
    }

    double a = 0.0;
    double b = 10.0;  //計測時間が0~10秒
    double h = (b - a) / N;
    double v_velo[N];
    v_velo[0] = 0.0;  //速度の初期条件

    for(int i=0; i<N-1; i++)
    {
        double jotei = data[i];
        double katei = data[i+1];
        double height = h;
        v_velo[i+1] = v_velo[i] + (jotei + katei) * height /2;
    }

    FILE *fp1;
    fp1 = fopen("velocity.csv", "w");

    for(int i=0; i<N; i++)
    {
        fprintf(fp1, "%f,%f\n", h*i, v_velo[i]);
    }

    fclose(fp1);
    return 0;
}
