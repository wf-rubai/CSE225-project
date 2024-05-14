#ifndef LOGICCALCULATOR_H
#define LOGICCALCULATOR_H

#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class logicCalculator
{
    public:
        logicCalculator();
        void setEquation(string);
        string getEquation();
        void setHeader(char *, int);
        string spliter(string, int &);
        void makeNoSpace();
        int output(int *);
        int solve(string);

    private:
        string equ;
        int lenght;
        int headersize;
        char * header;
        unordered_map<char, int> map;

};

#endif