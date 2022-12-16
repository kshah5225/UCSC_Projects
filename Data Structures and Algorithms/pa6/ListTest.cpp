//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=10;
   List A, B, C, D;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i+21);
      D.insertBefore(21-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();
   A.movePrev();
   A.movePrev();
   A.movePrev();
   C.moveNext();
   C.moveNext();
   C.moveNext();
   C.moveNext();
   C.moveNext();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=2; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "A==A is " << (A==A?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseBefore();
   B.eraseBefore();
   B.eraseAfter();
   B.eraseAfter();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=7; i--){
      A.insertAfter(i);
   }
   cout << "A = " << A << endl;
   for( i=1; i<=5; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;


   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
   }
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "A.length() = " << A.length() << endl;

   cout << "B = " << A << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "B.length() = " << B.length() << endl;

   cout << "C = " << A << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "C.length() = " << C.length() << endl;

   C = A;

   C.moveFront();
   C.moveNext();
   C.moveNext();
   C.moveNext();
   C.eraseAfter();
   C.eraseAfter();
   C.insertAfter(19);

   B.moveFront();
   B.eraseAfter();

   B.moveBack();
   B.eraseBefore();
   B.eraseBefore();
   B.insertBefore(22);

   A.clear();

   A = C.concat(B);

   A.cleanup();
   
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "A.length() = " << A.length() << endl;

   cout << "B = " << A << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "B.length() = " << B.length() << endl;

   cout << "C = " << A << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "C.length() = " << C.length() << endl;

    A=C;
   cout << "A==C is " << (A==C?"true":"false") << endl;


   return( EXIT_SUCCESS );
}
/*
Expected Output:
A = 10000000009000000008000000007000000006000000005000000004000000003000000002000000001
A.position() = 0
B = 1000000002000000003000000004000000005000000006000000007000000008000000009000000010
B.position() = 0
C = 22000000023000000024000000025000000026000000027000000028000000029000000030000000031
C.position() = 10
D = 20000000019000000018000000017000000016000000015000000014000000013000000012000000011
D.position() = 10

A = 10000000009000000008000000007000000006000000005000000004000000003000000002000000001
A.position() = 7
B = 1000000002000000003000000004000000005000000006000000007000000008000000009000000010
B.position() = 10
C = 22000000023000000024000000025000000026000000027000000028000000029000000030000000031
C.position() = 5
D = 20000000019000000018000000017000000016000000015000000014000000013000000012000000011
D.position() = 0

B: 10 9 8 7 6 5 4 
B.position() = 3

C: 27 28 
C.position() = 7

A==B is false
B==C is false
A==A is true
C==D is false
D==A is false

5
1000000002000000003000000004000000005000000006000000007000000008000000009000000010
1000000002000000009000000010
2
1
9000000010
0
-1
2
-1
0

A = 10000000009000000008000000007000000006000000005000000004000000007000000008000000009000000010000000003000000002000000001
12
A = 10000000009000000008000000007000000006000000005000000004000000003000000002000000001
8

E==A is true

F = 10000000009000000008000000007000000006000000005000000004000000003000000002000000001000000009000000010
length: 12
front: 10
back: 10
position: 0
peekNext: 10
10
peekNext: 9
9
peekNext: 8
8
peekNext: 7
7
peekNext: 6
6
peekNext: 5
5
peekNext: 4
4
F = -10000000100000000-20000000090000000-30000000080000000-40000000070000000-50000000060000000-60000000050000000-7000000004000000003000000002000000001000000009000000010

A = 10000000009000000008000000007000000006000000005000000004000000003000000010000000009000000008000000007000000006000000005000000004000000003000000002000000001000000002000000001
A.position() = 8
A.length() = 20
B = 10000000009000000008000000007000000006000000005000000004000000003000000010000000009000000008000000007000000006000000005000000004000000003000000002000000001000000002000000001
B.position() = 0
B.length() = 12
C = 10000000009000000008000000007000000006000000005000000004000000003000000010000000009000000008000000007000000006000000005000000004000000003000000002000000001000000002000000001
C.position() = 7
C.length() = 10
A = 10000000009000000008000000019000000005000000004000000003000000007000000006000000002000000001000000022
A.position() = 12
A.length() = 12
B = 10000000009000000008000000019000000005000000004000000003000000007000000006000000002000000001000000022
B.position() = 10
B.length() = 10
C = 10000000009000000008000000019000000005000000004000000003000000007000000006000000002000000001000000022
C.position() = 3
C.length() = 19
A==C is true
*/