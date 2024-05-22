#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){
    vector<int> ii;
    for(int i = 0; i<5; i++){
        ii.push_back(i);
    }
    ii.erase(ii.begin()+2);
    // ii.erase(2);
    for(int i = 0; i<ii.size(); i++){
        cout << ii[i];
    }
    // unordered_map<int, int> m;
    // m[0]=1;
    // m[1]=2;
    // cout << m[1] << endl;
    // cout << m[1] << endl;
    // m.erase(1);
    // if(m.find(1) == m.end()){
    //     cout << "erased";
    // }else{

    // cout << m[1] << endl;
    // }
}