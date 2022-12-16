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
#include"List.h"

//This function does a perfect shuffle by splitting 
//1 list into 2 lists in the middle then alternatly places the 
//items back into a cleared D list to be "returned"
void shuffle(List& D){
    List F = D;
    List S = D;
    int Flen = floor((F.length()+0.5)/2);
    int Slen = D.length()-Flen;
    F.moveBack();
    S.moveFront();
    while(F.length()!=Flen){
        F.eraseBefore();
    }
    while(S.length()!=Slen){
        S.eraseAfter();
    }
    F.moveFront();
    S.moveFront();
    D.clear();
    bool Sturn = true;
    while((F.position()!=F.length())||(S.position()!=S.length())){
        if(Sturn){
            D.insertBefore(S.moveNext());
            Sturn = false;
        }else{
            D.insertBefore(F.moveNext());
            Sturn = true;
        }
    }
}

int main (int argc, char * argv[]) {// reading input
    if( argc != 2 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }
    std::ofstream outfile;//determineing output file name
    int trysizes = std::stoi(argv[1])+1;
    std::ostringstream filename;
    filename <<"out"<<argv[1]<<".txt";
    std::string str(filename.str());
    outfile.open (str);
    int triedsizes = 1;
    outfile << "deck size       shuffle count" << std::endl << "------------------------------" << std::endl;//starting outfile headers
    List D;
    List DC;
    while(triedsizes<trysizes){//keep shuffling and outputing reasults for shuffles per identical list
        D.moveBack();
        DC.moveBack();
        D.insertBefore(triedsizes);//i know that the list dosent start at 0 but it should not matter
        DC.insertBefore(triedsizes);
        int attempts = 1;
        shuffle(D);
        while(!(D==DC)){
            attempts++;
            shuffle(D);
        }
        triedsizes++;
        outfile << triedsizes-1 <<" \t\t" << attempts << std::endl;
    }
    outfile.close();
    return 0;
}