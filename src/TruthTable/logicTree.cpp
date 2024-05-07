#include "logicTree.h"
#include<iostream>
#include<string>

using namespace std;

logicTree::logicTree(string str)
{
    head->par = NULL;
    head->lchild = NULL;
    head->rchild = NULL;
    head->name = str[0];

    currentparent = head;

}

void logicTree::setTree(char c)
{
    if(currentparent->lchild == NULL){
        child *temp = new child;
        temp->name = c;
        temp->lchild = NULL;
        temp->rchild = NULL;
        temp->par = currentparent;
        currentparent->lchild = temp;
    }else if(currentparent->rchild == NULL){
        child *temp = new child;
        temp->name = c;
        temp->lchild = NULL;
        temp->rchild = NULL;
        temp->par = currentparent;
        currentparent->rchild = temp;
    }else{
        currentparent = currentparent->lchild;
        setTree(c);
    }

    chechPrior();
    delete temp;
}

void logicTree::chechPrior()
{
    if(prior(currentparent->name, currentparent->par->name)){
        char c = currentparent->name;
        currentparent->name = currentparent->par->name;
        currentparent->par->name = c;
        currentparent = currentparent->par;
        chechPrior();
    }
    currentparent = head;
}

bool logicTree::prior(char a, char b)
{
    int priorA, priorB;
    if(a == '+')
        priorA = 1;
    else if(a == '.')
        priorA = 2;
    else if(a == '\'')
        priorA = 3;
    else
        priorA = 4;

    if(b == '+')
        priorB = 1;
    else if(b == '.')
        priorB = 2;
    else if(b == '\'')
        priorB = 3;
    else
        priorB = 4;

    return priorB > priorA;
}

logicTree::~logicTree()
{

}