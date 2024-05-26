#ifndef TABLEGENERATOR_H
#define TABLEGENERATOR_H

#pragma once
#include "logicCalculator.h"

#include <iostream>
#include <string>
using namespace std;

class tableGenerator
{
    public:
        tableGenerator(string *, int);
        void generator();
        void loop(int, int);
        string getstr();
        void checkSize();

    private:
        string * logicArr;
        string min;
        char *tabHeader;
        int *binarr;
        int size;
        int strcount;
        int counter;
        logicCalculator * calc;

};

#endif