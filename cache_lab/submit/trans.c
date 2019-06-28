/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]){
    int i,j,k,h,temp0,temp1,temp2,temp3,temp4,temp5,temp6,temp7;
    if(M==32&&N==32){
        for(i=0;i<32;i=i+8){
            for(j=0;j<32;j=j+8){
                if(i==j){
                    temp0=A[i][j];
                    temp1=A[i][j+1];
                    temp2=A[i][j+2];
                    temp3=A[i][j+3];
                    temp4=A[i][j+4];
                    temp5=A[i][j+5];
                    temp6=A[i][j+6];
                    temp7=A[i][j+7];

                    B[i][j]=temp0;
                    B[i][j+1]=temp1;
                    B[i][j+2]=temp2;
                    B[i][j+3]=temp3;
                    B[i][j+4]=temp4;
                    B[i][j+5]=temp5;
                    B[i][j+6]=temp6;
                    B[i][j+7]=temp7;

                    temp0=A[i+1][j];
                    temp1=A[i+1][j+1];
                    temp2=A[i+1][j+2];
                    temp3=A[i+1][j+3];
                    temp4=A[i+1][j+4];
                    temp5=A[i+1][j+5];
                    temp6=A[i+1][j+6];
                    temp7=A[i+1][j+7];

                    B[i+1][j]=B[j][i+1];
                    B[i][j+1]=temp0;
                    B[i+1][j+1]=temp1;
                    B[i+1][j+2]=temp2;
                    B[i+1][j+3]=temp3;
                    B[i+1][j+4]=temp4;
                    B[i+1][j+5]=temp5;
                    B[i+1][j+6]=temp6;
                    B[i+1][j+7]=temp7;

                    temp0=A[i+2][j];
                    temp1=A[i+2][j+1];
                    temp2=A[i+2][j+2];
                    temp3=A[i+2][j+3];
                    temp4=A[i+2][j+4];
                    temp5=A[i+2][j+5];
                    temp6=A[i+2][j+6];
                    temp7=A[i+2][j+7];

                    B[i+2][j]=B[j][i+2];
                    B[i+2][j+1]=B[j+1][i+2];
                    B[i][j+2]=temp0;
                    B[i+1][j+2]=temp1;
                    B[i+2][j+2]=temp2;
                    B[i+2][j+3]=temp3;
                    B[i+2][j+4]=temp4;
                    B[i+2][j+5]=temp5;
                    B[i+2][j+6]=temp6;
                    B[i+2][j+7]=temp7;
                    
                    temp0=A[i+3][j];
                    temp1=A[i+3][j+1];
                    temp2=A[i+3][j+2];
                    temp3=A[i+3][j+3];
                    temp4=A[i+3][j+4];
                    temp5=A[i+3][j+5];
                    temp6=A[i+3][j+6];
                    temp7=A[i+3][j+7];

                    B[i+3][j]=B[j][i+3];
                    B[i+3][j+1]=B[j+1][i+3];
                    B[i+3][j+2]=B[j+2][i+3];
                    B[i][j+3]=temp0;
                    B[i+1][j+3]=temp1;
                    B[i+2][j+3]=temp2;
                    B[i+3][j+3]=temp3;
                    B[i+3][j+4]=temp4;
                    B[i+3][j+5]=temp5;
                    B[i+3][j+6]=temp6;
                    B[i+3][j+7]=temp7;

                    temp0=A[i+4][j];
                    temp1=A[i+4][j+1];
                    temp2=A[i+4][j+2];
                    temp3=A[i+4][j+3];
                    temp4=A[i+4][j+4];
                    temp5=A[i+4][j+5];
                    temp6=A[i+4][j+6];
                    temp7=A[i+4][j+7];

                    B[i+4][j]=B[j][i+4];
                    B[i+4][j+1]=B[j+1][i+4];
                    B[i+4][j+2]=B[j+2][i+4];
                    B[i+4][j+3]=B[j+3][i+4];
                    B[i][j+4]=temp0;
                    B[i+1][j+4]=temp1;
                    B[i+2][j+4]=temp2;
                    B[i+3][j+4]=temp3;
                    B[i+4][j+4]=temp4;
                    B[i+4][j+5]=temp5;
                    B[i+4][j+6]=temp6;
                    B[i+4][j+7]=temp7;

                    temp0=A[i+5][j];
                    temp1=A[i+5][j+1];
                    temp2=A[i+5][j+2];
                    temp3=A[i+5][j+3];
                    temp4=A[i+5][j+4];
                    temp5=A[i+5][j+5];
                    temp6=A[i+5][j+6];
                    temp7=A[i+5][j+7];

                    B[i+5][j]=B[j][i+5];
                    B[i+5][j+1]=B[j+1][i+5];
                    B[i+5][j+2]=B[j+2][i+5];
                    B[i+5][j+3]=B[j+3][i+5];
                    B[i+5][j+4]=B[j+4][i+5];
                    B[i][j+5]=temp0;
                    B[i+1][j+5]=temp1;
                    B[i+2][j+5]=temp2;
                    B[i+3][j+5]=temp3;
                    B[i+4][j+5]=temp4;
                    B[i+5][j+5]=temp5;
                    B[i+5][j+6]=temp6;
                    B[i+5][j+7]=temp7;

                    temp0=A[i+6][j];
                    temp1=A[i+6][j+1];
                    temp2=A[i+6][j+2];
                    temp3=A[i+6][j+3];
                    temp4=A[i+6][j+4];
                    temp5=A[i+6][j+5];
                    temp6=A[i+6][j+6];
                    temp7=A[i+6][j+7];

                    B[i+6][j]=B[j][i+6];
                    B[i+6][j+1]=B[j+1][i+6];
                    B[i+6][j+2]=B[j+2][i+6];
                    B[i+6][j+3]=B[j+3][i+6];
                    B[i+6][j+4]=B[j+4][i+6];
                    B[i+6][j+5]=B[j+5][i+6];
                    B[i][j+6]=temp0;
                    B[i+1][j+6]=temp1;
                    B[i+2][j+6]=temp2;
                    B[i+3][j+6]=temp3;
                    B[i+4][j+6]=temp4;
                    B[i+5][j+6]=temp5;
                    B[i+6][j+6]=temp6;
                    B[i+6][j+7]=temp7;

                    temp0=A[i+7][j];
                    temp1=A[i+7][j+1];
                    temp2=A[i+7][j+2];
                    temp3=A[i+7][j+3];
                    temp4=A[i+7][j+4];
                    temp5=A[i+7][j+5];
                    temp6=A[i+7][j+6];
                    temp7=A[i+7][j+7];

                    B[i+7][j]=B[j][i+7];
                    B[i+7][j+1]=B[j+1][i+7];
                    B[i+7][j+2]=B[j+2][i+7];
                    B[i+7][j+3]=B[j+3][i+7];
                    B[i+7][j+4]=B[j+4][i+7];
                    B[i+7][j+5]=B[j+5][i+7];
                    B[i+7][j+6]=B[j+6][i+7];
                    B[i][j+7]=temp0;
                    B[i+1][j+7]=temp1;
                    B[i+2][j+7]=temp2;
                    B[i+3][j+7]=temp3;
                    B[i+4][j+7]=temp4;
                    B[i+5][j+7]=temp5;
                    B[i+6][j+7]=temp6;
                    B[i+7][j+7]=temp7;

                }
                else{
                    for(k=i;k<i+8;++k){                  
                        temp0=A[k][j];
                        temp1=A[k][j+1];
                        temp2=A[k][j+2];
                        temp3=A[k][j+3];
                        temp4=A[k][j+4];
                        temp5=A[k][j+5];
                        temp6=A[k][j+6];
                        temp7=A[k][j+7];
                        B[j][k]=temp0;
                        B[j+1][k]=temp1;
                        B[j+2][k]=temp2;
                        B[j+3][k]=temp3;
                        B[j+4][k]=temp4;
                        B[j+5][k]=temp5;
                        B[j+6][k]=temp6;
                        B[j+7][k]=temp7;
                    }
                }
            }
        }
    }
    else if(M==64&&N==64){
        for(i=0;i<64;i=i+8){
            for(j=0;j<64;j=j+8){
                for(k=i;k<i+4;++k){
                    temp0=A[k][j];
                    temp1=A[k][j+1];
                    temp2=A[k][j+2];
                    temp3=A[k][j+3];
                    temp4=A[k][j+4];
                    temp5=A[k][j+5];
                    temp6=A[k][j+6];
                    temp7=A[k][j+7];

                    B[j][k]=temp0;
                    B[j+1][k]=temp1;
                    B[j+2][k]=temp2;
                    B[j+3][k]=temp3;

                    B[j][k+4]=temp4;
                    B[j+1][k+4]=temp5;
                    B[j+2][k+4]=temp6;
                    B[j+3][k+4]=temp7;
                }
                for(k=j;k<j+4;++k){
                    temp0=A[i+4][k];
                    temp1=A[i+5][k];
                    temp2=A[i+6][k];
                    temp3=A[i+7][k];

                    temp4=B[k][i+4];
                    temp5=B[k][i+5];
                    temp6=B[k][i+6];
                    temp7=B[k][i+7];

                    B[k][i+4]=temp0;
                    B[k][i+5]=temp1;
                    B[k][i+6]=temp2;
                    B[k][i+7]=temp3;

                    B[k+4][i]=temp4;
                    B[k+4][i+1]=temp5;
                    B[k+4][i+2]=temp6;
                    B[k+4][i+3]=temp7;
                }
                for(k=i+4;k<i+8;++k){
                    temp0=A[k][j+4];
                    temp1=A[k][j+5];
                    temp2=A[k][j+6];
                    temp3=A[k][j+7];

                    B[j+4][k]=temp0;
                    B[j+5][k]=temp1;
                    B[j+6][k]=temp2;
                    B[j+7][k]=temp3;
                }
            }
        }
    }
    else if(M==61&&N==67){
        for(i=0;i<67;i=i+18){
            for(j=0;j<61;j=j+17){
                for(k=i;k<67&&k<i+18;++k){
                    for(h=j;h<61&&h<j+17;++h){
                        B[h][k]=A[k][h];
                    } 
                }
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}
