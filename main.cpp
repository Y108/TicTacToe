#include "func.h"

int main() {
    while (true) {
        //Main loop
        while (true){
            printGrid();

            if (playerWon(roundCounter % 2)) {
                std::cout<<'\n';
                std::cout<<"Player "<< (roundCounter % 2 == 1 ?"1" :"2") <<" won the game!"<<std::endl;
                break;
            }
            if (checkTie()) {
                std::cout<<"Tie!"<<std::endl;
                break;
            }
            (roundCounter % 2 == 0)?
            (std::cout<<'\n'<<"Player 1's turn :"<<std::endl):
            (std::cout<<'\n'<<"Player 2's turn :"<<std::endl);

            while (true) {
                std::cin>>inputPosition;

                if (inputValid(inputPosition) && !positionOccupied(inputPosition)) {
                    if (roundCounter % 2 == 0) {
                        placeMark(1, inputPosition);
                        break;
                    }
                    placeMark(2, inputPosition);
                    break;
                }
                std::cout<<"Invalid input or position already occupied! Please try again:"<<std::endl;
            }
            ++roundCounter;
        }
        if (continueYoN()) {
            std::cout<<"Playing another round!"<<std::endl;
            resetGame();
        }
        else {
            break;
        }
    }
}
