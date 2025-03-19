#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;

int main() {
    vector<vector<string>> vec (9, vector<string> (9, "0"));
    
    for (vector<string> vec1 : vec) {
        for (string str : vec1) {
            cout << str << ' ';
        }
    }
}