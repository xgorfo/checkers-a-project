#ifndef CHECKERS_H
#define CHECKERS_H

#include <vector>
#include <utility> //This is a header file containing utilities in unrelated domains.
#include <string>

class Checker {
private:
    std::string w_or_b;
    int num;
    std::pair<int, int> coordinate;

    std::vector<std::vector<Checker>> user_move(
        std::vector<Checker>& player_pieces,
        std::vector<Checker>& opponent_pieces,
        bool is_white_turn);


public:
    Checker(std::string w_or_b, int num, int i, int j);
    int get_num();
    std::string get_val();
    std::pair<int, int> get_coordinate();
    void set_coordinate(std::pair<int, int> selected_coordinate);
};


// Helper functions
int cnt_pair(std::vector<std::pair<int, int>> vec, std::pair<int, int> val);
int cnt_str(std::vector<std::string> vec, std::string val);
int cnt_int(std::vector<int> vec, int val);
std::string multiplying_strings(std::string str, int cnt);

// Board functions
std::vector<std::vector<std::string>> create_board(std::vector<Checker>& white_checkers, std::vector<Checker>& black_checkers);
void view_board(std::vector<Checker> white_checkers, std::vector<Checker> black_checkers);

// Game logic
std::vector<Checker> create_coordinates(bool is_black);
std::vector<Checker> find_user_checkers(std::vector<Checker> white_checkers, std::vector<Checker> black_checkers, bool is_black);
std::vector<std::pair<int, int>> find_free_coordinates(std::vector<Checker> white_checkers, std::vector<Checker> black_checkers);
std::vector<std::string> find_w_or_b_values(std::vector<Checker> w_or_b_checkers);
std::vector<std::pair<int, int>> find_possible_coordinates(std::vector<Checker> white_checkers, std::vector<Checker> black_checkers,
    bool is_black, std::pair<int, int> coordinate);
bool check_possible_coordinates(std::vector<Checker> white_checkers, std::vector<Checker> black_checkers,
    bool is_black, std::pair<int, int> coordinate_of_the_selected_num);
std::vector<std::vector<Checker>> removing_eaten_checker(std::vector<std::vector<Checker>>& checkers, bool is_black,
    std::vector<std::pair<int, int>> possible_coordinates,
    std::pair<int, int> selected_coordinate,
    std::pair<int, int> coordinate_of_the_selected_num);
std::vector<std::vector<Checker>> user_move(std::vector<Checker>& white_checkers, std::vector<Checker>& black_checkers, bool is_black);
std::string game();
void start_menu();

#endif // CHECKERS_H