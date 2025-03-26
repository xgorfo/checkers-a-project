#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <string>
#include "mini_checkers.cpp"

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
    string w_or_b; //white or black
    int num;
    pair<int, int> coordinate;

public:
    Checker(string w_or_b, int num, int i, int j) : w_or_b(w_or_b), num(num), coordinate({i, j})  {};
    int get_num() {
        return num;
    }
    string get_val() {
        return w_or_b + to_string(num);
    }
    pair<int, int> get_coordinate() {
        return coordinate;
    }
    void set_coordinate(pair<int, int>& selected_coordinate) {
        coordinate = selected_coordinate;
    }
};


vector<vector<string>> create_board(vector<Checker>& white_checkers, vector<Checker>& black_checkers) {
    /*
    creates a chessboard
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


void view_board(vector<Checker> white_checkers, vector<Checker> black_checkers) {
    /*
    draws a chessboard
    */
    for (vector<string> vec : create_board(white_checkers, black_checkers)) { 
        for (string value : vec) {
            cout << value << ' ';
        }
        cout << endl;
    }
}


vector<Checker> create_coordinates(bool is_black) {
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
                coordinates.push_back(Checker(multiplying_strings(" ", 2 - to_string(num).length()) + w_or_b, num, i, j));
            }
        }
        else {
            for (int j = 2; j < 9; j += 2, ++num) {
                coordinates.push_back(Checker(multiplying_strings(" ", 2 - to_string(num).length()) + w_or_b, num, i, j));
            }
        }
    }
    return coordinates;
}


vector<Checker> find_user_checkers(vector<Checker> white_checkers, vector<Checker> black_checkers, bool is_black) {
    vector<Checker> user_checkers;
    if (is_black) {
        for (size_t i = 0; i < black_checkers.size(); ++i) {
            user_checkers.push_back(black_checkers[i]);
        }
    }
    else {
        for (size_t i = 0; i < white_checkers.size(); ++i) {
            user_checkers.push_back(white_checkers[i]);
        }
    }
    return user_checkers;
}


vector<pair<int, int>> find_free_coordinates(vector<Checker> white_checkers, vector<Checker> black_checkers) {
    vector<pair<int, int>> free_coordinates;
    vector<vector<string>> board = create_board(white_checkers, black_checkers);

    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            if (board[i][j] == " _ ") {
                free_coordinates.push_back({i, j});
            }
        }
    }

    return free_coordinates;
}


vector<string> find_w_or_b_values(vector<Checker> w_or_b_checkers) {
    vector<string> w_or_b_values;
    for (Checker C : w_or_b_checkers) {
        w_or_b_values.push_back(C.get_val());
    }
    return w_or_b_values;
}


