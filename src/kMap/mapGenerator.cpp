#include "mapGenerator.h"
#include "Imports/QMC_Algorithm.cpp"
#include <iostream>
#include <string>

mapGenerator::mapGenerator(string str, string str1)
{
    strConverter(str, str1);
}

void mapGenerator::strConverter(string str, string str1)
{
    int count = 0;
    dc = 0;
    for(int i=0; i<str.length(); i++){      /// removing all spaces for str
        if(str[i] != ' '){
            str[count++] = str[i];
        }
    }
    str = str.substr(0, count);
    for(int i=0; i<str1.length(); i++){      /// removing all spaces for str1
        if(str1[i] != ' '){
            str1[dc++] = str1[i];
        }
    }
    str1 = str1.substr(0, dc);
    arr = new int[count+dc];
    arr[0] = 0;
    count = 0;
    for(int i=0; i<str.length(); i++){      /// making num arr to str
        if(str[i] == ','){
            arr[++count] = 0;
        }else{
            arr[count] = (arr[count] * 10) + (int)(str[i] - 48);
        }
    }
    if(str1.length() != 0)
        count++;
    dc = 0;
    for(int i=0; i<str1.length(); i++){      /// making num arr to str1
        if(str1[i] == ','){
            dc++;
            arr[++count] = 0;
        }else{
            arr[count] = (arr[count] * 10) + (int)(str1[i] - 48);
        }
    }
    dc++;
    arrlen = count+1;
    count = 0;
    for(int i=0; i<arrlen; i++){            /// finding highest number
        if(arr[i] > count){
            count = arr[i];
        }
    }
    size = 1;
    while(count >= pow(2, size)){           /// finding max bit size
        size++;     
    }

    // cout << size << endl;
    // cout << arrlen << endl;
    // cout << dc << endl;
    for(int i=0; i<arrlen; i++){
        cout << arr[i];
    }
    mapMaker();
    new QMC_Algorithm(size, arrlen-dc, dc, arr);
}

int* mapGenerator::makeBin(int n)
{
    tempsize = 0;
    int nn = n;
    while(nn != 0){
        nn/=2;
        tempsize++;
    }
    int * a = new int[tempsize];
    for(int i=tempsize-1; i>=0; i--){
        a[i] = n%2;
        n /= 2;
    }
    return a;
}

int mapGenerator::makeGray(int a[])
{
    int ar[tempsize];
    ar[0] = a[0];
    for(int i=1; i<tempsize; i++){
        if(a[i-1] == a[i]){
            ar[i] = 0;
        }else{
            ar[i] = 1;
        }
    }
    int sum = 0;
    for(int i=tempsize-1, j=0; i>=0; i--, j++){
        sum += (ar[i]*pow(2,j));
    }
    return sum;
}

void mapGenerator::mapMaker()
{
    int s1 = pow(2, size/2);
    int s2 = pow(2, size - (size/2));
    row = new int[s1];
    col = new int[s2];
    int ar[s1][s2];
    // for(int i=0; i<arrlen; i++){
    //     cout << arr[i];
    // }
    // cout << "..." << endl;
    // cout << size << endl;
    // cout << s1 << endl;
    // cout << s2 << endl;
    for(int i=0; i<s1; i++){
        for(int j=0; j<s2; j++){
            ar[i][j] = 0;
            col[j] = makeGray(makeBin(j));
        }

        row[i] = makeGray(makeBin(i));
    }

    for(int i=0; i<arrlen; i++){
        for(int j=0; j<s1; j++){
            if(row[j] == arr[i]/s2){
                for(int k=0; k<s2; k++){
                    if(col[k] == arr[i]%s2){
                        if(i < arrlen-dc)
                            ar[j][k] = 1;
                        else
                            ar[j][k] = -1;
                    }
                }
            }
        }
    }
    cout << endl;
    cout << endl << "    Your K-Map...";
    cout << endl;
    cout << endl;
    cout << "\t      ";
    for(int i=0; i<s2; i++){
        cout << col[i] << "   ";
    }
    cout << endl;
    cout << "\t    +-";
    for(int i=0; i<s2; i++){
        if(i != s2-1)
            cout << "--+-";
        else
            cout << "--+";
    }
    cout << endl;

    for(int i=0; i<s1; i++){
        printf("\t%3d | ", row[i]);
        for(int j=0; j<s2; j++){
            if(ar[i][j] != -1)
                cout << ar[i][j] << " | ";
            else
                cout << "x | ";
        }
        cout << endl;
        cout << "\t    +-";
        for(int j=0; j<s2; j++){
            if(j != s2-1)
                cout << "--+-";
            else
                cout << "--+";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

void mapGenerator::print()
{
}
