#include "mini_checkers.h"
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::string;
using std::endl;

int cnt_str(vector<char> vec, char val) {
    int countt = 0;
    for (char s : vec) {
        countt += (s == val);
    }
    return countt;
}

void check() {
    pair<char, int> start, finish;
    char x;
    int y;
    vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    vector<int> integers = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int countt;

    do {
        cout << "enter the coordinates in this format: <capital letter> <number>" << endl;
        cout << "enter the initial coordinate of the checker: ";
        cin >> x >> y;

        countt = 0;
        for (int s : integers) {
            countt += (s == y);
        }

    } while (cnt_str(letters, x) == 0 || countt == 0);
    start = { x, y };
    cout << endl;

    do {
        cout << "enter the coordinates in this format: <capital letter> <number>" << endl;
        cout << "enter the final coordinate of the checker: ";
        cin >> x >> y;

        countt = 0;
        for (int s : integers) {
            countt += (s == y);
        }

    } while (cnt_str(letters, x) == 0 || countt == 0);
    finish = { x, y };

    int startnum = start.first - 'a' + 1;
    int finishnum = finish.first - 'a' + 1;
    if (start.second != 8) {
        if (finish.second - start.second == 1 && abs(finishnum - startnum) == 1) {
            cout << "YES" << endl;
            if (finish.second == 8) {
                cout << "Congrats! You got a QUEEEEEEEN";
            }
        }else {
            cout << "NO";
        }
    }else {
        if (abs(finish.first - start.first) == abs(finishnum - startnum)) {
            cout << "YES";
        }else {
            cout << "NO";
        }
    }
}