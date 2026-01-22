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

void gauss_jordan(Matrix A)
{
    double pivot;
    int max_index;   //ピボット最大値が何行目にあったかを記録する変数

    for(int i=0; i<dim; i++)
    {
        max_index = find_max_pivot(A,pivot, i);
        printf("max_index is %d,max_pivot is %f\n", max_index+1, pivot);

        swapp_Mat(A,i,max_index);                 //ピボット最大値を見つけた行と交換する。
        printf("\nChange row %d and row %d\n",i+1,max_index+1);
        print_matrix(A);

        printf("\nall the element of row %d was devided with %f\n",i+1,pivot);
        for(int j=0; j<dim+1; j++)
        {
            A[i][j] /= pivot;      //i行目の要素をすべてpivotで割り、先頭の要素を1にする
        }
        print_matrix(A);

        printf("\nsubtract all the element of row %d from that of row 1 ~ 4\n",i+1);
        for(int k=0; k<dim; k++)  //掃き出し計算
        {
            if(k != i)
            {
                double temp = A[k][i];   //k行目の先頭の項を一時保存
                for(int l=0; l<dim+1; l++)
                {
                    A[k][l] -= temp * A[i][l];
                }
            }
        }
        print_matrix(A);
    }

    printf("---------result----------\n");
    for(int i=0; i<dim; i++)
    {
        printf("x[%d] = %lf\n", i+1, A[i][dim]);
    }
}

int main(void)
{
    Matrix A = { 
        { 2, 1, 3, 1, -2} ,
        { -1, 2, -2, -3, 5},
        { 1, -3, 1, 2, -7},
        { -3, 1, 1, 4, 11}
    };

    print_matrix(A);
    gauss_jordan(A);
    return 0;
}