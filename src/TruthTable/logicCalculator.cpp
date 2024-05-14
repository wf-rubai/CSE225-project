#include "logicCalculator.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

logicCalculator::logicCalculator()
{
}

void logicCalculator::setEquation(string str)
{
    equ = str;
    makeNoSpace();
}

string logicCalculator::getEquation()
{
    return equ;
}

void logicCalculator::setHeader(char * header, int size)
{
    this->header = header;
    headersize = size;
    for(int i=0; i<size; i++){
        map[tolower(header[i])] = 0;
    }
}

string logicCalculator::spliter(string str, int & i)
{
    stack<char> st;
    int start = i, count = 0;
    for( ; i<lenght; i++){
        if(str[i] == '('){
            st.push('(');
        }
        if(str[i] == ')'){
            st.pop();
            if(st.empty()){
                break;
            }
        }
        count++;
    }

    return str.substr(start+1, count-1);
}

void logicCalculator::makeNoSpace()
{
    int size = 0;
    for(int i=0; equ[i]; i++){
        if(isalpha(equ[i]) && isupper(equ[i])){
            equ[i] = tolower(equ[i]);
        }
        if(equ[i] != ' '){
            equ[size++] = equ[i];
        }
    }
    equ[size] = '\0';
    equ = equ.substr(0, size);
    lenght = size;
}

int logicCalculator::output(int * arr)
{
    for(int i=0; i<headersize; i++){
        map[tolower(header[i])] = arr[i];
    }
    return solve(equ);
}

int logicCalculator::solve(string str)
{
    string temp;
    int bin = 1;
    for(int i=0; i<str.length(); i++){


        if(str[i] == '+' && bin != 0){
            return 1;
        }else if(str[i] == '+' && bin == 0){
            bin = 1;
        }

        if(str[i] == '+' || str[i] == '\''){
            continue;
        }

        if(str[i] == '('){
            temp = spliter(str, i);
            int t = solve(temp);
            if(str[i+1] == '\''){
                t += 1;
                t %= 2;
            }
            bin *= t;
        }else{
            int t = map[str[i]];
            if(str[i+1] == '\''){
                t += 1;
                t %= 2;
            }
            bin *= t;
        }
    }
    if(bin != 0)
        return 1;
    return 0;
}
