#include <iostream>
#include <string>
#include "func.h"

std::string inputPosition;
std::string answer;

int main() {
    while (true) {
        //Main loop
        while (true){
            printGrid();
            if (playerWon(1)) {
                std::cout<<'\n';
                std::cout<<"Player 1 won the game!"<<std::endl;
                break;
            }
            if (playerWon(2)) {
                std::cout<<'\n';
                std::cout<<"Player 2 won the game!"<<std::endl;
                break;
            }
            if (roundCounter % 2 == 0) {
                std::cout<<'\n'<<"Player 1's turn :"<<std::endl;
            }
            else {
                std::cout<<'\n'<<"Player 2's turn :"<<std::endl;
            }
            while (true) {
                std::cin>>inputPosition;
                if (inputValid(inputPosition) && !positionOccupied(inputPosition)) {
                    if (roundCounter % 2 == 0) {
                        placeMark(1, inputPosition);
                        playerWon(1);
                    }
                    else {
                        placeMark(2, inputPosition);
                        playerWon(2);
                    }
                    break;
                }
                std::cout<<"Invalid input or position already occupied! Please try again:"<<std::endl;
            }
            if (roundCounter == 9) {
                std::cout<<"Tie!"<<std::endl;
            }
            system("CLS");
            ++roundCounter;
        }
        std::cout<<'\n';
        std::cout<<"Would you like to play another game? ( Y / N )"<<std::endl;
        while (true) {
            std::cin >> answer;
            if (answer == "Y" || answer == "y" || answer == "N" || answer == "n") {
                if (answer == "Y" || answer == "y") {
                    resetGame();
                    system("CLS");
                    break;
                }
                return 0;
            }
            std::cout<<"Invalid input!"<<std::endl;
        }
    }
}
