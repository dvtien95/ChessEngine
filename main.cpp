#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

const int SIZE = 64; // Board size in 1D array.
const char PROMOTIONLISTSIZE = 4;
const char promotionList[PROMOTIONLISTSIZE] = {'N', 'B', 'R', 'Q'}; // List of what pawn can promote to

vector<char> testBoard();
vector<char> initializeBoard();
void printBoard(const vector<char> &currentBoard);
vector<vector<char> > calculateNextStates(const vector<char> &currentBoard);
void calculatePawnMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
void calculateKingMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
void calculateKnightMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
void calculateRookMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
void calculateBishopMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
void calculateQueenMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
void updateMoves(int curPos, int nextPos, char nextPiece, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
bool isEmpty(char c);
bool isNotEmpty(char c);
bool isWhite(char c);
bool isBlack(char c);
bool isSameSide(char p1, char p2);
bool isDifferentSide(char p1, char p2);
bool isOnBoard(int pos);
bool isValidRC(int rc);

int main()
{

    // Initialize board
    vector<char> Board = initializeBoard();

    // print board
    //printBoard(Board);

    // calculate next moves
    //vector<vector<char>> next = calculateNextStates(Board);
    
    vector<char> tb = testBoard();
    cout << "Testing Board: " << endl;
    printBoard(tb);
    vector<vector<char> > next = calculateNextStates(tb);
    
    cout << "Next states board: " << endl;
    for (int i = 0; i < next.size(); i++) {
        printBoard(next[i]); cout << endl;
    }

}

vector<char> testBoard()
{
    vector<char> Board(SIZE, '-'); // initialize vector with size: vector<int> x (size, value)

    //Board[48] = 'P';
    
    //Board[11] = 'P';
    //Board[12] = 'P';
    //Board[13] = 'P';
    
    // Board[52] = 'R';
    
//    Board[52] = 'B';
//    Board[44] = 'q';
//    Board[56] = 'q';
//     Board[7] = 'q';
//     Board[0] = 'q';
//    Board[61] = 'K';
    Board[36] = 'k';
    Board[34] = 'k';
    Board[43] = 'k';
    Board[27] = 'k';

    Board[42] = 'k';
    Board[44] = 'k';
    Board[26] = 'k';
    Board[28] = 'k';

    Board[35] = 'Q';
    // Board[29] = 'n';
    
    //Board[41] = 'N';

    return Board;
}

// Initialize starting board
// Make board of 64 char, capital character represents white, non-cap represents black. Ex: 'K' is white King
// The board index will take care of the position. Ex: Board[0] is a1. Board[1] is b1. Board[63] is h8.
vector<char> initializeBoard()
{
    vector<char> Board(SIZE, '-'); // initialize vector with size: vector<int> x (size, value)

    // Initialize white pieces
    Board[0] = 'R';
    Board[1] = 'N';
    Board[2] = 'B';
    Board[3] = 'Q';
    Board[4] = 'K';
    Board[5] = 'B';
    Board[6] = 'N';
    Board[7] = 'R';
    // White pawns
    Board[8] = 'P';
    Board[9] = 'P';
    Board[10] = 'P';
    Board[11] = 'P';
    Board[12] = 'P';
    Board[13] = 'P';
    Board[14] = 'P';
    Board[15] = 'P';

    // Initialize black pieces
    Board[56] = 'r';
    Board[57] = 'n';
    Board[58] = 'b';
    Board[59] = 'q';
    Board[60] = 'k';
    Board[61] = 'b';
    Board[62] = 'n';
    Board[63] = 'r';
    // Black pawns
    Board[48] = 'p';
    Board[49] = 'p';
    Board[50] = 'p';
    Board[51] = 'p';
    Board[52] = 'p';
    Board[53] = 'p';
    Board[54] = 'p';
    Board[55] = 'p';

    return Board;
}

// Print playing chessboard 8x8 in viewer's eyes
void printBoard(const vector<char> &currentBoard)
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << currentBoard[i * 8 + j] << " ";
        }
        cout << endl;
    }
}

