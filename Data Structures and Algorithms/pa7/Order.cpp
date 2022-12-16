//-----------------------------------------------------------------------------
// Shuffle.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<stdexcept>
#include<cmath>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){

    //initilization
    Dictionary A;

    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    fstream newfile;
    newfile.open(argv[1],ios::in);
    string tp;
    unsigned int i = 0;
    while(getline(newfile, tp)){ //read data from file object and put it into string.
        i++;
        A.setValue(tp,i);
    }
    newfile.close();
    ofstream writefile;
    writefile.open (argv[2]);
    writefile << A << A.pre_string();
    writefile.close();
}
