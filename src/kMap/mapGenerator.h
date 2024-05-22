#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class mapGenerator
{
    public:
        mapGenerator(string);
        void strConverter(string);
        int* makeBin(int[], int, int&);
        void add(int[]);
        void solve();
        void print();

    private:
        int arrlen;
        int size;
        int * arr;
        unordered_map<int, vector<int*> > map;

};

#endif