//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA4
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Matrix.h"
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct EntryObj* Entry;

// private NodeObj type
typedef struct EntryObj{
   int x;
   double data;
} EntryObj;

// private Matrix type
typedef struct MatrixObj* Matrix;

// private MatrixObj type
typedef struct MatrixObj{
    int n;
    int NNZ;
    List* matrix;
} MatrixObj;

// Exported types -------------------------------------------------------------
typedef struct MatrixObj* Matrix;
#define TOLERANCE 0.00001

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix R = malloc(sizeof(MatrixObj));
    R->n = n;
    R->NNZ = 0;
    R->matrix = calloc(n,sizeof(List));
    for(int i=0;i<n;i++){
        R->matrix[i] = newList();
        if(R->matrix[i]==NULL){
            printf("out of memory while assigning list");//shuld be unessecary
        }
    }
    return R;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if( pM!=NULL && *pM!=NULL ){
        for(int y = 1;y-1<(*pM)->n;y++){
            while(length((*pM)->matrix[y-1])!=0){
                free((front((*pM)->matrix[y-1])));
                deleteFront((*pM)->matrix[y-1]);
            }
        }
        for(int i=0;i<((*pM)->n);i++){
            freeList(&((*pM)->matrix[i]));
        }
        free((*pM)->matrix);
        free(*pM);
        //free(&pM);
    }
    *pM = NULL;
}

// Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M){
    return M->n;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if(A==B){
        return 1;
    }
    if(A->n!=B->n){
        return 0;
    }
    if(A->NNZ!=B->NNZ){
        return 0;
    }
    for(int y = 1;y-1<A->n;y++){
        moveFront(A->matrix[y-1]);
        moveFront(B->matrix[y-1]);
        while(index(A->matrix[y-1])!=-1){
            int Ax = ((Entry)(get(A->matrix[y-1])))->x;
            double Adata = ((Entry)(get(A->matrix[y-1])))->data;
            int Bx = ((Entry)(get(B->matrix[y-1])))->x;
            double Bdata = ((Entry)(get(B->matrix[y-1])))->data;
            if(!((Ax==Bx) && (Adata==Bdata))){
                return 0;
            }
            moveNext(A->matrix[y-1]);
            moveNext(B->matrix[y-1]);
        }
    }
    return 1;
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    for(int y = 1;y-1<M->n;y++){
        while(length(M->matrix[y-1])!=0){
            free((front(M->matrix[y-1])));
            deleteFront(M->matrix[y-1]);
        }
    }
    M->NNZ=0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (((x>-TOLERANCE) && (x<TOLERANCE))){//update this so it overides old non zero values with no value and free correctly
        if (length(M->matrix[i-1]) == 0){
            return;
        }else{
            moveFront(M->matrix[i-1]);
            while((((Entry)(get(M->matrix[i-1])))->x)<j){
                moveNext(M->matrix[i-1]);
                if (index(M->matrix[i-1])==-1){
                    return;
                }
                if((((Entry)(get(M->matrix[i-1])))->x)==j){
                    M->NNZ--;
                    free((get(M->matrix[i-1])));
                    delete(M->matrix[i-1]);
                    return;
                }
            }
            if((((Entry)(get(M->matrix[i-1])))->x)==j){
                M->NNZ--;
                free((get(M->matrix[i-1])));
                delete(M->matrix[i-1]);
                return;
            }
        }
    }

    if (length(M->matrix[i-1]) == 0){
        Entry N = malloc(sizeof(Entry));
        N->x = j;
        N->data = x;
        append(M->matrix[i-1],N);
        M->NNZ++;
    }else{
        moveFront(M->matrix[i-1]);
        while((((Entry)(get(M->matrix[i-1])))->x)<j){
            moveNext(M->matrix[i-1]);
            if(index(M->matrix[i-1])==-1){
                Entry N = malloc(sizeof(Entry));
                N->x = j;
                N->data = x;
                append(M->matrix[i-1],N);
                M->NNZ++;
                return;
            }
        }
        if((((Entry)(get(M->matrix[i-1])))->x)==j){
            if (((Entry)(get(M->matrix[i-1])))->data != x){
                ((Entry)(get(M->matrix[i-1])))->data = x;
            }
        }else{
            Entry N = malloc(sizeof(Entry));
            N->x = j;
            N->data = x;
            insertBefore(M->matrix[i-1],N);
            M->NNZ++;
        }
    }
}

