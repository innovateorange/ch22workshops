#include "../headers/board.hpp"




/* Hill climbing algorithm for solving n-queens*/
void chessBoard::solveGame(){
    //Implement the solution code here!!


    if(n == 2 || n == 3){
        std::cout << "Game has no solution" << std::endl;
        return;
    }
    int cnt = 0;
    while(!isGameSolved()){
        cnt++;
        int worstConflict = -1;
        std::vector<std::tuple<int,int,int> > queensAndConflicts = {};
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(queens[i][j]){
                    int conflictsThisQueenHas = numConflictsAt(i,j);
                    if(conflictsThisQueenHas > worstConflict){
                        worstConflict = conflictsThisQueenHas;
                        queensAndConflicts = {std::make_tuple(i,j,conflictsThisQueenHas)};
                    } else if (conflictsThisQueenHas == worstConflict){
                        queensAndConflicts.push_back(std::make_tuple(i,j,conflictsThisQueenHas));
                    }
                }
                    
            }
        }
        
        int randQueen = rand() % queensAndConflicts.size();

        moveQueen(std::get<0>(queensAndConflicts[randQueen]), std::get<1>(queensAndConflicts[randQueen]));
        
       
        if(cnt > 1e3 * n){
            std::cout << "Rerandomizing game" << std::endl;
            cnt = 0;
            initializeGame();
        }
        
    }
    std::cout << "Game is solved" << std::endl;
    printDiagnostic();
    return;
}

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
    if(cols[j] - 1 > 0)
        totalConflicts++;
    if(rows[i] - 1 > 0)
        totalConflicts++;
    if(mainDiags[(j-i)+(n-1)] - 1 > 0)
        totalConflicts++;
    if(reverseDiags[(i+j)] - 1 > 0)
        totalConflicts++;
    
    return totalConflicts;
}

int chessBoard::numConflictsAtNew(int i, int j){
    int totalConflicts = 0;
    if(cols[j] > 0)
        totalConflicts++;
    if(rows[i] > 0)
        totalConflicts++;
    if(mainDiags[(j-i)+(n-1)] > 0)
        totalConflicts++;
    if(reverseDiags[(i+j)] > 0)
        totalConflicts++;
    
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
void chessBoard::moveQueen(int i, int j){

    queens[i][j] = false;
    cols[j]--;
    rows[i]--;
    mainDiags[(j-i)+(n-1)]--;
    reverseDiags[i+j]--;
    
   std::tuple<int, int, int> newMoves = getMove(j);

    int newI = std::get<0>(newMoves);
    int newJ = std::get<1>(newMoves);
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
   for(int j = 0; j < n; j++){
        int randI = rand() % n;
        if(!queens[randI][j]){
            placeQueen(randI, j);
            count--;
        }

    }

}

/*Get the available moves for a queen */
std::tuple<int, int, int> chessBoard::getMove(int qj){
    std::vector<std::tuple<int, int, int> > newMoves;
    int bestMove = n+1;
    for(int i = 0; i < n; i++){
        if(!queens[i][qj]){
    
            int numConflictsNew = numConflictsAtNew(i,qj);
            if(numConflictsNew < bestMove){
                bestMove = numConflictsNew;
                newMoves = {std::make_tuple(i,qj,bestMove)};
            } else if(numConflictsNew == bestMove){
                newMoves.push_back(std::make_tuple(i,qj,bestMove));
            }
        }
    }
    int randMove = rand() % newMoves.size();
    return newMoves[randMove];  
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

    std::cout << std::endl;
    std::cout << "The number of queens on the board is: ";
    int total = 0;
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(queens[i][j])
                total++;
        }
    }
    std::cout << total << " queens" << std::endl;

}

