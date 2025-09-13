#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <windows.h>

inline COORD origin(0,0);
inline COORD postClearPosition(0, 9);

inline int roundCounter = 0;

inline char grid[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}},
            positionValues[6] = {'A','B','C','1','2','3'};

inline std::string inputPosition;

inline bool playerWon(const int &player) {
    const char playerSymbol = (player == 1) ? 'X' : 'O';
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] == playerSymbol && grid[i][1] == playerSymbol && grid[i][2] == playerSymbol) return true;
        if (grid[0][i] == playerSymbol && grid[1][i] == playerSymbol && grid[2][i] == playerSymbol) return true;
    }
    if ((grid[0][0] == playerSymbol && grid[1][1] == playerSymbol && grid[2][2] == playerSymbol) ||
        (grid[0][2] == playerSymbol && grid[1][1] == playerSymbol && grid[2][0] == playerSymbol)) return true;

    return false;
}

inline std::string positionToIndex(const std::string &position) {
    std::string temp = position;
    /* 0x11 : difference between ascii values '0' and 'A'
       Which converts A,B,C to 0,1,2 */
    if (std::isdigit(position[0])) {
        std::swap(temp[0],temp[1]);
    }
    temp[0] = std::toupper(temp[0])-0x11;
    temp[1] = temp[1]-0x01;
    return temp;
}

inline bool inputValid(const std::string &input) {
    if (input.size() != 2 ||
        !(std::isalnum(input[0]) && std::isalnum(input[1])) ||
        std::isalpha(input[0]) && std::isalpha(input[1]) ||
        std::isdigit(input[0]) && std::isdigit(input[1])) {
        return false;
    }
    return std::ranges::find(positionValues, input[0]) != std::end(positionValues) &&
           std::ranges::find(positionValues, input[1]) != std::end(positionValues);
}


inline bool positionOccupied(const std::string &position) {
    if (grid[positionToIndex(position)[0]-'0'][positionToIndex(position)[1]-'0'] == 'X' ||
        grid[positionToIndex(position)[0]-'0'][positionToIndex(position)[1]-'0'] == 'O') {
        return true;
    }
    return false;
}

inline void placeMark(const int &player, const std::string &position) {
    if (player==1) {
        grid[positionToIndex(position)[0]-'0'][positionToIndex(position)[1]-'0'] = 'X';
    }
    else {
        grid[positionToIndex(position)[0]-'0'][positionToIndex(position)[1]-'0'] = 'O';
    }
}

inline void printGrid() {
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE) ,origin); // move cursor to top left of screen to overwrite previous grid.
    std::cout << '\n';
    std::cout << "         1     2     3" << std::endl;
    std::cout << "            ,     ," << std::endl;
    std::cout << "   A     " << grid[0][0] << "  |  " << grid[0][1] << "  |  " << grid[0][2] << std::endl;
    std::cout << "       -----|-----|-----"<<std::endl;
    std::cout << "   B     " << grid[1][0] << "  |  " << grid[1][1] << "  |  " << grid[1][2] << std::endl;
    std::cout << "       -----|-----|-----"<<std::endl;
    std::cout << "   C     " << grid[2][0] << "  |  " << grid[2][1] << "  |  " << grid[2][2] << std::endl;
    std::cout << "            '     '" << std::endl;
    for (int i = 0; i<20; ++i){ // clear "Wrong input" lines (up to a certain point)
        std::cout<<"                                                                                "<<'\n';
    }
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE) ,postClearPosition); // move cursor to where it would have been prior to the empty lines.
}

inline bool continueYoN() {
    std::string answer;
    std::cout<<"\nWould you like to play another round? ( Y / N )"<<std::endl;
    while (true) {
        std::cin >> answer;
        if (answer == "Y" || answer == "y") {
            return true;
        }
        if (answer == "N" || answer == "n") {
            return false;
        }
        std::cout<<"Invalid input!"<<std::endl;
    }
}

inline bool checkTie() {
    return !(std::ranges::find(grid[0], ' ') != std::end(grid[0]) ||
             std::ranges::find(grid[1], ' ') != std::end(grid[1]) ||
             std::ranges::find(grid[2], ' ') != std::end(grid[2])) ;
}

inline void resetGame() {
    for (auto & i : grid) {
        for (char & j : i) {
            j = ' ';
        }
    }
    roundCounter = 0;
}

#endif