// Matrix Arithmetic operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    Matrix R = newMatrix(A->n);
    for(int y = 1;y-1<A->n;y++){
        moveFront(A->matrix[y-1]);
        while(index(A->matrix[y-1])!=-1){
            int x = ((Entry)(get(A->matrix[y-1])))->x;
            double data = ((Entry)(get(A->matrix[y-1])))->data;
            changeEntry(R,y,x,data);
            moveNext(A->matrix[y-1]);          
        }
        if(A->NNZ==R->NNZ){
            break;
        }
    }
    return R;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    Matrix R = newMatrix(A->n);
    for(int y = 1;y-1<A->n;y++){
        moveFront(A->matrix[y-1]);
        while(index(A->matrix[y-1])!=-1){
            int x = ((Entry)(get(A->matrix[y-1])))->x;
            double data = ((Entry)(get(A->matrix[y-1])))->data;
            changeEntry(R,x,y,data);
            moveNext(A->matrix[y-1]);     
        }
        if(A->NNZ==R->NNZ){
            break;
        }
    }
    return R;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    Matrix R = newMatrix(A->n);
    for(int y = 1;y-1<A->n;y++){
        moveFront(A->matrix[y-1]);
        while(index(A->matrix[y-1])!=-1){
            int xint = ((Entry)(get(A->matrix[y-1])))->x;
            double data = ((Entry)(get(A->matrix[y-1])))->data;
            changeEntry(R,y,xint,data*x);
            moveNext(A->matrix[y-1]);          
        }
        if(A->NNZ==R->NNZ){
            break;
        }
    }
    return R;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (A==B){
        return scalarMult(2,A);
    }
    Matrix R = newMatrix(A->n);
    int ANNZ = 0;
    int BNNZ = 0;
    for(int y = 1;y-1<A->n;y++){
        if (length(A->matrix[y-1])>0){
            moveFront(A->matrix[y-1]);
        }
        if (length(B->matrix[y-1])>0){
            moveFront(B->matrix[y-1]);
        }
        int EA = A->n+1;
        int EB = B->n+1;
        //int EA = ((Entry)(get(A->matrix[y-1])))->x;
        //int EB = ((Entry)(get(B->matrix[y-1])))->x;
        while((index(A->matrix[y-1])!=-1)||(index(B->matrix[y-1])!=-1)){
            if (index(A->matrix[y-1])!=-1){
                EA = ((Entry)(get(A->matrix[y-1])))->x;
            }else{
                EA = A->n+1;
            }
            if (index(B->matrix[y-1])!=-1){
                EB = ((Entry)(get(B->matrix[y-1])))->x;
            }else{
                EB = B->n+1;
            }
            if(EA==EB){
                changeEntry(R,y,EA,((((Entry)(get(B->matrix[y-1])))->data)+(((Entry)(get(A->matrix[y-1])))->data)));
                moveNext(A->matrix[y-1]);
                moveNext(B->matrix[y-1]);
                ANNZ++;
                BNNZ++;
            }else if(EA>EB){
                changeEntry(R,y,EB,((((Entry)(get(B->matrix[y-1])))->data)));
                moveNext(B->matrix[y-1]);
                BNNZ++;
            }else if(EA<EB){
                changeEntry(R,y,EA,((((Entry)(get(A->matrix[y-1])))->data)));
                moveNext(A->matrix[y-1]);
                ANNZ++;
            }
        }
        if((A->NNZ==ANNZ) && (B->NNZ==BNNZ)){
            break;
        }
    }
    return R;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    Matrix R = newMatrix(A->n);
    if (A==B){
        return R;
    }
    int ANNZ = 0;
    int BNNZ = 0;
    for(int y = 1;y-1<A->n;y++){
        if (length(A->matrix[y-1])>0){
            moveFront(A->matrix[y-1]);
        }
        if (length(B->matrix[y-1])>0){
            moveFront(B->matrix[y-1]);
        }
        int EA = A->n+1;
        int EB = B->n+1;
        //int EA = ((Entry)(get(A->matrix[y-1])))->x;
        //int EB = ((Entry)(get(B->matrix[y-1])))->x;
        while((index(A->matrix[y-1])!=-1)||(index(B->matrix[y-1])!=-1)){
            if (index(A->matrix[y-1])!=-1){
                EA = ((Entry)(get(A->matrix[y-1])))->x;
            }else{
                EA = A->n+1;
            }
            if (index(B->matrix[y-1])!=-1){
                EB = ((Entry)(get(B->matrix[y-1])))->x;
            }else{
                EB = B->n+1;
            }
            if(EA==EB){
                changeEntry(R,y,EA,-(((((Entry)(get(B->matrix[y-1])))->data)-(((Entry)(get(A->matrix[y-1])))->data))));
                moveNext(A->matrix[y-1]);
                moveNext(B->matrix[y-1]);
                ANNZ++;
                BNNZ++;
            }else if(EA>EB){
                changeEntry(R,y,EB,-((((Entry)(get(B->matrix[y-1])))->data)));
                moveNext(B->matrix[y-1]);
                BNNZ++;
            }else if(EA<EB){
                changeEntry(R,y,EA,((((Entry)(get(A->matrix[y-1])))->data)));
                moveNext(A->matrix[y-1]);
                ANNZ++;
            }
        }
        if((A->NNZ==ANNZ) && (B->NNZ==BNNZ)){
            break;
        }
    }
    return R;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    Matrix BP = transpose(B);
    Matrix R = newMatrix(A->n);
    for(int y = 1;y-1<A->n;y++){
        for(int x = 1;x-1<A->n;x++){
            //printf("change entry:  x:%d  y:%d  D:%f\n",x,y,vectorDot(A->matrix[x-1],BP->matrix[y-1]));
            changeEntry(R,x,y,vectorDot(A->matrix[x-1],BP->matrix[y-1]));
        }
    }
    freeMatrix(&(BP));
    return R;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    for(int y = 1;y-1<M->n;y++){
        if(length(M->matrix[y-1])>0){
            fprintf(out,"%d:",y);
            moveFront(M->matrix[y-1]);
            while(index(M->matrix[y-1])!=-1){
                fprintf(out," (%d, %.1f)",((Entry)(get(M->matrix[y-1])))->x,((Entry)(get(M->matrix[y-1])))->data);  
                moveNext(M->matrix[y-1]);          
            }
            fprintf(out,"\n");
        }
    }
}

//helper function to multiply lists and then sum them
double vectorDot(List P, List Q){
    if(length(P)==0){
        return 0;
    }
    if(length(Q)==0){
        return 0;
    }
    double SUM = 0;
    int EP = length(P);
    int EQ = length(Q);
    moveFront(P);
    moveFront(Q);
    while((index(Q)!=-1)&&(index(P)!=-1)){
        if (index(P)!=-1){
            EP = ((Entry)(get(P)))->x;
        }else{
            EP = length(P)+1;
        }
        if (index(Q)!=-1){
            EQ = ((Entry)(get(Q)))->x;
        }else{
            EQ = length(Q)+1;
        }
        if(EQ==EP){
            SUM = SUM + ((((Entry)get(Q))->data)*(((Entry)get(P))->data));
            moveNext(P);
            moveNext(Q);
        }else if(EP<EQ){
            moveNext(P);
        }else if(EP>EQ){
            moveNext(Q);
        }
    }
    return(SUM);
}
