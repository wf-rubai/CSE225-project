#include "tableGenerator.h"
#include<iostream>
#include<string>

using namespace std;

tableGenerator::tableGenerator(string log)
{
    logic = log;
    generator();
}

void tableGenerator::generator()
{
    checkSize();

    for(int i=0; i<size; i++){
        binarr[i] = 0;
        cout << tabHeader[i] << "  ";
    }
    cout << endl;

    loop( 0, 0);
    loop( 1, 0);
}

void tableGenerator::loop(int a, int i)
{
    binarr[i] = a;

    if(i == size-1){
        for(int i=0; i<size; i++)
            cout << binarr[i] << "  ";
        cout << endl;
    }else{
        loop( 0, i+1);
        loop( 1, i+1);
    }

}

void tableGenerator::checkSize()
{
    char arr[26];
    int count = 0;
    for(int i=0; i<26; i++){
        arr[i] = 0;
    }

    for(char c: logic){
        if(isupper(c)){
            int ii = c - 'A';
            arr[ii] = 1;
        }else if(islower(c)){
            int ii = c - 'a';
            arr[ii] = 1;
        }
    }
    for(char c: arr){
        if(c == 1)
            count++;
    }
    tabHeader = new char[count];
    binarr = new int[count];
    size = count;

    count = 0;
    for(int i=0; i<26; i++){
        if(arr[i] == 1){
            tabHeader[count] = 'A' + i;
            count++;
        }
    }
}
