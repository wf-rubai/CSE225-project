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
        mapGenerator(string, string);
        void strConverter(string, string);
        int* makeBin(int);
        int makeGray(int[]);
        void mapMaker();
        void print();

    private:
        int arrlen;
        int dc;
        int size;
        int tempsize;
        int * arr;
        int * row;
        int * col;

};

#endif