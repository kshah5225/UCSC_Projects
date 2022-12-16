//-----------------------------------------------------------------------------
// Kunal Shah, kgshah
// 2022 Spring CSE101 PA6
// Arithmetic.cpp
// Takes an input file and preforms a small varity of calculations in an output file
//
// compile:
//
//     make
//
//-----------------------------------------------------------------------------
#include<string>
#include<fstream>
#include<iostream>
#include <vector>
#include"BigInteger.h"

using namespace std;

int main(int argc, char * argv[]){

    //initilization
    BigInteger A,B,C,D,E,F,G;

    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    string filename("input.txt");
    std::vector<string> lines;
    string line;
    ifstream input_file(argv[1]);
    getline(input_file, line);
    A = BigInteger(line);
    getline(input_file, line);
    getline(input_file, line);
    B = BigInteger(line);
    input_file.close();

    
    D = BigInteger("2");
    E = BigInteger("3");
    F = BigInteger("9");
    G = BigInteger("16");


    ofstream writefile;
    writefile.open (argv[2]);
    writefile<<A<<endl<<endl<<B<<endl<<endl;
    C=A+B;
    writefile<<C<<endl<<endl;
    C=A-B;
    writefile<<C<<endl<<endl;
    C=A-A;
    writefile<<C<<endl<<endl;
    E = E*A;
    D = D*B;
    C=E-D;
    writefile<<C<<endl<<endl;
    C=A*B;
    writefile<<C<<endl<<endl;
    E=A*A;
    writefile<<E<<endl<<endl;
    D=B*B;
    writefile<<D<<endl<<endl;
    C=((E*E)*F)+(G*(B*D*D));
    writefile<<C<<endl<<endl;

    writefile.close();
    return 0;
}
