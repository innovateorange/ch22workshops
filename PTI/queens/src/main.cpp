#include "../headers/board.hpp"
#include<iostream>

int main(int argc, char* argv[]){
    int nQueens = 5;
    if(argc != 1){
        nQueens = atoi(argv[1]);  
    }
 
    chessBoard board(nQueens);
    board.initializeGame();
    board.solveGame();
}