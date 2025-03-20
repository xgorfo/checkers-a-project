#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::string;
using std::count;
using std::endl;
using std::__cxx11::to_string;

int main() {
    /*vector<vector<string>> vec (9, vector<string> (9, "0"));
    
    for (vector<string> vec1 : vec) {
        for (string str : vec1) {
            cout << str << ' ';
        }
    }*/
    int num = 10;
    cout << 2 - to_string(num).length();
}