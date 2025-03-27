#include "checkers.h"
#include "mini_checkers.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::string;
using std::to_string;
using std::endl;

// Checker class implementation
Checker::Checker(string w_or_b, int num, int i, int j) :
    w_or_b(w_or_b), num(num), coordinate({ i, j }) {
}

int Checker::get_num() { return num; }
string Checker::get_val() { return w_or_b + to_string(num); }
pair<int, int> Checker::get_coordinate() { return coordinate; }
void Checker::set_coordinate(pair<int, int> selected_coordinate) { coordinate = selected_coordinate; }

// Helper functions
int cnt_pair(vector<pair<int, int>> vec, pair<int, int> val) {
    int countt = 0;
    for (pair<int, int> s : vec) {
        countt += (s == val);
    }
    return countt;
}

int cnt_str(vector<string> vec, string val) {
    int countt = 0;
    for (string s : vec) {
        countt += (s == val);
    }
    return countt;
}

int cnt_int(vector<int> vec, int val) {
    int countt = 0;
    for (int s : vec) {
        countt += (s == val);
    }
    return countt;
}

string multiplying_strings(string str, int cnt) {
    for (int i = 0; i < cnt - 1; ++i) {
        str += str;
    }
    if (cnt == 0) {
        return "";
    }
    return str;
}

