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
        void checkSize();

    private:
        string * logicArr;
        char *tabHeader;
        int *binarr;
        int size;
        int strcount;
        int counter;
        logicCalculator * calc;

};

#endif