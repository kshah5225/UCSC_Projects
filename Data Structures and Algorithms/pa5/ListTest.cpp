//-----------------------------------------------------------------------------
// ListClient.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=10;
   List A, B, C;

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
A = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
A.position() = 0
A.length() = 10
B = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
B.position() = 0
B.length() = 10
C = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
C.position() = 0
C.length() = 0
A = (10, 9, 8, 19, 5, 4, 3, 2, 1, 6, 7, 22)
A.position() = 12
A.length() = 12
B = (10, 9, 8, 19, 5, 4, 3, 2, 1, 6, 7, 22)
B.position() = 8
B.length() = 8
C = (10, 9, 8, 19, 5, 4, 3, 2, 1, 6, 7, 22)
C.position() = 3
C.length() = 9
A==C is true
*/