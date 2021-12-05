#ifndef BOARD_H
#define BOARD_H

#include<vector>
#include<iostream>
#include<tuple>
#include<algorithm>

class chessBoard{
public:
    chessBoard();
    chessBoard(int rowsCols);
    void initializeGame();
    void printDiagnostic();
    //Implement this
    void solveGame();
    

private:

    bool isGameSolved();
    
    std::tuple<int, int, int> getMove(int j);
    int numConflictsAt(int i, int j);
    int numConflictsAtNew(int i , int j);
    void placeQueen(int i, int j);
    void moveQueen(int i, int j);
    
    std::vector<std::vector<bool> > queens;
    
    //Hint: Formulate the problem around the notion of occupied cols, rows, or diagonals
    std::vector<int> cols;
    std::vector<int> rows;
    std::vector<int> mainDiags;
    std::vector<int> reverseDiags;



    int n;
};
#endif



