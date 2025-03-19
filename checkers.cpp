#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::vector;
using std::count;


//void game() {}


void start_menu() {
    int action;
    cout << "Your possible actions:\n\t1 Start a new game\n\t2 It hasn't been thought out yet\n\t3 Exit the game\n";
    vector<int> possible_actions = {1, 2, 3};
    do {
        cout << "Enter a number from 1 to 3 : ";
        cin >> action;
    } while (count(possible_actions.begin(), possible_actions.end(), action) == 0);

    if (action == 1) {
        cout << "Let's play!\n";
        //game();
    }
    //else if (action == 2) {}
    else if (action == 3){
        cout << "Thank you for your game! (*´﹀`*)";
        //return -1;
    }
}


int main() {
    start_menu();
    return 0;
}