vector<pair<int, int>> find_possible_coordinates(vector<Checker> white_checkers, vector<Checker> black_checkers, bool is_black, pair<int, int> coordinate) {
    vector<pair<int, int>> free_coordinates = find_free_coordinates(white_checkers, black_checkers);
    vector<pair<int, int>> possible_coordinates_1(4);
    vector<pair<int, int>> possible_coordinates_2(4);
    vector<pair<int, int>> possible_coordinates(8);
    vector<vector<string>> board = create_board(white_checkers, black_checkers);
    vector<vector<Checker>> checkers = {white_checkers, black_checkers};
    vector<string> w_or_b_values = find_w_or_b_values(checkers[!is_black]);

    for (size_t i = 0, j = 0; i < free_coordinates.size(); ++i) {
        if (abs(free_coordinates[i].first - coordinate.first) == 1 && abs(free_coordinates[i].second - coordinate.second) == 1) {
            possible_coordinates_1[j] = free_coordinates[i];
            ++j;
        }
    }
    for (size_t i = 0, j = 0; i < free_coordinates.size(); ++i) {
        if (free_coordinates[i].first == coordinate.first + 2 && free_coordinates[i].second == coordinate.second + 2) {
            if (count(w_or_b_values.begin(), w_or_b_values.end(), board[coordinate.first + 1][coordinate.second + 1])) {
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }
        else if (free_coordinates[i].first == coordinate.first - 2 && free_coordinates[i].second == coordinate.second - 2) {
            if (count(w_or_b_values.begin(), w_or_b_values.end(), board[coordinate.first - 1][coordinate.second - 1])) {
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }
        else if (free_coordinates[i].first == coordinate.first - 2 && free_coordinates[i].second == coordinate.second + 2) {
            if (count(w_or_b_values.begin(), w_or_b_values.end(), board[coordinate.first - 1][coordinate.second + 1])) {
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }
        else if (free_coordinates[i].first == coordinate.first + 2 && free_coordinates[i].second == coordinate.second - 2) {
            if (count(w_or_b_values.begin(), w_or_b_values.end(), board[coordinate.first + 1][coordinate.second - 1])) {
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }
    }

    copy(possible_coordinates_1.begin(), possible_coordinates_1.end(), possible_coordinates.begin());
    copy(possible_coordinates_2.begin(), possible_coordinates_2.end(), possible_coordinates.begin() + possible_coordinates_1.size());

    return possible_coordinates;
}


int check_possible_num(vector<int> possible_numbers, int &selected_num) {
    /*
    checks that a "live" checker is selected and returns the finally selected checkers number.
    */
    while (count(possible_numbers.begin(), possible_numbers.end(), selected_num) == 0) {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\t Enter the number of the available checkers: ";
        cin >> selected_num;
    }
    return selected_num;
}


bool check_possible_coordinates(vector<Checker> white_checkers, vector<Checker> black_checkers, bool is_black, pair<int, int> coordinate_of_the_selected_num) {
    /*
    checking for possible coordinates of the checker
    */
    vector<pair<int, int>> possible_coordinates = find_possible_coordinates(white_checkers, black_checkers, is_black, coordinate_of_the_selected_num);
    
    bool f = false;
    for (pair<int, int> p : possible_coordinates) {  //checks if there are possible coordinates
        if (p.first != 0) {
            f = true;
            break;
        }
    }

    return f;
}


vector<vector<Checker>> removing_eaten_checker(vector<vector<Checker>>& checkers, bool is_black, vector<pair<int, int>> possible_coordinates, pair<int, int> selected_coordinate, pair<int, int> coordinate_of_the_selected_num) {
    int x_eaten_checker;
    int y_eaten_checker;
    for (size_t i = 0; i < possible_coordinates.size(); ++i) { //removing the eaten checkers
        if (possible_coordinates[i] == selected_coordinate && i >= 4) {
            int x_coordinate_difference = selected_coordinate.first - coordinate_of_the_selected_num.first;
            int y_coordinate_difference = selected_coordinate.second - coordinate_of_the_selected_num.second;

            if (x_coordinate_difference > 0) {
                x_eaten_checker = coordinate_of_the_selected_num.first + 1;
            }
            else {
                x_eaten_checker = coordinate_of_the_selected_num.first - 1;
            }

            if (y_coordinate_difference > 0) {
                y_eaten_checker = coordinate_of_the_selected_num.second + 1;
            }
            else {
                y_eaten_checker = coordinate_of_the_selected_num.second - 1;
            }
            
            pair<int, int> coordinate_eaten_checker = {x_eaten_checker, y_eaten_checker};
            if (checkers[!is_black].size() == 1) {
                checkers[!is_black] = {};
            }
            else {
                for (size_t i = 0; i < checkers[!is_black].size(); ++i) {
                    if (checkers[!is_black][i].get_coordinate() == coordinate_eaten_checker) {
                        checkers[!is_black].erase(checkers[!is_black].begin() + i);
                    }
                }
            }
        }
    }
    return checkers;
}


vector<vector<Checker>> user_move(vector<Checker>& white_checkers, vector<Checker>& black_checkers, bool is_black) {
    vector<vector<Checker>> checkers = {white_checkers, black_checkers};
    int selected_num;
    pair<int, int> selected_coordinate;
    pair<int, int> coordinate_of_the_selected_num;
    vector<Checker> user_checkers = find_user_checkers(checkers[0], checkers[1], is_black);
    vector<int> possible_numbers(12);

    if (is_black) {
        cout << "\n\t ** black's move ** \n"; //!!!!! прописать правила игры !!!!!
    }
    else {
        cout << "\n\t ** white's move ** \n"; //!!!!! прописать правила игры !!!!!
    }
    
    for (size_t i = 0; i < user_checkers.size(); ++i) { //possible numbers of the 'live' checkers
        possible_numbers[i] = user_checkers[i].get_num();
    }

    cout << "\t Select the checker you're going to use and enter its number: ";
    cin >> selected_num;
    selected_num = check_possible_num(possible_numbers, selected_num);
    for (Checker C : user_checkers) {
        if (C.get_num() == selected_num) {
            coordinate_of_the_selected_num = C.get_coordinate();
        }
    }
    
    while (check_possible_coordinates(checkers[0], checkers[1], is_black, coordinate_of_the_selected_num) == 0) {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\t Choose the number of the checker that has possible coordinates: ";
        cin >> selected_num;
        selected_num = check_possible_num(possible_numbers, selected_num);
        for (Checker C : user_checkers) {
            if (C.get_num() == selected_num) {
                coordinate_of_the_selected_num = C.get_coordinate();
            }
        }
    }
    
    vector<pair<int, int>> possible_coordinates = find_possible_coordinates(checkers[0], checkers[1], is_black, coordinate_of_the_selected_num);

    cout << "\t Possible coordinates: ";
    for (pair<int, int> p : possible_coordinates) {
        if (p.first != 0) {
            cout << '{' << p.first << ';' << p.second << '}' << ' ';
        }
    }
    cout << endl;

    cout << "\t Enter the coordinate where you want to move the checker: ";
    int x, y;
    cin >> x >> y;
    selected_coordinate = {x, y};

    while (count(possible_coordinates.begin(), possible_coordinates.end(), selected_coordinate) == 0) {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\t Choose from the possible cells: ";
        cin >> x >> y;
        selected_coordinate = {x, y};
    }

    checkers = removing_eaten_checker(checkers, is_black, possible_coordinates, selected_coordinate, coordinate_of_the_selected_num);
    
    int n = 0;
    if (is_black) {
        n = 1;
    }
    for (size_t i = 0; i < checkers[n].size(); ++i) {  //changes the coordinate of the selected checker to the entered one
        if (checkers[n][i].get_num() == selected_num) {
            checkers[n][i].set_coordinate(selected_coordinate);
        }
    }
    return checkers;
}


string game() {
    vector<Checker> white_checkers = create_coordinates(0); //0 - white checkers
    vector<Checker> black_checkers = create_coordinates(1); //1 - black checkers
    bool is_black_move = 0;
    string winner = "_";  // "_"/"white"/"black"

    vector<vector<Checker>> ans;
    do {
        view_board(white_checkers, black_checkers);
        ans = user_move(white_checkers, black_checkers, is_black_move);
        white_checkers = ans[0];
        black_checkers = ans[1];

        is_black_move = !is_black_move;
        if (white_checkers.size() == 0) {
            winner = "black";
        }
        else if (black_checkers.size() == 0) {
            winner = "white";
        }
    } while (winner == "_");

    return winner;
}


void start_menu() {
    /*
    displays the start menu
    */
    int action;  //user's choice
    cout << "Your possible actions:\n\t1 Start a game of a chess\n\t2 Start a game of a mini chess\n\t3 Exit the game\n\t4 Rules of the game of checkers";
    vector<int> possible_actions = {1, 2, 3, 4};
    do {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\nEnter a number from 1 to 4 : ";
        cin >> action;
    } while (count(possible_actions.begin(), possible_actions.end(), action) == 0);

    if (action == 1) {  //start a game of a chess
        cout << "\n\t Let's play! :)\n";
        string end_of_the_game = game();
        cout << "\t The end of the game!\n";
        cout << "\t The victory goes to the player who played for the " << end_of_the_game << " checkers!";
        cout << "\n\t Thank you for your game! :)";
    }
    else if (action == 2) { //start a game of a mini chess
        check();
    }
    else if (action == 3){   //exit the game
        cout << "\n\tThank you for your game! :)";
    }
    else if (action == 4) { //rules of the game of checkers
        cout << "\n\trules: \n";
        //rules_of_the_game()
    }
}


int main() {
    start_menu();
    return 0;
}