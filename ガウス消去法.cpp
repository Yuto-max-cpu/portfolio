#include <stdio.h>
#include <math.h>

const int dim = 4;
typedef double Matrix[dim][dim+1];

void print_matrix(Matrix A)  //行列Aを出力する関数
{
    for(int i=0; i<dim; i++)
    {
        for(int j=0; j<dim+1; j++)
        {
            if(j==dim) {
                printf("|%8.3f ",A[i][j]);
            }else{
                printf("%8.3f ",A[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void swapp_Mat(Matrix A,int i, int j)  //行列のi行目とj行目を交換する関数
{
    double temp[dim+1];
    for(int k=0; k<dim+1; k++)
    {
        temp[k] = A[i][k];
        A[i][k] = A[j][k];
        A[j][k] = temp[k];
    }
}

int find_max_pivot(Matrix A, double &pivot, int i)  //ピボットの最大値を選択する関数
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

void forward_elimination(Matrix A)  //前進消去法
{
    double pivot;    //ピボット格納
    int max_index;    //ピボット最大値がある行を格納

    for(int i=0; i<dim; i++)
    {
        max_index = find_max_pivot(A,pivot,i);   //ピボット最大値取得
        printf("\nmax_pivot = %lf, max_index = %d\n", pivot, max_index+1);

        swapp_Mat(A,i,max_index);               //ピボット最大値がある行と交換
        printf("\nChanged %d and %d\n\n",i+1,max_index+1);
        print_matrix(A);

        for(int k=i+1; k<dim; k++)  //掃き出し計算。上三角行列を作る。
        {
            double temp = A[k][i]/ pivot;
            for(int l=0; l<dim+1; l++)
            {
                A[k][l] -= A[i][l] * temp;
            }
        }
        print_matrix(A);
    }
}

void backward_substitution(Matrix A, double x[])  //後退代入
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
    if(argc != 3)
    {
        printf("Usage: a.exe .txt .txt\n");
        exit(-1);
    }

    FILE* fp1;
    FILE* fp2;
    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    if(fp1 == NULL || fp2 == NULL)
    {
        printf("Cant Open File\n");
        exit(-2);
    }

    Matrix A;
    for(int i=0; i<dim; i++)  //A4_mat.csvから行列読み込み
    {
        for(int j=0; j<dim; j++)
        {
            fscanf(fp1,"%lf,",&A[i][j]);
        }
    }

    for(int i=0; i<dim; i++)   //b4_vec.csvからベクトル読み込み
    {
        fscanf(fp2, "%lf,", &A[i][dim]);
    }

    fclose(fp1);
    fclose(fp2);

    printf("-----------solve this Eqation----------\n\n");
    print_matrix(A);
    forward_elimination(A);

    double x[dim];
    backward_substitution(A,x);

    printf("--------answer---------\n");
    for(int i=0; i<dim; i++)
    {
        printf("x[%d] = %lf\n", i+1, x[i]);
    }
    return 0;
}