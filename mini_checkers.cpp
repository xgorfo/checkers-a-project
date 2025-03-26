#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using std::cout;
using std::cin;
using std::string;
using std::count;
using std::pair;
using std::endl;
using std::vector;


void check() {
    pair<char, int> start, finish;
    char x;
    int y;
    vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    vector<int> integers = {1, 2, 3, 4, 5, 6, 7, 8};
    
    do {
        cout << "enter the coordinates in this format: <capital letter> <number>" << endl;
        cout << "enter the initial coordinate of the checker: ";
        cin >> x >> y;
    } while (count(letters.begin(), letters.end(), x) == 0 || count(integers.begin(), integers.end(), y) == 0);
    start = {x, y};
    cout << endl;

    do {
        cout << "enter the coordinates in this format: <capital letter> <number>" << endl;
        cout << "enter the final coordinate of the checker: ";
        cin >> x >> y;
    } while (count(letters.begin(), letters.end(), x) == 0 || count(integers.begin(), integers.end(), y) == 0);
    finish = {x, y};
    
    int startnum = start.first - 'a' + 1; //char -> int
    int finishnum = finish.first - 'a' + 1; //char -> int
    if (start.second != 8) {
        if (finish.second - start.second == 1 && abs(finishnum - startnum) == 1) {
            cout << "YES" << endl;
            if (finish.second == 8) { 
                cout << "Congrats! You got a QUEEEEEEEN"; 
            }
        }
        else { 
            cout << "NO"; 
        }
    }
    else {
        if (abs(finish.first - start.first) == abs(finishnum - startnum)) {
            cout << "YES";
        }
        else {
            cout << "NO";
        }
    }
}