#include "mapGenerator.h"
#include <iostream>
#include <string>

mapGenerator::mapGenerator(string str)
{
    strConverter(str);
}

void mapGenerator::strConverter(string str)
{
    int count = 0;
    for(int i=0; i<str.length(); i++){      /// removing all spaces
        if(str[i] != ' '){
            str[count++] = str[i];
        }
    }
    str = str.substr(0, count);
    arr = new int[count];
    arr[0] = 0;
    count = 0;
    for(int i=0; i<str.length(); i++){      /// making num arr to sring
        if(str[i] == ','){
            arr[++count] = 0;
        }else{
            arr[count] = (arr[count] * 10) + (int)(str[i] - 48);
        }
    }
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

    for(int i=0; i<arrlen; i++){ 
        int* a;
        a = makeBin(a, arr[i], count);
        add(a);
    }

    print();
    solve();
}

int* mapGenerator::makeBin(int a[], int n, int& count)
{
    count = 0;
    a = new int[size];
    for(int i=size-1; i>=0; i--){
        a[i] = n%2;
        if(n%2 == 1){
            count++;
        }
        n /= 2;
    }
    return a;
}

void mapGenerator::add(int a[])
{
    bool canadd = false;
    int count = 0;
    for (int i=0; i<size; i++){
        if(a[i] == 1)
            count++;
    }
    
    if(map.find(count) == map.end()){
        vector<int*> v;
        v.push_back(a);
        map[count] = v;
    }else{
        vector<int*> v = map[count];
        for(int i=0; i<v.size(); i++){      /// cheaking for duplicates
            int* aa = v[i];
            canadd = false;
            for(int j=0; j<size; j++){
                if(a[j] != aa[j]){
                    canadd = true;
                    break;
                }
            }
        }
        if(canadd){
            v.push_back(a);
            map.erase(count);
            map[count] = v;
        }
    }
}

void mapGenerator::solve()
{
    for(int ii=1; ii<=size; ii++){
        if(map.find(ii) != map.end()){
            if(map.find(ii-1) != map.end()){
                vector<int*> v1 = map[ii-1];
                vector<int*> v2 = map[ii];
                vector<int*> v3;
                for(int i=0; i<v2.size(); i++){
                    int* a = v2[i];
                    for(int j=0; j<v1.size(); j++){
                        int* aa = v1[j];
                        bool canmarge = true;
                        int count = 0;
                        for(int k=0; k<size; k++){
                            if(a[k] != aa[k] && a[k] != -1 && aa[k] != -1){
                                count++;
                            }
                            if(count > 1){
                                canmarge = false;
                                break;
                            }
                        }
                        if(canmarge){
                            for(int k=0; k<size; k++){
                                if(a[k] != aa[k] && a[k] != -1 && aa[k] != -1)
                                    aa[k] = -1;
                            }
                            v3.push_back(aa);
                        }
                    }
                    for (int i = 0; i < v3.size(); i++)
                    {
                        int* f = v3[i];
                        int f0 = f[0];
                        int f1 = f[1];
                        int f2 = f[2];
                        int f3 = f[3];
                        add(v3[i]);
                    }
                    v3.clear();
                }
            }
        }
        cout << "--------------------\n" << endl;
        print();
    }
}

void mapGenerator::print()
{
    for(int ii=0; ii<=size; ii++){
        if(map.find(ii) == map.end()){
            continue;
        }else{
            vector<int*> v = map[ii];
            for(int i=0; i<v.size(); i++){
                int* aa = v[i];
                for(int j=0; j<size; j++){
                    cout << aa[j];
                }
                cout << endl;
            }
            cout << endl;
        }
    }
}
