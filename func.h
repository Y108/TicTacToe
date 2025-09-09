#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

inline int roundCounter = 0;

inline char grid[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}},
            positionValues[6] = {'A','B','C','1','2','3'};

inline bool playerWon(const int &player) {
    char playerSymbol = (player == 1) ? 'X' : 'O';
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
    // Val1 : difference between ascii values '0' and 'A'
    // Which converts A,B,C to 0,1,2
    constexpr char Val1 = 0x11;
    constexpr char Val2 = 0x01;
    if (std::isdigit(position[0])) {
        std::ranges::reverse(temp);
    }
    temp[0] = std::toupper(temp[0]);
    temp[0] = temp[0]-Val1;
    temp[1] = temp[1]-Val2;
    return temp;
}

inline bool inputValid(const std::string &input) {
    if (input.size() != 2 ||
        std::isalpha(input[0]) && std::isalpha(input[1]) ||
        std::isdigit(input[0]) && std::isdigit(input[1])) {
        return false;
    }

    bool strChar1_valid = false;
    bool strChar2_valid = false;

    for (const char &c : positionValues) {
        if (std::toupper(input[0])==c) {
            strChar1_valid = true;
        }
        if (std::toupper(input[1])==c) {
            strChar2_valid = true;
        }
    }

    return strChar1_valid && strChar2_valid;
}

inline bool positionOccupied(const std::string &position) {
    const std::string indices = positionToIndex(position);
    const int pos1 = indices[0]-'0';
    const int pos2 = indices[1]-'0';
    if (grid[pos1][pos2] == 'X' || grid[pos1][pos2] == 'O') {
        return true;
    }
    return false;
}

inline void placeMark(const int &player, const std::string &position) {
    const std::string indices = positionToIndex(position);
    const int pos1 = indices[0]-'0';
    const int pos2 = indices[1]-'0';
    if (player==1) {
        grid[pos1][pos2] = 'X';
    }
    else {
        grid[pos1][pos2] = 'O';
    }
}

inline void printGrid() {
    std::cout << '\n';
    std::cout << "         1     2     3" << std::endl;
    std::cout << "            ,     ," << std::endl;
    std::cout << "   A     " << grid[0][0] << "  |  " << grid[0][1] << "  |  " << grid[0][2] << std::endl;
    std::cout << "       -----|-----|-----"<<std::endl;
    std::cout << "   B     " << grid[1][0] << "  |  " << grid[1][1] << "  |  " << grid[1][2] << std::endl;
    std::cout << "       -----|-----|-----"<<std::endl;
    std::cout << "   C     " << grid[2][0] << "  |  " << grid[2][1] << "  |  " << grid[2][2] << std::endl;
    std::cout << "            '     '" << std::endl;
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
