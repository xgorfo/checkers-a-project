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


string multiplying_strings(string str, int cnt) {
    for (int i = 0; i < cnt - 1; ++i) {
        str += str;
    }
    if (cnt == 0) {
        return "";
    }
    return str;
}


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
    /*
    draws a chessboard
    */
    vector<vector<string>> board(9, vector<string> (9,  " _ "));

    board[0][0] = "  "; //the upper left cell of the chessboard

    for (int i = 1; i < 9; ++i) { //fills in the top row and the left column with numbers from 1 to 8
        for (int j = 1; j < 9; ++j) {
            board[0][j] = " " + to_string(j) + " ";
            board[i][0] = to_string(i) + " ";
        }
    }

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
    int item = 1; //the x-axis coordinate of the first black checker
    string w_or_b = "b";
    if (is_black == 0) {
        item = 6; //the x-axis coordinate of the first white checker
        w_or_b = "w";
    }

    for (int i = item, num = 1; i < item + 3; ++i) { //creates black and white checkers by giving them coordinates and a name
        if (i % 2 == 0) {
            for (int j = 1; j < 9; j += 2, ++num) {
                coordinates.push_back(Checker(w_or_b + to_string(num) + multiplying_strings(" ", 2 - to_string(num).length()), i, j));
            }
        }
        else {
            for (int j = 2; j < 9; j += 2, ++num) {
                coordinates.push_back(Checker(w_or_b + to_string(num) + multiplying_strings(" ", 2 - to_string(num).length()), i, j));
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
        cout << "Thank you for your game! :)";
        //return -1;
    }
}


int main() {
    start_menu();
    return 0;
}