// This function returns a vector of boards representing all legal next moves of a player
vector<vector<char> > calculateNextStates(const vector<char> &currentBoard)
{
    vector<vector<char> > allPossibleBoards;

    // return all possible states of the board
    for (int i = 0; i < SIZE; i++)
    {
        // if there is a piece and the pice is white, calculate next move, push result
        if (isNotEmpty(currentBoard[i]) && isWhite(currentBoard[i]))
        {
            switch (currentBoard[i])
            {
            case 'P':
            case 'p':
                // Case Pawn
                    calculatePawnMoves(currentBoard[i], i, currentBoard, allPossibleBoards);
                    break;
            case 'N':
            case 'n':
                // Case Knight
                    calculateKnightMoves(currentBoard[i], i, currentBoard, allPossibleBoards);
                    break;
            case 'R':
            case 'r':
                // Case Rook
                    calculateRookMoves(currentBoard[i], i, currentBoard, allPossibleBoards);
                    break;
            case 'B':
            case 'b':
                // Case Bishop
                calculateBishopMoves(currentBoard[i], i, currentBoard, allPossibleBoards);
                    break;
            case 'Q':
            case 'q':
                // Case Queen
                calculateQueenMoves(currentBoard[i], i, currentBoard, allPossibleBoards);
                    break;
            case 'K':
            case 'k':
                // Case King
                //calculateKingMoves(currentBoard[i], i, currentBoard, allPossibleBoards);
                break;
            default:
                break;
            }
        }
    }

    return allPossibleBoards;
}

// Calculate all possible moves of this Pawn given pos and currentBoard.
// If there are possible move(s), push the next state to allPossibleBoards (pass by reference).
void calculatePawnMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards)
{
    // White Pawn
    if (isWhite(piece)) {
        if (pos / 8 == 8) return; // take care of stupid case (whitePawn at row 8)
        
        int row = pos / 8;
        int col = pos % 8;
        
        // White Pawn at previous-to-promote rank
        if (pos / 8 == 6) {
            // Pawn move forward and promote
            if (currentBoard[pos+8] == '-') {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateMoves(pos, pos+8, promotionList[i], currentBoard, allPossibleBoards);
                }
            }
            // Check for ability to capture and promote
            // If up left square is valid and has a black piece
            int posUL = (row+1)*8 + col-1;
            if (row+1 < 8 && col-1 >= 0 && isNotEmpty(currentBoard[posUL]) && isBlack(currentBoard[posUL]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateMoves(pos, posUL, promotionList[i], currentBoard, allPossibleBoards);
                }
            }
            // If up right square is valid and has a black piece
            int posUR = (row+1)*8 + col+1;
            if (row+1 < 8 && col+1 >= 0 && isNotEmpty(currentBoard[posUL]) && isBlack(currentBoard[posUR]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateMoves(pos, posUR, promotionList[i], currentBoard, allPossibleBoards);
                }
            }
            return;
        }
        
        // Pawn at starting square and the forward two squares is empty
        if (pos / 8 == 1 && currentBoard[pos+8] == '-' && currentBoard[pos+16] == '-') {
            updateMoves(pos, pos+16, piece, currentBoard, allPossibleBoards);
        }
        // If forward square is valid
        if (currentBoard[pos+8] == '-') {
            updateMoves(pos, pos+8, piece, currentBoard, allPossibleBoards);
        }
        // If up left square is valid and not empty and has a black piece
        int posUL = (row+1)*8 + col-1;
        if (row+1 < 8 && col-1 >= 0 && isNotEmpty(currentBoard[posUL]) && isBlack(currentBoard[posUL]) ) {
            updateMoves(pos, posUL, piece, currentBoard, allPossibleBoards);
        }
        // If up right square is valid and not empty and  has a black piece
        int posUR = (row+1)*8 + col+1;
        if (row+1 < 8 && col+1 >= 0 && isNotEmpty(currentBoard[posUR]) && isBlack(currentBoard[posUR]) ) {
            updateMoves(pos, posUR, piece, currentBoard, allPossibleBoards);
        }
    }
    // Black Pawn
    else {
        if (pos / 8 == 0) return; // take care of stupid case (blackPawn at row 8)

        int row = pos / 8;
        int col = pos % 8;
        
        // Black Pawn at previous-to-promote rank
        if (pos / 8 == 1) {
            // Pawn move forward and promote
            if (currentBoard[pos-8] == '-') {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateMoves(pos, pos-8, promotionList[i], currentBoard, allPossibleBoards);
                }
            }
            // Check for ability to capture and promote
            // If up left square is valid and has a black piece
            int posDL = (row-1)*8 + col-1;
            if (row-1 < 8 && col-1 >= 0 && isBlack(currentBoard[posDL]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateMoves(pos, posDL, promotionList[i], currentBoard, allPossibleBoards);
                }
            }
            // If up right square is valid and has a black piece
            int posDR = (row-1)*8 + col+1;
            if (row-1 < 8 && col+1 >= 0 && isBlack(currentBoard[posDR]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateMoves(pos, posDR, promotionList[i], currentBoard, allPossibleBoards);
                }
            }
            return;
        }
        
        // Pawn at starting square and the forward two squares is empty
        if (pos / 8 == 6 && currentBoard[pos+8] == '-' && currentBoard[pos-16] == '-') {
            updateMoves(pos, pos-16, piece, currentBoard, allPossibleBoards);
        }
        // If forward square is valid
        if (currentBoard[pos-8] == '-') {
            updateMoves(pos, pos-8, piece, currentBoard, allPossibleBoards);
        }
        // If up left square is valid and not empty and has a black piece
        int posDL = (row-1)*8 + col-1;
        if (row-1 < 8 && col-1 >= 0 && isNotEmpty(currentBoard[posDL]) && isWhite(currentBoard[posDL]) ) {
            updateMoves(pos, posDL, piece, currentBoard, allPossibleBoards);
        }
        // If up right square is valid and not empty and  has a black piece
        int posDR = (row-1)*8 + col+1;
        if (row-1 < 8 && col+1 >= 0 && isNotEmpty(currentBoard[posDR]) && isWhite(currentBoard[posDR]) ) {
            updateMoves(pos, posDR, piece, currentBoard, allPossibleBoards);
        }
    }
}

