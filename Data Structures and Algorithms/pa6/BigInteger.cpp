//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<sstream>
#include<string>
#include<stdexcept>
#include"List.h"
#include"BigInteger.h"

#define POWER 9
#define BASE 1000000000

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if(""==s){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    int i = 0;
    if (s[i]=='+'){
        i++;
        signum = 1;
    }else if(s[i]=='-'){
        i++;
        signum = -1;
    }else{//unsure if this else statement is nessecary to run while
        int n=0;
        signum = 0;
        while(s[n]!='\0'){
            if(s[n]!='0'){
                signum = 1;
            }
            n++;
        }
    }
    if(s[i]=='\0'){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    while(s[i]!='\0'){
        int lengrab = ((s.length()-i)%(POWER));
        if (lengrab==0){
            lengrab=POWER;
        }
        std::string substr = s.substr(i,lengrab);
        //std::cout<<"i:"<<i<<"lengrab:"<<lengrab<<"string:"<<substr<<std::endl;
        digits.insertBefore(std::stoi(substr));
        i+=lengrab;
        if((digits.peekPrev()>(BASE-1))||(digits.peekPrev()<0)){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }
    digits.moveFront();
    while((digits.position()!=digits.length())){
        if(digits.moveNext()==0){
            digits.eraseBefore();
        }else{
            break;
        }
    }
    if(0==digits.length()){
        signum = 0;
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = N.digits;
}


// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if(((signum==1)&&(N.signum!=1))){
        return 1;
    }
    if((signum!=1)&&(N.signum==1)){
        return -1;
    }
    if((signum==0)&&(N.signum==0)){
        return 0;
    }
    if((signum==1)&&(N.signum==1)){
        if(digits.length()>N.digits.length()){
            return 1;
        }else if(digits.length()<N.digits.length()){
            return -1;
        }else{
            List OL = digits;
            List CL = N.digits;
            OL.moveFront();
            CL.moveFront();
            while(CL.position()!=CL.length()){
                int temp1 = OL.moveNext();
                int temp2 = CL.moveNext();
                if(temp1>temp2){
                    return 1;
                }
                if(temp1<temp2){
                    return -1;
                }
            }
            return 0;
        }
    }
    if((signum==-1)&&(N.signum==-1)){
        if(digits.length()>N.digits.length()){
            return -1;
        }else if(digits.length()<N.digits.length()){
            return 1;
        }else{
            List OL = digits;
            List CL = N.digits;
            OL.moveFront();
            CL.moveFront();
            while(CL.position()!=CL.length()){
                int temp1 = OL.moveNext();
                int temp2 = CL.moveNext();
                if(temp1>temp2){
                    return 1;
                }
                if(temp1<temp2){
                    return -1;
                }
            }
            return 0;
        }
    }
    std::cout << "send help1" << std::endl;
    std::cout << signum << *this << std::endl;
    std::cout << N.signum << N << std::endl;
    return 2;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
    digits.insertBefore(0);
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    signum = signum*(-1);
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger R = BigInteger();
    if((N.signum==0)&&(signum==0)){
        return R;
    }
    BigInteger I1 = *this;
    BigInteger I2 = N;
    if(I1.signum==I2.signum){
        //do normal addition
        R.signum = I1.signum;
        I1.digits.moveBack();
        I2.digits.moveBack();
        int temp_carry = 0;
        while((I1.digits.position()!=0)&&(I2.digits.position()!=0)){
            int temp = I1.digits.movePrev()+I2.digits.movePrev()+temp_carry;
            int temp_remainder = temp%BASE;
            R.digits.insertAfter(temp_remainder);
            temp_carry = temp/BASE;
        }
        while(I1.digits.position()!=0){
            int temp = I1.digits.movePrev()+temp_carry;
            int temp_remainder = temp%BASE;
            R.digits.insertAfter(temp_remainder);
            temp_carry = temp/BASE;
        }
        while(I2.digits.position()!=0){
            int temp = I2.digits.movePrev()+temp_carry;
            int temp_remainder = temp%BASE;
            R.digits.insertAfter(temp_remainder);
            temp_carry = temp/BASE;
        }
        while(temp_carry != 0){
            int temp = temp_carry;
            int temp_remainder = temp%BASE;
            R.digits.insertAfter(temp_remainder);
            temp_carry = temp/BASE;
        }
        R.digits.moveFront();
        while((R.digits.position()!=R.digits.length())){
            if(R.digits.moveNext()==0){
                R.digits.eraseBefore();
            }else{
                break;
            }
        }
        if(0==R.digits.length()){
            R.signum = 0;
        }
        return R;
    }else if((I1.signum==-1)&&(I2.signum==1)){
        I1.negate();
        return I2 - I1;
    }else if((I1.signum==1)&&(I2.signum==-1)){
        I2.negate();
        return I1 - I2;
    }else if((I1.signum==0)){
        return I2;
    }else if((I2.signum==0)){
        return I1;
    }
    BigInteger L = *this;
    std::cout << "send help2" << std::endl;
    std::cout << signum << *this << std::endl;
    std::cout << N.signum << N << std::endl;
    return L;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger R = BigInteger();
    if(this==&N){
        return R;
    }
    if((N.signum==0)&&(signum==0)){
        return R;
    }else if((N.signum==0)&&(signum==1)){
        R = *this;
        return R;
    }else if((N.signum==0)&&(signum==-1)){
        R = *this;
        return R;
    }else if((N.signum==1)&&(signum==0)){
        R = N;
        R.negate();
        return R;
    }else if((N.signum==-1)&&(signum==0)){
        R = *this;
        return R;
    }
    BigInteger I1 = *this;
    BigInteger I2 = N;
    if((N.signum==-1)&&(signum==1)){
        I2.negate();
        return I2+I1;
    }else if((N.signum==1)&&(signum==-1)){
        I1.negate();
        R=I1+I2;
        R.negate();
        return R;
    }else if(I1.signum==I2.signum){
        if((N.signum==-1)&&(signum==-1)){
            std::swap(I1, I2);
            I1.negate();
            I2.negate();
        }
        R.signum = 1;
        bool N2E = false;
        int comp = I1.compare(I2);
        if(comp==0){
            R.signum = 0;
            return R;
        }
        if(comp==-1){
            std::swap(I1, I2);
            N2E = true;
        }
        //do normal subtraction
        I1.digits.moveBack();
        I2.digits.moveBack();
        int temp_carry = 0;
        while((I2.digits.position()!=0)){
            int temp = I1.digits.movePrev()-I2.digits.movePrev()+temp_carry;
            int temp_remainder = temp%BASE;
            temp_carry = temp/BASE;
            while(temp_remainder<0){
                temp_remainder = temp_remainder + BASE;
                temp_carry--;
            }
            R.digits.insertAfter(temp_remainder);
        }
        while(I1.digits.position()!=0){
            int temp = I1.digits.movePrev()+temp_carry;
            int temp_remainder = temp%BASE;
            temp_carry = temp/BASE;
            while(temp_remainder<0){
                temp_remainder = temp_remainder + BASE;
                temp_carry--;
            }
            R.digits.insertAfter(temp_remainder);
        }
        if(N2E){
            R.negate();
        }
        R.digits.moveFront();
        while((R.digits.position()!=R.digits.length())){
            if(R.digits.moveNext()==0){
                R.digits.eraseBefore();
            }else{
                break;
            }
        }
        //std::cout<<"length:" << R.digits.length()<<std::endl;
        if(0==R.digits.length()){
            R.signum = 0;
        }
        return R;
    }
    BigInteger L = *this;
    std::cout << "send help3" << std::endl;
    std::cout << signum << *this << std::endl;
    std::cout << N.signum << N << std::endl;
    return L;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger I1 = *this;
    BigInteger I2 = N;
    BigInteger R = BigInteger();
    BigInteger T = BigInteger();
    int tempsignum = I1.signum * I2.signum;
    I1.signum = 1;
    I2.signum = 1;
    I2.digits.moveBack();
    int iteration = 0;
    while((I2.digits.position()!=0)){
        T.makeZero();
        int i = 0;
        while(i!=iteration){
            i++;
            T.digits.insertAfter(0);
        }
        T.signum = 1;
        I1.digits.moveBack();
        long long temp_carry = 0;
        long long n = I2.digits.movePrev();
        iteration++;
        while((I1.digits.position()!=0)){
            long long temp = (I1.digits.movePrev()*n)+temp_carry;
            long long temp_remainder = temp%BASE;
            T.digits.insertAfter(temp_remainder);
            temp_carry = temp/BASE;
        }
        while(temp_carry != 0){
            long long temp = temp_carry;
            long long temp_remainder = temp%BASE;
            T.digits.insertAfter(temp_remainder);
            temp_carry = temp/BASE;
        }
        //std::cout<<T<<std::endl;
        R+=T;
    }
    R.signum = tempsignum;
    //std::cout<<"final"<<R<<std::endl;
    R.digits.moveFront();
    while((R.digits.position()!=R.digits.length())){
        if(R.digits.moveNext()==0){
            R.digits.eraseBefore();
        }else{
            break;
        }
    }
    if(0==R.digits.length()){
        R.signum = 0;
    }
    return R;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::ostringstream os;
    if(signum==-1){
        os << "-";
    }
    os << digits;
    std::string str(os.str());
    return str;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    return (A.BigInteger::compare(B))==0;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    return (A.BigInteger::compare(B))==-1;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    return ((A.BigInteger::compare(B))==-1)||((A.BigInteger::compare(B))==0);//might//inefficientmight fix using temp bool
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    return (A.BigInteger::compare(B))==1;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    return ((A.BigInteger::compare(B))==1)||((A.BigInteger::compare(B))==0);//might//inefficientmight fix using temp bool
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    return A=A+B;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    return A=A-B;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    return A=A*B;
}

// operator=()
// Overwrites the state of this List with state of 
BigInteger& BigInteger::operator=( const BigInteger& L ){
    if(this != &L){ // not self assignment
      // make a copy of L
      BigInteger temp = L;

      // then swap the copy's fields with fields of this
      std::swap(signum, temp.signum);
      std::swap(digits, temp.digits);
   }

   // return this with the new data installed
   return *this;
}