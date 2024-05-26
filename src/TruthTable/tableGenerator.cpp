#include "tableGenerator.h"
#include "logicCalculator.cpp"
#include <iostream>
#include <string>

using namespace std;

tableGenerator::tableGenerator(string * log, int n)
{
    logicArr = log;
    strcount = n;
    calc = new logicCalculator[n];
    for(int i=0; i<n; i++){
        calc[i].setEquation(log[i]);
    }
    generator();
}

void tableGenerator::generator()
{
    checkSize();


    cout << " +-----+-";
    for(int i=0; i<size; i++){
        cout << "--+-";
    }
    for(int i=0; i<strcount-1; i++){
        cout << "----+-";
    }
    cout << "----+\n |     | ";
    for(int i=0; i<size; i++){
        binarr[i] = 0;
        cout << tabHeader[i] << " | ";
    }
    for(int i=0; i<strcount; i++){
        cout << "OP" << i+1 << " | ";
    }
    cout << endl;

    cout << " +-----+-";
    for(int i=0; i<size; i++){
        cout << "--+-";
    }
    for(int i=0; i<strcount-1; i++){
        cout << "----+-";
    }
    
    counter = 0;
    loop( 0, 0);
    loop( 1, 0);
    cout << "----+" << endl;
}

void tableGenerator::loop(int a, int i)
{
    binarr[i] = a;

    if(i == size-1){
        cout << "----+\n";
        printf(" | %3d", counter++);
        cout << " | ";
        for(int i=0; i<size; i++)
            cout << binarr[i] << " | ";

        cout << " ";
        for(int i=0; i<strcount; i++){
            cout << calc[i].output(binarr) << "  |  ";
            if(calc[i].output(binarr) == 1){
                min = min + to_string(counter-1) + ", ";
            }    
        }
        cout << endl;

        cout << " +-----+-";
        for(int i=0; i<size; i++){
            cout << "--+-";
        }
        for(int i=0; i<strcount-1; i++){
            cout << "----+-";
        }
    }else{
        loop( 0, i+1);
        loop( 1, i+1);
    }

}

string tableGenerator::getstr()
{
    int n = min.length();
    --n;
    while(!(min[n] <= '9' && min[n] >= '0')){
        min = min.substr(0,n);
        --n;
    }
    return min;
}

void tableGenerator::checkSize()
{
    char arr[26];
    int count = 0;
    for(int i=0; i<26; i++){
        arr[i] = 0;
    }

    for(int j=0; j<strcount; j++){
        for(int i=0; i<logicArr[j].length(); i++){
            string logic = logicArr[j];
            char c = logic[i];
            if(isupper(c)){
                int ii = c - 'A';
                arr[ii] = 1;
            }else if(islower(c)){
                int ii = c - 'a';
                arr[ii] = 1;
            }
        }
    }
    for(int i=0; i<26; i++){
        if(arr[i] == 1)
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
    for(int i=0; i<strcount; i++){
        calc[i].setHeader(tabHeader, size);
    }
}
