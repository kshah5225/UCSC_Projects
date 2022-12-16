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
#include<algorithm>
#include<cctype>
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
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    while(getline(newfile, tp)){ //read data from file object and put it into string.
        //cout<<"NEW LINE:  "<<tp<<endl;
        size_t tpite = 0;
        size_t Ntpite = 0;
        while (Ntpite<tp.length()){
            Ntpite = tp.find_first_of(delim,tpite);
            //cout<<tp.substr(tpite,Ntpite-tpite)<<" tpite: "<<tpite<<"    Ntpite: "<<Ntpite<<endl;
            string data = tp.substr(tpite,Ntpite-tpite);
            transform(data.begin(), data.end(), data.begin(),
                [](unsigned char c){ return std::tolower(c); });
            if(A.contains(data)){
                A.getValue(data)++;
            }else{
                A.setValue(data,1);
            }
            tpite = Ntpite+1;
        }
    }
    if(A.contains("")){
        A.remove("");
    }
    newfile.close();
    ofstream writefile;
    writefile.open (argv[2]);
    writefile << A << endl;
    writefile.close();
}