// Calculate all possible moves of this Knight given pos and currentBoard.
// If there are possible move(s), push the next state to allPossibleBoards (pass by reference).
void calculateKnightMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > & allPossibleBoards)
{
    // nnp holds Next (legal) Knight Positions
    vector<int> nnp;
    int validPos;
    // Converting pos (1D) to row and column (2D) by formula: pos = row * 8 + col;
    int row = pos / 8;
    int col = pos % 8;
    
    // Check for square validity in 2D-board form, convert back to pos, push to nnp if legal position.
    if (row+1 < 8 && col-2 >= 0) {
        nnp.push_back( (row+1)*8 + col-2 );
    }
    if (row+1 < 8 && col+2 < 8) {
        nnp.push_back( (row+1)*8 + col+2 );
    }
    if (row+2 < 8 && col-1 >= 0) {
        nnp.push_back( (row+2)*8 + col-1 );
    }
    if (row+2 < 8 && col+1 < 8) {
        nnp.push_back( (row+2)*8 + col+1 );
    }
    if (row-1 >= 0 && col-2 >= 0) {
        nnp.push_back( (row-1)*8 + col-2 );
    }
    if (row-1 >= 0 && col+2 < 8) {
        nnp.push_back( (row-1)*8 + col+2 );
    }
    if (row-2 >= 0 && col-1 >= 0) {
        nnp.push_back( (row-2)*8 + col-1 );
    }
    if (row-2 >= 0 && col+1 < 8) {
        nnp.push_back( (row-2)*8 + col+1 );
    }
    
    for (int i = 0; i < nnp.size(); i++) {
        int n = nnp[i];
        // if n onBoard && currentBoard at n is Empty || (currentBoard at n is not empty but piece are on different sides )
        // then add new next states of the board to allPossibleBoards.
        if ((currentBoard[n] == '-') || ( isNotEmpty(currentBoard[n]) && isDifferentSide(piece, currentBoard[n])) ) {
            //updateMoves(int curPos, int nextPos, char nextPiece, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards);
            updateMoves(pos, n, piece, currentBoard, allPossibleBoards);
        }
    }
}

// Calculate all possible moves of this Rook given pos and currentBoard.
// If there are possible move(s), push the next state to allPossibleBoards (pass by reference).
void calculateRookMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards)
{ 
    int row = pos / 8;
    int col = pos % 8;

    //Rook forward movement
    int fwd = row + 1;
    while(currentBoard[8*fwd+col] == '-'  && fwd < 8) {
            updateMoves(pos,8*fwd+col,piece,currentBoard,allPossibleBoards);
            fwd++;
        }
    // Rook forward capture piece
    if (isDifferentSide(piece, currentBoard[8*fwd+col]) && fwd < 8)
    {
        updateMoves(pos,8*fwd+col,piece,currentBoard,allPossibleBoards);
    }
    
     //Rook backward movement
    int bwd = row - 1;
    while(currentBoard[8*bwd+col] == '-'  && bwd >= 0) {
            updateMoves(pos,8*bwd+col,piece,currentBoard,allPossibleBoards);
            bwd--;
        }


    // Rook backward capture piece
    if (isDifferentSide(piece,currentBoard[8*bwd+col]) && bwd >= 0)
    {
        updateMoves(pos,8*bwd+col,piece,currentBoard,allPossibleBoards);
    }

    // Rook right movement
    int rw = col + 1;
    while(currentBoard[8*row+rw] == '-' && rw < 8){
        updateMoves(pos,8*row+rw,piece,currentBoard,allPossibleBoards);
        rw++;
    }
    if (isDifferentSide(piece,currentBoard[8*row+rw]) && rw < 8)
    {
       updateMoves(pos,8*row+rw,piece,currentBoard,allPossibleBoards);
    }

    // Rook left movement
    int lw = col - 1;
    while(currentBoard[8*row+lw] == '-' && lw >= 0) {
     
        updateMoves(pos,8*row+lw,piece,currentBoard,allPossibleBoards);
        lw--;
    }
    if (isDifferentSide(piece,currentBoard[8*row-lw]) && lw >= 0)
    {
        updateMoves(pos,8*row+lw,piece,currentBoard,allPossibleBoards);
    }
}

