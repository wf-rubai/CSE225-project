#ifndef LOGICTREE_H
#define LOGICTREE_H

#pragma once
#include<iostream>
#include<string>

using namespace std;

class logicTree
{
    struct child
    {
        char name;
        child *par;
        child *lchild;
        child *rchild;
    };

    public:
        logicTree(string);
        void setTree(char);
        void chechPrior();
        bool prior(char, char);
        ~logicTree();

    private:
        child *head;
        child *currentparent;

};

#endif