// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"

// Module-level variables:
float zero_matrix[3][3] = {{},{},{}};
float result2[2][2] = {{},{}};
float result3[3][3] = {{},{},{}};
float t1m[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
float t2m[3][3] = {{9,10,11},{12,13,14},{15,16,17}};
float t2mc[3][3] = {{9,10,11},{12,13,14},{15,16,17}};
float t3m[3][3] = {{1,2,3},{0,1,5},{5,6,0}};
float t4m[3][3] = {{2,4,3},{7,1,9},{1,4,3}};
float t1mxt2m[3][3] = {{42,45,48},{150,162,174},{258,279,300}};
float t2mxt3m[3][3] = {{64,94,77},{82,121,101},{100,148,125}};
float t1x3m[3][3] = {{0,3,6},{9,12,15},{18,21,24}};
float t2x5m[3][3] = {{45,50,55},{60,65,70},{75,80,85}};
float t1mplust2m[3][3] = {{9,11,13},{15,17,19},{21,23,25}};
float t2mplust3m[3][3] = {{10,12,14},{12,14,19},{20,22,17}};
float t1plus3m[3][3] = {{3,4,5},{6,7,8},{9,10,11}};
float t2plus5m[3][3] = {{14,15,16},{17,18,19},{20,21,22}};
float t1m3supneg1[3][3] = {{-6.0,18.0/5.0,7.0/5.0},{5.0,-3.0,-1.0},{-1.0,4.0/5.0,1.0/5.0}};
float t1m4supneg1[3][3] = {{1,0,-1},{4.0/11.0,-1.0/11.0,-1.0/11.0},{-9.0/11.0,4.0/33.0,26.0/33.0}};
float t1mtranspose[3][3] = {{0,3,6},{1,4,7},{2,5,8}};
float t2mtranspose[3][3] = {{9,12,15},{10,13,16},{11,14,17}};

int main()
{
    BOARD_Init();
    printf("Beginning kgshah's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    printf("Demonstrating MatrixPrint():\n");
    int numer = 0;
    int fnal = 0;
    
    numer = 0;
    numer = numer + MatrixEquals(t2m,t2mc);//MatrixEquals test 1
    if (MatrixEquals(t2m,t3m) == 0){numer = numer + 1;}//MatrixEquals test 2
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixEquals()\n",numer);
    
    numer = 0;
    MatrixMultiply(t1m,t2m,result3);
    numer = numer + MatrixEquals(t1mxt2m,result3);//MatrixMultiply test 1
    MatrixMultiply(t2m,t3m,result3);
    numer = numer + MatrixEquals(t2mxt3m,result3);//MatrixMultiply test 2
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixMultiply()\n",numer);
    
    numer = 0;
    MatrixScalarMultiply(3,t1m,result3);
    numer = numer + MatrixEquals(t1x3m,result3);//MatrixMultiply test 1
    MatrixScalarMultiply(5,t2m,result3);
    numer = numer + MatrixEquals(t2x5m,result3);//MatrixMultiply test 2
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixScalarMultiply()\n",numer);
    
    numer = 0;
    if (MatrixDeterminant(t1m)==0.0){numer=numer+1;}
    if (MatrixDeterminant(t3m)==5.0){numer=numer+1;}
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixDeterminant()\n",numer);
    
    numer = 0;
    MatrixAdd(t1m,t2m,result3);
    numer = numer + MatrixEquals(t1mplust2m,result3);//MatrixMultiply test 1
    MatrixAdd(t2m,t3m,result3);
    numer = numer + MatrixEquals(t2mplust3m,result3);//MatrixMultiply test 2
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixAdd()\n",numer);
    
    numer = 0;
    MatrixScalarAdd(3,t1m,result3);
    numer = numer + MatrixEquals(t1plus3m,result3);//MatrixMultiply test 1
    MatrixScalarAdd(5,t2m,result3);
    numer = numer + MatrixEquals(t2plus5m,result3);//MatrixMultiply test 2
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixScalarAdd()\n",numer);
    
    numer = 0;
    MatrixInverse(t3m,result3);
    numer = numer + MatrixEquals(t1m3supneg1,result3);//MatrixMultiply testMatrixInverse 1
    MatrixInverse(t4m,result3);
    numer = numer + MatrixEquals(t1m4supneg1,result3);//MatrixMultiply testMatrixInverse 2
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixInverse()\n",numer);
    
    numer = 0;
    MatrixTranspose(t1m,result3);
    numer = numer + MatrixEquals(t1mtranspose,result3);//MatrixMultiply testMatrixInverse 1
    MatrixTranspose(t2m,result3);
    numer = numer + MatrixEquals(t2mtranspose,result3);//MatrixMultiply testMatrixInverse 2
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixTranspose()\n",numer);
    
    numer = 0;
    if (MatrixTrace(t1m) == 12.0){numer=numer+1;}
    if (MatrixTrace(t2m) == 39.0){numer=numer+1;}
    if (numer==2){fnal=fnal+1;}//reporting to final fraction of functions passed
    printf("PASSED (%d/2): MatrixTrace()\n",numer);
    
    printf("-----------------------------\n%d out of 9 functions passed (%.1f%%).\n",fnal, (fnal/9.0)*100.0);
    
    printf("\nOutput of MatrixPrint():\n");
    MatrixPrint(t1m);
    printf("\nExpected output of MatrixPrint():\n ____________________\n| 0.00 | 1.00 | 2.00 |\n| 3.00 | 4.00 | 5.00 |\n| 6.00 | 7.00 | 8.00 |\n --------------------\n");

    
    
    BOARD_End();
    while (1);
}

