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


vector<Checker> find_user_checkers(vector<Checker>& white_checkers, vector<Checker>& black_checkers, bool is_black) {
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


vector<pair<int, int>> find_free_coordinates(vector<Checker>& white_checkers, vector<Checker>& black_checkers) {
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


/*vector<pair<int, int>> find_possible_coordinates(vector<Checker> white_checkers, vector<Checker> black_checkers, bool is_black) {
    vector<pair<int, int>> free_coordinates = find_free_coordinates(white_checkers, black_checkers);
}*/


vector<vector<Checker>> user_move(vector<Checker> &white_checkers, vector<Checker> &black_checkers, bool is_black) {
    if (is_black) {
        cout << "\n\t ** black's move ** \n"; //!!!!! прописать правила игры !!!!!
    }
    else {
        cout << "\n\t ** white's move ** \n"; //!!!!! прописать правила игры !!!!!
    }
    
    vector<Checker> user_checkers = find_user_checkers(white_checkers, black_checkers, is_black);
    vector<int> possible_numbers(12);
    vector<pair<int, int>> possible_coordinates = find_free_coordinates(white_checkers, black_checkers);

    for (size_t i = 0; i < user_checkers.size(); ++i) { //possible numbers of the 'live' checkers
        possible_numbers[i] = user_checkers[i].get_num();
    }

    for (Checker C : user_checkers) {
        cout << C.get_val() << ' ' << C.get_coordinate().first << ' ' << C.get_coordinate().second << endl;
    }
    for (int n : possible_numbers) {
        cout << n << ' ';
    }
    cout << endl;
    for (pair<int, int> coo : possible_coordinates) {
        cout << coo.first << ' ' << coo.second << endl; 
    }
    cout << endl;


    int selected_num;
    pair<int, int> selected_coordinate;

    cout << "\t Select the checker you're going to use and enter its number: ";
    cin >> selected_num;
    while (count(possible_numbers.begin(), possible_numbers.end(), selected_num) == 0) {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "Choose from the 'live' checkers: ";
        cin >> selected_num;
    }

    cout << "\t Enter the coordinate where you want to move the checker: ";
    int x, y;
    cin >> x >> y;
    selected_coordinate = {x, y};
    while (count(possible_coordinates.begin(), possible_coordinates.end(), selected_coordinate) == 0) {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "Choose from the free cells: ";
        cin >> x >> y;
        selected_coordinate = {x, y};
    }

    vector<vector<Checker>> checkers = {white_checkers, black_checkers};

    int n = 0;
    if (is_black) {
        n = 1;
    }
    for (size_t i = 0; i < checkers[n].size(); ++i) {
        if (checkers[n][i].get_num() == selected_num) {
            checkers[n][i].set_coordinate(selected_coordinate);
        }
    }

    return checkers;

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


string game() {
    vector<Checker> white_checkers = create_coordinates(0); //0 - white checkers
    vector<Checker> black_checkers = create_coordinates(1); //1 - black checkers
    bool is_black_move = 0;
    string winner = "_";  // "_"/"white"/"black"/"draw"

    vector<vector<Checker>> ans;
    do {
        view_board(white_checkers, black_checkers);
        ans = user_move(white_checkers, black_checkers, is_black_move);
        copy(ans[0].begin(), ans[0].end(), white_checkers.begin());
        copy(ans[1].begin(), ans[1].end(), black_checkers.begin());

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
    cout << "Your possible actions:\n\t1 Start a new game\n\t2 It hasn't been thought out yet\n\t3 Exit the game\n\t4 Rules of the game of checkers";
    vector<int> possible_actions = {1, 2, 3, 4};
    do {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\nEnter a number from 1 to 4 : ";
        cin >> action;
    } while (count(possible_actions.begin(), possible_actions.end(), action) == 0);

    if (action == 1) {  //start a new game
        cout << "\n\tLet's play! :)\n";
        string end_of_the_game = game();
    }
    //else if (action == 2) {}
    else if (action == 3){   //exit the game
        cout << "\n\tThank you for your game! :)";
        //return -1;
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