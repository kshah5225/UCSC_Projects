// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "MatrixMath.h"

void MatrixPrint(float mat[3][3]){
    int n=1;
    int c=1;
    printf(" __");
    for(n=0;n<DIM;n=n+1){
        printf("______");
    }
    printf("\n");
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            printf("|");
            printf(" %.2f ",mat[n][c]);
        }
        printf("|");
        printf("\n");
    }
    printf(" --");
    for(n=0;n<DIM;n=n+1){
        printf("------");
    }
    printf("\n");
}

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    
    int n=1;
    int c=1;
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            if (mat1[n][c]-FP_DELTA < mat2[n][c] & mat2[n][c] < mat1[n][c]+FP_DELTA){
                //printf("%f != %f incorrect\n",mat1[n][c],mat2[n][c]);
            }else{
                //printf("%f < %f < %f incorrect\n",mat1[n][c]-FP_DELTA,mat2[n][c],mat1[n][c]+FP_DELTA);
                return 0;
            }
        }
    }
    return 1;
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int n=1;
    int c=1;
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            result[n][c] = mat1[n][c] + mat2[n][c];
        }
    }
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int n=1;
    int c=1;
    int r=1;
    float curr=0;
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            curr = 0;
            for(r=0;r<DIM;r=r+1){
                curr=curr+(mat1[n][r]*mat2[r][c]);
            }
            result[n][c]=curr;
        }
    }
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int n=1;
    int c=1;
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            result[n][c] = mat[n][c] + x;
        }
    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int n=1;
    int c=1;
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            result[n][c] = mat[n][c] * x;
        }
    }
}

float MatrixTrace(float mat[3][3])
{
    int n=1;
    float curr=0;
    for(n=0;n<DIM;n=n+1){
        //printf("%f\n",mat[n][n]);
        curr=curr+mat[n][n];
    }
    return curr;
}

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int n=1;
    int c=1;
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            result[n][c] = mat[c][n];
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    int n=1;
    int c=1;
    for(n=i;n<i+DIM-1;n=n+1){
        for(c=j;c<j+DIM-1;c=c+1){
            result[n-i][c-j] = mat[n][c];
        }
    }
}

float MatrixDeterminant(float mat[3][3])
{
    return (mat[0][0]*((mat[1][1]*mat[2][2])-(mat[1][2]*mat[2][1])))-(mat[0][1]*((mat[1][0]*mat[2][2])-(mat[1][2]*mat[2][0])))+(mat[0][2]*((mat[1][0]*mat[2][1])-(mat[1][1]*mat[2][0])));
}

void MatrixInverse(float mat[3][3], float result[3][3])
{
    result[0][0] =  (mat[1][1]*mat[2][2]) - (mat[1][2]*mat[2][1]);
    result[0][1] =-((mat[1][0]*mat[2][2]) - (mat[1][2]*mat[2][0]));
    result[0][2] =  (mat[1][0]*mat[2][1]) - (mat[1][1]*mat[2][0]);
    result[1][0] =-((mat[0][1]*mat[2][2]) - (mat[0][2]*mat[2][1]));
    result[1][1] =  (mat[0][0]*mat[2][2]) - (mat[0][2]*mat[2][0]);
    result[1][2] =-((mat[0][0]*mat[2][1]) - (mat[0][1]*mat[2][0]));
    result[2][0] =  (mat[0][1]*mat[1][2]) - (mat[0][2]*mat[1][1]);
    result[2][1] =-((mat[0][0]*mat[1][2]) - (mat[0][2]*mat[1][0]));
    result[2][2] =  (mat[0][0]*mat[1][1]) - (mat[0][1]*mat[1][0]);
    float tempdet = (mat[0][0]*((mat[1][1]*mat[2][2])-(mat[1][2]*mat[2][1])))-(mat[0][1]*((mat[1][0]*mat[2][2])-(mat[1][2]*mat[2][0])))+(mat[0][2]*((mat[1][0]*mat[2][1])-(mat[1][1]*mat[2][0])));
    int n=1;
    int c=1;
    for(n=0;n<DIM;n=n+1){
        for(c=0;c<DIM;c=c+1){
            mat[n][c] = result[c][n];
        }
    }
    MatrixScalarMultiply(1/tempdet,mat,result);
    
}