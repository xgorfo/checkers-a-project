
  # Сheckers project
## Idea

**The C++ "Checkers" project is a game where two players can take turns making moves. Players move their checkers around the board, can take the opponent's checkers, and also turn their pieces into queens if they reach the last line.**


##  Main Features:
> - An 8x8 game board that is displayed in the console.
> - Game mode support: against another player.
> - Game rules: checkers move only diagonally.
## The composition of the team:

> - Anna Kobitskaya - good person, developer.
> - Sergey Bityutskiy - buller c++, good person, developer, idea generator.
> - Anfisa Vinogradova - good person, <sup> moral </sup> and <sup> material </sup> support, problem solving generator, developer.


## Execution format:
> github (https://github.com/xgorfo/checkers-a-project.git)

## Execution stack:
> libraries from bits/stdc++.h


## Additional statement:
> - Sergey's code is committed by Anna.
> - Sergey is responsible for the verification.
> - Anna is responsible for the main part of the game.
> - Anfisa is responsible for the architecture and code of the style.

## How the game works: 
> Our checkers games support two people playing on one device. You will see a field on which there are w and b. White and black, respectively. Ours has a shape check.
> The game ends when one of the players has no pieces left.
>
 ## About code:
> - The Checker class
> - Checker::Checker(string w_or_b, int num, int i, int j)
> - The constructor of the Checker class initializes a checker with a color (w_or_b), a number (num), and coordinates (i, j).
> - int Checker::get_num()
> - Returns the checker number.
> - string Checker::get_val()
> - Returns the string representation of the checker (color + number).
> - pair<int, int> Checker::get_coordinate()
> - Returns the current coordinates of the checker.
> - void Checker::set_coordinate(pair<int, int> selected_coordinate)
> - Sets the new coordinates of the checker.
> - Auxiliary functions
> - int cnt_pair(vector<pair<int, int>> vec, pair<int, int> val)
> - Counts the number of occurrences of the val pair in the vec vector.
> - int cnt_str(vector<string> vec, string val)
> - Counts the number of occurrences of the string val in the vector vec.
> - int cnt_int(vector<int> vec, int val)
> - Counts the number of occurrences of the number val in the vector vec.
> - string multiplying_strings(string str, int cnt)
> - Multiplies the string str by the number cnt (repeats it cnt times). If cnt == 0, returns an empty string.


## Control report:
### Points for Anna:
> - Amount of code.
> - Team building.
> - UI.
> - UX.

### Points for Sergey:
> - Team building.
> - Amount of code.

### Points for Anfisa:
> - Team building.
> - Architecture.
> - Teamleading.
> - Deadlines.

### Points for team:
> - Architecture.
> - Bugs.
> - Presentation.
> - Code format.
> - Conditional rules of decency.
> - Meeting deadlines.
