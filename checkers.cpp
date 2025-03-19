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



class Checker {
    string val;
    pair<int, int> coordinate;

public:
    Checker(string val, int i, int j) : val(val), coordinate({i, j})  {};
    string get_val() {
        return val;
    }
    pair<int, int> get_coordinate() {
        return coordinate;
    }
};


vector<vector<string>> view_board(vector<Checker> white_checkers, vector<Checker> black_checkers) {
    vector<vector<string>> board(9, vector<string> (9, "0"));

    for (Checker C : white_checkers) {
        board[C.get_coordinate().first][C.get_coordinate().second] = C.get_val();
    }
    for (Checker C : black_checkers) {
        board[C.get_coordinate().first][C.get_coordinate().second] = C.get_val();
    }

    return board;
}


vector<Checker> initial_coordinates(bool is_black) {
    /*
    fills in the initial coordinates of the checkers
    */
    vector<Checker> coordinates;
    if (is_black) {
        for (int i = 1, num = 1; i < 4; ++i) {
            if (i % 2 == 0) {
                for (int j = 1; j < 9; j += 2, ++num) {
                    coordinates.push_back(Checker("b" + to_string(num), i, j));
                }
            }
            else {
                for (int j = 2; j < 9; j += 2, ++num) {
                    coordinates.push_back(Checker("b" + to_string(num), i, j));
                }
            }
        }
    }

    else {
        for (int i = 6, num = 1; i < 9; ++i) {
                if (i % 2 == 0) {
                    for (int j = 1; j < 9; j += 2, ++num) {
                        coordinates.push_back(Checker("w" + to_string(num), i, j));
                    }
                }
                else {
                    for (int j = 2; j < 9; j += 2, ++num) {
                        coordinates.push_back(Checker("w" + to_string(num), i, j));
                    }
                }
        }
    }
    return coordinates;
}


void game() {
    vector<Checker> white_checkers = initial_coordinates(0);
    vector<Checker> black_checkers = initial_coordinates(1);
    for (vector<string> vec : view_board(white_checkers, black_checkers)) {
        for (string value : vec) {
            cout << value << ' ';
        }
        cout << endl;
    }
}


void start_menu() {
    /*
    displays the start menu
    */
    int action;  //user's choice
    cout << "Your possible actions:\n\t1 Start a new game\n\t2 It hasn't been thought out yet\n\t3 Exit the game\n";
    vector<int> possible_actions = {1, 2, 3};
    do {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "Enter a number from 1 to 3 : ";
        cin >> action;
    } while (count(possible_actions.begin(), possible_actions.end(), action) == 0);

    if (action == 1) {  //start a new game
        cout << "Let's play! :)\n";
        game();
    }
    //else if (action == 2) {}
    else if (action == 3){   //exit the game
        cout << "Thank you for your game! (*´﹀`*)";
        //return -1;
    }
}


int main() {
    start_menu();
    return 0;
}