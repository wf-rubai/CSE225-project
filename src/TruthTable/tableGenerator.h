#ifndef TABLEGENERATOR_H
#define TABLEGENERATOR_H

#pragma once

#include<iostream>
#include<string>
using namespace std;

class tableGenerator
{
    public:
        tableGenerator(string);
        void generator();
        void loop(int, int);
        void checkSize();

    private:
        string logic;
        char *tabHeader;
        int *binarr;
        int size;

};

#endif