// Calculate all possible moves of this Bishop given pos and currentBoard.
// If there are possible move(s), push the next state to allPossibleBoards (pass by reference).
void calculateBishopMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards)
{   
    int row = pos / 8;
    int col = pos % 8;
    
    // Forward diagonal right
   while(currentBoard[8*(row+1)+col+1] == '-' && (row < 8 && col < 8)) {
       updateMoves(pos, 8*(row+1)+col+1, piece, currentBoard, allPossibleBoards);
       row++;
       col++;
   }
   // Capture forward diagonal right
   if (isDifferentSide(piece,currentBoard[8*(row+1)+col+1]) && 8*(row+1)+col+1 < 64) {
       updateMoves(pos, 8*(row+1)+col+1, piece, currentBoard, allPossibleBoards);
   }

   // Forward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(currentBoard[8*(row+1)+(col-1)] == '-' && row < 8 && col > 0) {
       updateMoves(pos, 8*(row+1)+(col-1), piece, currentBoard, allPossibleBoards);
       row++;
       col--;
   }
   // Capture forward diagonal left
   if (isDifferentSide(piece,currentBoard[8*(row+1)+col-1]) && row < 8 && col > 0){
        updateMoves(pos, 8*(row+1)+col-1, piece, currentBoard, allPossibleBoards);
   }

   // Backward diagonal right
   row = pos / 8;
   col = pos % 8;
   while(currentBoard[8*(row-1)+(col+1)] == '-' && row > 0 && col < 8) {
       updateMoves(pos, 8*(row-1)+(col+1), piece, currentBoard, allPossibleBoards);
       row--;
       col++;
   }
   // Capture Backward diagonal right
    if (isDifferentSide(piece,currentBoard[8*(row-1)+col+1]) && row > 0 && col < 8){
        updateMoves(pos, 8*(row-1)+col+1, piece, currentBoard, allPossibleBoards);
   }
   // Backward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(currentBoard[8*(row-1)+(col-1)] == '-' && row > 0 && col > 0) {
       updateMoves(pos, 8*(row-1)+(col-1), piece, currentBoard, allPossibleBoards);
       row--;
       col--;
   }
   // Capture Backward diagonal left
    if (isDifferentSide(piece,currentBoard[8*(row-1)+col-1]) && row > 0 && col > 0){
        updateMoves(pos, 8*(row-1)+col-1, piece, currentBoard, allPossibleBoards);
   }
}

