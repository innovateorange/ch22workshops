#include<vector>
#include<iostream>
#include<tuple>


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
    std::vector<std::tuple<int, int, int> > numConflicts();
    std::vector<std::tuple<int, int, int,int,int> > getMoves();
    int numConflictsAt(int i, int j);
    void placeQueen(int i, int j);
    void moveQueen(int i, int j, int newI, int newJ);
    int stateValue(int qi, int qj, int i, int j);
    std::vector<std::vector<bool> > queens;
    
    //Hint: Formulate the problem around the notion of occupied cols, rows, or diagonals
    std::vector<int> cols;
    std::vector<int> rows;
    std::vector<int> mainDiags;
    std::vector<int> reverseDiags;



    int n;
};

chessBoard::chessBoard(){
    std::cout << "This function doesn't exist for this problem... EXITING" << std::endl;
    exit(1);
}

chessBoard::chessBoard(int rowsCols): n(rowsCols) {
   /* Init Chess board code */
   /* A chess board is a 2D array of true and false */
   /* True corresponds to a queen's location */

   /*     0     1     2     3
        0 false false false false
        1 true  false false false
        2 false true  false true
        3 false false false true 
        
                                    */
                                   
    /* The diagonals are structured like follows */

    /* main diags by index */

    /*
        6 5 4 3
        5 4 3 2
        4 3 2 1
        3 2 1 0
        
                    */


    /* reverse diags by index */
    /*
        3 2 1 0
        4 3 2 1
        5 4 3 2
        6 5 4 3 
                
                    */

    for(int i = 0; i < rowsCols; i++){
        std::vector<bool> curRow;
        for(int j = 0; j < rowsCols; j++){
            curRow.push_back(false); //Chessboard is initially empty
        }
        queens.push_back(curRow);
        cols.push_back(0);
        rows.push_back(0);
    }
    /* We also initialize vectors which contain the number of queens
        in a given row or column numbered like above */
    for(int i = 0; i < 2*rowsCols-1 ; i++){
        mainDiags.push_back(0);
        reverseDiags.push_back(0);
    }

}
/* Calculate the number of conflicts each queen has */
std::vector<std::tuple<int, int, int> > chessBoard::numConflicts(){
    std::vector<std::tuple<int, int, int> > conflicts;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(queens[i][j]){
                conflicts.push_back(std::make_tuple(i, j, numConflictsAt(i, j)));
            }
        }
    }
    return conflicts;
}
/* Conflict checking algorithm */
int chessBoard::numConflictsAt(int i, int j){
    int totalConflicts = 0;
    totalConflicts += cols[j] - 1 + rows[i] - 1 + mainDiags[(j-i)+(n-1)] - 1 + reverseDiags[(i+j)] - 1;
    return totalConflicts;
}

/* Place a queen and update conflicts */
void chessBoard::placeQueen(int i, int j){
    if(queens[i][j]){
        return;
    } else {
        queens[i][j] = true;
        cols[j]++;
        rows[i]++;
        mainDiags[j-i + (n-1)]++;
        reverseDiags[i+j]++;
    }
}

/*Move a queen and update conflicts */
void chessBoard::moveQueen(int i, int j, int newI, int newJ){

    queens[i][j] = false;
    cols[j]--;
    rows[i]--;
    mainDiags[(j-i)+(n-1)]--;
    reverseDiags[i+j]--;
    
    queens[newI][newJ] = true;
    cols[newJ]++;
    rows[newI]++;
    mainDiags[(newJ - newI)+(n-1)]++;
    reverseDiags[newI+newJ]++;

    return;
    
}
/*Check if the game is solved by getting the num of conflicts for each queen*/
bool chessBoard::isGameSolved(){
    std::vector<std::tuple<int, int, int> > conflicts = numConflicts();
    for(int i = 0; i < conflicts.size(); i++){
        if (std::get<2>(conflicts[i]) > 0){
            return false;
        }
    }
    return true;
}