// Board functions
vector<vector<string>> create_board(vector<Checker>& white_checkers, vector<Checker>& black_checkers) {
    vector<vector<string>> board(9, vector<string>(9, " _ "));
    board[0][0] = "  ";

    for (int i = 1; i < 9; ++i) {
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
    for (vector<string> vec : create_board(white_checkers, black_checkers)) {
        for (string value : vec) {
            cout << value << ' ';
        }
        cout << endl;
    }
}

// Game logic
vector<Checker> create_coordinates(bool is_black) {
    vector<Checker> coordinates;
    int item = is_black ? 1 : 6;
    string w_or_b = is_black ? "b" : "w";

    for (int i = item, num = 1; i < item + 3; ++i) {
        if (i % 2 == 0) {
            for (int j = 1; j < 9; j += 2, ++num) {
                coordinates.push_back(Checker(multiplying_strings(" ", 2 - (to_string(num)).length()) + w_or_b, num, i, j));
            }
        }
        else {
            for (int j = 2; j < 9; j += 2, ++num) {
                coordinates.push_back(Checker(multiplying_strings(" ", 2 - (to_string(num)).length()) + w_or_b, num, i, j));
            }
        }
    }
    return coordinates;
}

vector<Checker> find_user_checkers(vector<Checker> white_checkers, vector<Checker> black_checkers, bool is_black) {
    return is_black ? black_checkers : white_checkers;
}

vector<pair<int, int>> find_free_coordinates(vector<Checker> white_checkers, vector<Checker> black_checkers) {
    vector<pair<int, int>> free_coordinates;
    vector<vector<string>> board = create_board(white_checkers, black_checkers);

    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            if (board[i][j] == " _ ") {
                free_coordinates.push_back({ i, j });
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

vector<pair<int, int>> find_possible_coordinates(vector<Checker> white_checkers, vector<Checker> black_checkers,
    bool is_black, pair<int, int> coordinate) {

        //finds all possible coordinates that a checker can resemble, the coordinates of which are passed by the argument of this function

    vector<pair<int, int>> free_coordinates = find_free_coordinates(white_checkers, black_checkers);
    vector<pair<int, int>> possible_coordinates_1(4); //coordinates at a distance of 1 diagonally from the transmitted coordinate
    vector<pair<int, int>> possible_coordinates_2(4); //coordinates at a distance of 2 diagonally from the transmitted coordinate
    vector<pair<int, int>> possible_coordinates(8);
    vector<vector<string>> board = create_board(white_checkers, black_checkers);
    vector<vector<Checker>> checkers = { white_checkers, black_checkers };
    vector<string> w_or_b_values = find_w_or_b_values(checkers[!is_black]); //finds the values of the opponent's checkers

    for (size_t i = 0, j = 0; i < free_coordinates.size(); ++i) {
        if (abs(free_coordinates[i].second - coordinate.second) == 1) { //the difference of the x-coordinates
            if ((is_black && (free_coordinates[i].first - coordinate.first) == 1) || (!is_black && (free_coordinates[i].first - coordinate.first) == -1)) { //the difference of the y-coordinates
                //the condition that the checker can only move towards the opponent (it cannot move backwards)
                possible_coordinates_1[j] = free_coordinates[i];
                ++j;
            }
        }
    }
    for (size_t i = 0, j = 0; i < free_coordinates.size(); ++i) {
        if (free_coordinates[i].first == coordinate.first + 2 && free_coordinates[i].second == coordinate.second + 2) {
            //the condition is that the coordinate of the free cell is 2 diagonally away (2 to the right and 2 down)
            if (cnt_str(w_or_b_values, board[coordinate.first + 1][coordinate.second + 1])) {
                //checks whether the value of the coordinate of the chessboard located at a distance of 1 diagonally (right 1 and down 1) is one of the values of the opponent's chess
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }else if (free_coordinates[i].first == coordinate.first - 2 && free_coordinates[i].second == coordinate.second - 2) {
            //the condition is that the coordinate of the free cell is 2 diagonally away (2 to the left and 2 up)
            if (cnt_str(w_or_b_values, board[coordinate.first - 1][coordinate.second - 1])) {
                //checks whether the value of the coordinate of the chessboard located at a distance of 1 diagonally (left 1 and up 1) is one of the values of the opponent's chess
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }else if (free_coordinates[i].first == coordinate.first - 2 && free_coordinates[i].second == coordinate.second + 2) {
            //the condition is that the coordinate of the free cell is 2 diagonally away (2 to the right and 2 up)
            if (cnt_str(w_or_b_values, board[coordinate.first - 1][coordinate.second + 1])) {
                //checks whether the value of the coordinate of the chessboard located at a distance of 1 diagonally (right 1 and up 1) is one of the values of the opponent's chess
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }else if (free_coordinates[i].first == coordinate.first + 2 && free_coordinates[i].second == coordinate.second - 2) {
            //the condition is that the coordinate of the free cell is 2 diagonally away (2 to the left and 2 down)
            if (cnt_str(w_or_b_values, board[coordinate.first + 1][coordinate.second - 1])) {
                //checks whether the value of the coordinate of the chessboard located at a distance of 1 diagonally (left 1 and down 1) is one of the values of the opponent's chess
                possible_coordinates_2[j] = free_coordinates[i];
                ++j;
            }
        }
    }

    for (size_t i = 0; i < possible_coordinates_1.size(); ++i) { //fills it with possible coordinates located at a distance of 1 from the initial point
        possible_coordinates[i] = possible_coordinates_1[i];
    }
    for (size_t i = 0; i < possible_coordinates_2.size(); ++i) { //fills it with possible coordinates located at a distance of 2 from the initial point
        possible_coordinates[i + 4] = possible_coordinates_2[i];
    }

    return possible_coordinates;
}

int check_possible_num(vector<int> possible_numbers, int& selected_num) {
    /*
    checks that a "live" checker is selected and returns the finally selected checkers number.
    */
    while (cnt_int(possible_numbers, selected_num) == 0) {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\t Enter the number of the available checkers: ";
        cin >> selected_num;
    }

    return selected_num;
}





bool check_possible_coordinates(vector<Checker> white_checkers, vector<Checker> black_checkers,
    bool is_black, pair<int, int> coordinate_of_the_selected_num) {

    //checking for possible coordinates of the checker

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

vector<vector<Checker>> removing_eaten_checker(vector<vector<Checker>>& checkers, bool is_black,
    vector<pair<int, int>> possible_coordinates,
    pair<int, int> selected_coordinate,
    pair<int, int> coordinate_of_the_selected_num) {

       //removes dead checkers from the vectors

    int x_eaten_checker; //the x-coordinate of the dead checker
    int y_eaten_checker; //the y-coordinate of the dead checker
    for (size_t i = 0; i < possible_coordinates.size(); ++i) {
        if (possible_coordinates[i] == selected_coordinate && i >= 4) {
            int x_coordinate_difference = selected_coordinate.first - coordinate_of_the_selected_num.first; //the difference between the empty and transmitted x-coordinate
            int y_coordinate_difference = selected_coordinate.second - coordinate_of_the_selected_num.second; //the difference between the empty and transmitted y-coordinate

            if (x_coordinate_difference > 0) { //the coordinate from the bottom of the transmitted one
                x_eaten_checker = coordinate_of_the_selected_num.first + 1;
            }
            else { //the coordinate on top of the transmitted one
                x_eaten_checker = coordinate_of_the_selected_num.first - 1;
            }

            if (y_coordinate_difference > 0) { //the coordinate to the right of the transmitted one
                y_eaten_checker = coordinate_of_the_selected_num.second + 1;
            }
            else { //the coordinate to the left of the transmitted one
                y_eaten_checker = coordinate_of_the_selected_num.second - 1;
            }

            pair<int, int> coordinate_eaten_checker = { x_eaten_checker, y_eaten_checker };
            if (checkers[!is_black].size() == 1) { //if the last piece remains in the array, then we return an empty one
                checkers[!is_black] = {};
            }
            else {
                for (size_t i = 0; i < checkers[!is_black].size(); ++i) {
                    if (checkers[!is_black][i].get_coordinate() == coordinate_eaten_checker) { //looking for a checker with the coordinate of a dead checker
                        checkers[!is_black].erase(checkers[!is_black].begin() + i); //removes the dead checker from the vectors
                    }
                }
            }
        }
    }
    return checkers;
}

vector<vector<Checker>> user_move(vector<Checker>& white_checkers, vector<Checker>& black_checkers, bool is_black) {
    /*
    player's turn
    */
    vector<vector<Checker>> checkers = { white_checkers, black_checkers };
    int selected_num;
    pair<int, int> selected_coordinate;
    pair<int, int> coordinate_of_the_selected_num;
    vector<Checker> user_checkers = find_user_checkers(checkers[0], checkers[1], is_black); //the vector of checkers that the current user is playing for (white or black)
    vector<int> possible_numbers(12);  //possible numbers of the checkers

    if (is_black) {
        cout << "\n\t ** black's move ** \n";
    }
    else {
        cout << "\n\t ** white's move ** \n";
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
    selected_coordinate = { x, y };

    while (cnt_pair(possible_coordinates, selected_coordinate) == 0) {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\t Choose from the possible cells: ";
        cin >> x >> y;
        selected_coordinate = { x, y };
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
        cin.ignore();
    }
    return checkers;
}


string game() {


    vector<Checker> white_checkers = create_coordinates(false);
    vector<Checker> black_checkers = create_coordinates(true);
    bool is_black_move = false;
    string winner = "_";

    vector<vector<Checker>> ans;
    do {
        view_board(white_checkers, black_checkers);
        ans = user_move(white_checkers, black_checkers, is_black_move);
        white_checkers = ans[0];
        black_checkers = ans[1];
        is_black_move = !is_black_move;

        if (white_checkers.empty()) {
            winner = "black";
        }
        else if (black_checkers.empty()) {
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
    cout << "Your possible actions:\n\t1 Start a game of a chess\n\t2 Start a game of a mini chess\n\t3 Exit the game";
    vector<int> possible_actions = { 1, 2, 3 };
    do {  //asks you to enter a number until the user enters one of the possible numbers
        cout << "\nEnter a number from 1 to 3 : ";
        cin >> action;
    } while (cnt_int(possible_actions, action) == 0);

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
    else if (action == 3) {   //exit the game
        cout << "\n\tThank you for your game! :)";
    }
}