// Calculate all possible moves of this Queen given pos and currentBoard.
// If there are possible move(s), push the next state to allPossibleBoards (pass by reference).
void calculateQueenMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards)
{
    /* Write code here*/
    int row = pos / 8;
    int col = pos % 8;

    //Forward movement
    int fwd = row + 1;
    while(currentBoard[8*fwd+col] == '-'  && fwd < 8) {
            updateMoves(pos,8*fwd+col,piece,currentBoard,allPossibleBoards);
            fwd++;
        }
    // Forward capture piece
    if (isDifferentSide(piece, currentBoard[8*fwd+col]) && fwd < 8)
    {
        updateMoves(pos,8*fwd+col,piece,currentBoard,allPossibleBoards);
    }
    
     // Backward movement
    int bwd = row - 1;
    while(currentBoard[8*bwd+col] == '-'  && bwd >= 0) {
            updateMoves(pos,8*bwd+col,piece,currentBoard,allPossibleBoards);
            bwd--;
        }


    // Backward capture piece
    if (isDifferentSide(piece,currentBoard[8*bwd+col]) && bwd >= 0)
    {
        updateMoves(pos,8*bwd+col,piece,currentBoard,allPossibleBoards);
    }

    // Right movement
    int rw = col + 1;
    while(currentBoard[8*row+rw] == '-' && rw < 8){
        updateMoves(pos,8*row+rw,piece,currentBoard,allPossibleBoards);
        rw++;
    }
    if (isDifferentSide(piece,currentBoard[8*row+rw]) && rw < 8)
    {
       updateMoves(pos,8*row+rw,piece,currentBoard,allPossibleBoards);
    }

    // Left movement
    int lw = col - 1;
    while(currentBoard[8*row+lw] == '-' && lw >= 0) {
     
        updateMoves(pos,8*row+lw,piece,currentBoard,allPossibleBoards);
        lw--;
    }
    if (isDifferentSide(piece,currentBoard[8*row-lw]) && lw >= 0)
    {
        updateMoves(pos,8*row+lw,piece,currentBoard,allPossibleBoards);
    }

     // Forward diagonal right
   while(currentBoard[8*(row+1)+col+1] == '-' && (row < 8 && col < 8)) {
       updateMoves(pos, 8*(row+1)+col+1, piece, currentBoard, allPossibleBoards);
       row++;
       col++;
   }
   // Capture forward diagonal right
   if (isDifferentSide(piece,currentBoard[8*(row+1)+col+1]) && 8*(row+1)+col+1 < 64) {
       updateMoves(pos, 8*(row+1)+col+1, piece, currentBoard, allPossibleBoards);
   }

   // Forward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(currentBoard[8*(row+1)+(col-1)] == '-' && row < 8 && col > 0) {
       updateMoves(pos, 8*(row+1)+(col-1), piece, currentBoard, allPossibleBoards);
       row++;
       col--;
   }
   // Capture forward diagonal left
   if (isDifferentSide(piece,currentBoard[8*(row+1)+col-1]) && row < 8 && col > 0){
        updateMoves(pos, 8*(row+1)+col-1, piece, currentBoard, allPossibleBoards);
   }

   // Backward diagonal right
   row = pos / 8;
   col = pos % 8;
   while(currentBoard[8*(row-1)+(col+1)] == '-' && row > 0 && col < 8) {
       updateMoves(pos, 8*(row-1)+(col+1), piece, currentBoard, allPossibleBoards);
       row--;
       col++;
   }
   // Capture Backward diagonal right
    if (isDifferentSide(piece,currentBoard[8*(row-1)+col+1]) && row > 0 && col < 8){
        updateMoves(pos, 8*(row-1)+col+1, piece, currentBoard, allPossibleBoards);
   }
   // Backward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(currentBoard[8*(row-1)+(col-1)] == '-' && row > 0 && col > 0) {
       updateMoves(pos, 8*(row-1)+(col-1), piece, currentBoard, allPossibleBoards);
       row--;
       col--;
   }
   // Capture Backward diagonal left
    if (isDifferentSide(piece,currentBoard[8*(row-1)+col-1]) && row > 0 && col > 0){
        updateMoves(pos, 8*(row-1)+col-1, piece, currentBoard, allPossibleBoards);
   }
}

// Calculate all possible moves of this King given pos and currentBoard.
// If there are possible move(s), push the next state to allPossibleBoards (pass by reference).
void calculateKingMoves(char piece, int pos, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards)
{
    /* Write code here*/
}

void updateMoves(int curPos, int nextPos, char nextPiece, const vector<char> &currentBoard, vector<vector<char> > &allPossibleBoards) {
    vector<char> newBoard = currentBoard;
    newBoard[curPos] = '-';
    newBoard[nextPos] = nextPiece;
    allPossibleBoards.push_back(newBoard);
}

bool isEmpty(char c) {
    return c == '-';
}

bool isNotEmpty(char c) {
    return c != '-';
}

bool isWhite(char c)
{
    return isupper(c);
}

bool isBlack(char c)
{
    return !isupper(c);
}

bool isSameSide(char p1, char p2) {
    return (isupper(p1) && isupper(p2)) || (!isupper(p1) && !isupper(p2));
}

bool isDifferentSide(char p1, char p2) {
    return (isupper(p1) && !isupper(p2)) || (!isupper(p1) && isupper(p2));
}

bool isOnBoard(int pos) {
    return 0 <= pos && pos < 64;
}

bool isValidRC(int rc) {
    return 0 <= rc && rc < 8;
}
            
        