/*Initialize the game with all queens in same row */
void chessBoard::initializeGame(){
    int count = n;
    
    for(int i = 0; i < n; i++){
        rows[i] = 0;
        cols[i] = 0;
        for(int j = 0; j < n; j++){
            queens[i][j] = false;
        }
    }
    for(int i =0; i < 2*n-1; i++){
        mainDiags[i] = 0;
        reverseDiags[i] = 0;
    }
    while(count){
        int randI = rand() % n;
        int randJ = rand() % n;
        if(!queens[randI][randJ]){
            placeQueen(randI, randJ);
            count--;
        }

    }

}

/*Get the available moves for a queen */
std::vector<std::tuple<int, int, int, int, int> > chessBoard::getMoves(){
    std::vector<std::tuple<int, int, int, int, int> > newMoves;
    for(int qi = 0; qi < n; qi++){
        for(int qj = 0; qj < n; qj++){
            if(queens[qi][qj])
             for(int in =0; in < n; in++){
                for(int jn = 0; jn < n; jn++){
                    if(!queens[in][jn]){
                        newMoves.push_back(std::make_tuple(qi,qj,in,jn, stateValue(qi,qj,in,jn)));
                    }
                }
            }
        }
    }
    
    
    
    return newMoves;  
}

int chessBoard::stateValue(int qi, int qj, int i, int j){
    
    moveQueen(qi, qj, i, j);
    std::vector<int> maxVals = { *std::max_element(cols.begin(), cols.end()), *std::max_element(rows.begin(),rows.end()), *std::max_element(mainDiags.begin(), mainDiags.end()),
                 *std::max_element(reverseDiags.begin(), reverseDiags.end())};
    int curState = *std::max_element(maxVals.begin(), maxVals.end());
    moveQueen(i, j, qi, qj);
    return curState;
}
/* Hill climbing algorithm for solving n-queens*/
void chessBoard::solveGame(){
    //Implement the solution code here!!


    if(n == 2 || n == 3){
        std::cout << "Game has no solution" << std::endl;
        return;
    }

   int oldStateValue = 100;
   std::vector<int> maxVals = { *std::max_element(cols.begin(), cols.end()), *std::max_element(rows.begin(),rows.end()), *std::max_element(mainDiags.begin(), mainDiags.end()),
                            *std::max_element(reverseDiags.begin(), reverseDiags.end())};

   int curState = *std::max_element(maxVals.begin(), maxVals.end());
   
    while(!isGameSolved()){

        std::vector<std::tuple<int, int, int,int, int> > availMoves = getMoves();
        int bestMove = availMoves.size();
        int bestMoveScore = n+1;
        for(int i = 0; i < availMoves.size(); i++){
            if(std::get<4>(availMoves[i]) < bestMoveScore){
                double pNoSwitch = (double) rand()/RAND_MAX;
                if(std::get<4>(availMoves[i]) == bestMoveScore &&  pNoSwitch < 0.1){
                    continue;
                } else{
                    bestMove = i;
                    bestMoveScore = std::get<4>(availMoves[i]);
                }
                
            }
        }
        int oldi = std::get<0>(availMoves[bestMove]);
        int oldj = std::get<1>(availMoves[bestMove]);
        int besti = std::get<2>(availMoves[bestMove]);
        int bestj = std::get<3>(availMoves[bestMove]);

        oldStateValue = curState;
        curState = std::get<4>(availMoves[bestMove]);

        moveQueen(oldi, oldj, besti, bestj);
        
        double pSwitch = (double) rand()/RAND_MAX;
        if((oldStateValue > curState || curState == oldStateValue) && (pSwitch < 0.1) ){
            std::cout << "Rerandomizing game: " << pSwitch <<std::endl;
            initializeGame();
            oldStateValue = 100;
            curState = 100;
        }
        
    }
    std::cout << "Game is solved" << std::endl;
    printDiagnostic();

}

void chessBoard::printDiagnostic(){

    std::cout << "Conflicts in Row i" << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << rows[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Conflicts in Col j" << std::endl;
    for(int j = 0; j < n; j++){
        std::cout << cols[j] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Conflicts in Main diag i" << std::endl;
    for(int i = 0; i < 2*n-1; i++){
        std::cout << mainDiags[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Conflicts in rev diag" << std::endl;
    for(int i = 0; i < 2*n-1; i++){
        std::cout << reverseDiags[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "The state of the board is " << std::endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout << (int) queens[i][j] << ", ";
        }
        std::cout << std::endl;
    }

}