//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string s;
   int x;
   string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par", "jar", "car" , "liar"};

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<11; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;

   B.setValue("bar", 9);
   B.setValue("car", 16);



   // call copy constructor
   Dictionary C = B;

   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << A.getValue("happy") << endl;
   A.getValue("happy") *= 10; // change the value associated with "happy"
   cout << A.getValue("happy") << endl << endl;
   A.remove("one");
   A.remove("two");
   B.remove("two");
   B.remove("car");



   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   // do forward iteration on B
   for(B.begin(); B.hasCurrent(); B.next()){
      s = B.currentKey();
      x = B.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   // do reverse iteration on C
   for(C.end(); C.hasCurrent(); C.prev()){
      s = C.currentKey();
      x = C.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   return( EXIT_SUCCESS );
}
/*
Expected Output:
A.size() = 11
bar : 4
car : 10
foo : 3
happy : 5
is : 6
jar : 9
liar : 11
one : 1
par : 8
three : 7
two : 2

B.size() = 11
bar : 4
car : 10
foo : 3
happy : 5
is : 6
jar : 9
liar : 11
one : 1
par : 8
three : 7
two : 2

B.size() = 13
bar : 9
car : 16
foo : 3
happy : 5
is : 6
jar : 9
liar : 11
one : 1
par : 8
three : 7
two : 2

C.size() = 11
bar : 9
car : 16
foo : 3
happy : 5
is : 6
jar : 9
liar : 11
one : 1
par : 8
three : 7
two : 2

A==B is false
B==C is true
C==A is false

5
50

A.size() = 9
bar : 4
car : 10
foo : 3
happy : 50
is : 6
jar : 9
liar : 11
par : 8
three : 7

par
foo
bar
car
happy
is
jar
liar
three

(bar, 9) (foo, 3) (happy, 5) (is, 6) (jar, 9) (liar, 11) (one, 1) (par, 8) (three, 7) 

(two, 2) (three, 7) (par, 8) (one, 1) (liar, 11) (jar, 9) (is, 6) (happy, 5) (foo, 3) (car, 16) (bar, 9) 
*/