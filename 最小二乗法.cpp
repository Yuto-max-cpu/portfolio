#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const int n = 7;  //データ点の個数
typedef double Matrix[100][100];

void print_matrix(Matrix A, int dim)
{
    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim+1; j++)
        {
            if(j == dim)
            {
                printf("| %8.3f", A[i][j]);
                continue;
            }
            printf("%8.3f ",A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double S_2m(double x[], int n, int m)  //左側行列の係数sの第m項を求める関数
{
    double sum = 0;

    for(int k=0; k<n; k++)
    {
        sum += pow(x[k], m);
    }

    return sum;
}

double t_m(double x[], double y[], int n, int m)  //右側行列の係数tを求める関数
{
    double sum = 0;

    for(int k=0; k<n; k++)
    {
        sum += pow(x[k],m) * y[k];
    }
    return sum;
}

void swapp_Mat(Matrix A,int i, int j, int dim)  //行列のi行目とj行目を交換する関数
{
    double temp[dim+1];
    for(int k=0; k<dim+1; k++)
    {
        temp[k] = A[i][k];
        A[i][k] = A[j][k];
        A[j][k] = temp[k];
    }
}

int find_max_pivot(Matrix A, double &pivot, int i, int dim)  //ピボットの最大値を選択する関数
{
    pivot = A[i][i];
    double max_pivot = fabs(A[i][i]);
    int max_index = i;

    if(i == dim-1)    //k=dim-1のときのバグ回避
    {
        pivot = A[i][i];
        return i;
    }

    for(int k=i; k<dim; k++)
    {
        if(max_pivot < fabs(A[k][i]) )
        {
            pivot = A[k][i];
            max_pivot = fabs(pivot);   //ピボット更新
            max_index = k;            //何行目にmax_pivotがあったかを格納
        }
    }

    return max_index;     //ピボット最大値を記憶し、何行目にあったかを返す。
}

void forward_elimination(Matrix A, int dim)  //前進消去法
{
    double pivot;    //ピボット格納
    int max_index;    //ピボット最大値がある行を格納

    for(int i=0; i<dim; i++)
    {
        max_index = find_max_pivot(A,pivot,i,dim);   //ピボット最大値取得
        printf("\nmax_pivot = %lf, max_index = %d\n", pivot, max_index+1);

        swapp_Mat(A,i,max_index,dim);               //ピボット最大値がある行と交換
        printf("\nChanged %d and %d\n\n",i+1,max_index+1);
        print_matrix(A,dim);

        for(int k=i+1; k<dim; k++)  //掃き出し計算。上三角行列を作る。
        {
            double temp = A[k][i]/ pivot;
            for(int l=0; l<dim+1; l++)
            {
                A[k][l] -= A[i][l] * temp;
            }
        }
        print_matrix(A,dim);
    }
}

void backward_substitution(Matrix A, double x[], int dim)  //後退代入
{
    for(int i=dim-1; i>=0; i--)
    {
        x[i] = A[i][dim];
        for(int j=i+1; j<dim; j++)
        {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

int main(int argc, char* argv[])
{
    double x[n] = {-3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0};
    double y[n] = {-3.0, -0.8, 1.2, -3.2, 2.5, 2.0, 3.8};
    Matrix A;

    if(argc != 2)
    {
        printf("Usage: a.exe number\n");
        exit(-1);
    }

    int m = atoi(argv[1]);  //コマンドラインから入力された近似する次数
    int dim = m + 1;

    double s[2*m+1];
    double t[m+1];

    for(int i=0; i<2*m+1; i++)  //sの項を作成
    {
        s[i] = S_2m(x,n,i);
    }

    for(int i=0; i<m+1; i++)  //tの項を作成
    {
        t[i] = t_m(x,y,n,i);
    }

    for(int i=0; i<=m; i++)  //s[i]を左側行列に変換
    {
        for(int j=0; j<=m; j++)
        {
            A[i][j] = s[i + j];
        }
    }

    for(int i=0; i<=m; i++)  //t[i]を右側のベクトルに変換
    {
        A[i][m+1] = t[i];
    }

    printf("---------solve this Eqation---------\n");
    print_matrix(A,dim);
    forward_elimination(A,dim);

    double a[m+1];    //求める近似曲線の係数
    backward_substitution(A,a,dim);

    printf("--------reslut----------\n\n");
    for(int i=0; i<m+1; i++)  //近似曲線の解をコマンドラインに表示
    {
        printf("a[i] = %f\n", a[i]);
    }
    return 0;
}