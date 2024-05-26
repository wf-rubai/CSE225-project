#ifndef QMC_ALGORITHM_H
#define QMC_ALGORITHM_H

#include <cstdio>
#include <cstring>
#include <algorithm>

#pragma once

using namespace std;

#define MAX_VAR_N (26)
#define MAX_ITM_N (25600)

#define TERM_NUM(P, G) (*(int *)((P) + group_len * (G)))
#define TERM_PTR(P, G, T) (char *)((P) + group_len * (G) + sizeof(int) + term_len * (T))
#define TERM_DATA(P, G, T, K) (*(char *)((P) + group_len * (G) + sizeof(int) + term_len * (T) + sizeof(int) + sizeof(char) * (K)))
#define TERM_PDATA(P, G, T) (char *)((P) + group_len * (G) + sizeof(int) + term_len * (T) + sizeof(int))
#define SUB_NUM(P, G, T) (*(int *)((P) + group_len * (G) + sizeof(int) + term_len * (T)))
#define SUB_DATA(P, G, T, K) (*(int *)((P) + group_len * (G) + sizeof(int) + term_len * (T) + sizeof(int) + sizeof(char) * (n + 1) + sizeof(int) * (K)))
#define SUB_PDATA(P, G, T) (int *)((P) + group_len * (G) + sizeof(int) + term_len * (T) + sizeof(int) + sizeof(char) * (n + 1))

class QMC_Algorithm
{
public:
    QMC_Algorithm(int, int, int, int[]);
    void load_data();
    void copy_terms();
    int combine_terms();
    int find_prime();
    void print_terms();
    void show_output();
    void solve();

private:
    int term_len;
    int group_len;
    int *input;
    char *temp;
    char *output;
    int n, m, d;
};

#endif