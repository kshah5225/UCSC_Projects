//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "541285785709695684572346635689568";
   string s2 = "-47502391247580988676584786987";

   //BigInteger N;
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s2);

   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << endl;

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   BigInteger C = A+B;
   cout << "C = " << C << endl;

   BigInteger D = B+A;
   cout << "D = " << D << endl;
   cout << "(C==D) = " << ((C==D)?"True":"False") << endl;

   BigInteger E = A-A;
   cout << "E = " << E << endl;

   BigInteger F = B-A;
   cout << "F = " << F << endl;

   BigInteger G = A*B;
   cout << "G = " << G << endl;

   BigInteger H = B*A;
   cout << "H = " << H << endl;
   cout << "(G==H) = " << ((G==H)?"True":"False") << endl;

   BigInteger I = C*E;
   cout << "I = " << I << endl << endl;

   cout << endl;

   A += B;
   B -= C;
   C *= D;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << A*B*C*D*F*G*H << endl << endl;

   cout << endl;

   return EXIT_SUCCESS;
}
/*
Expected Output:
A = 541285785709695684572346635689568
B = -47502391247580988676584786987

(A==B) = False
(A<B)  = False
(A<=B) = False
(A>B)  = True
(A>=B) = True

C = 541238283318448103583670050902581
D = 541238283318448103583670050902581
(C==D) = True
E = 0
F = -541333288100943265561023220476555
G = -25712369169536246882156744465303734666561597431936457138051616
H = -25712369169536246882156744465303734666561597431936457138051616
(G==H) = True
I = 0


A = 541238283318448103583670050902581
B = -541285785709695684572346635689568
C = 292938879329500698717872645054106931733197442828307495612752461561

16623772156677919008052067877000895613715103124505540476796511394270960608134524594061014789398763762244281242816582177573379491489583429568577539793607037242527760998623422949595052997222374586753068784765529388173345693532855295800412820008173312627712910240991131741547767943872619355083798076521765820866785781514240
*/