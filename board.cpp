#include "board.h"

#include <vector>
#include <iostream>
#include <ctype.h>

// Default constructor
Board::Board()
{
    cb = initializeBoard();
    //wa = initializeWhiteAttackBoard();
    //ba = initializeBlackAttackBoard();
    
    lm = initializeLastMove();
    
    wcp = true;
    bcp = true;
    
    wic = false;
    bic = false;
    
    wk = 4;
    bk = 60;
    
    turn = 0; // White turn
}

// Constructor with full arguments
Board::Board(std::vector<char> CB, LAST_MOVE LM, bool WCP, bool BCP, bool WIC, bool BIC, unsigned int WK, unsigned int BK, bool t)
{
    cb = CB;
    lm = LM;
    wcp = WCP;
    bcp = BCP;
    wic = WIC;
    bic = BIC;
    wk = WK;
    bk = BK;
    turn = t;
}

std::vector<char> Board::initializeBoard() {
    std::vector<char> board(SIZE, '-'); // initialize vector with size: vector<int> x (size, value)

    // Initialize white pieces
    board[0] = 'R';    board[1] = 'N';    board[2] = 'B';    board[3] = 'Q';
    board[4] = 'K';    board[5] = 'B';    board[6] = 'N';    board[7] = 'R';
    // White pawns
    board[8] = 'P';    board[9] = 'P';    board[10] = 'P';   board[11] = 'P';
    board[12] = 'P';   board[13] = 'P';   board[14] = 'P';   board[15] = 'P';

    // Initialize black pieces
    board[56] = 'r';   board[57] = 'n';   board[58] = 'b';   board[59] = 'q';
    board[60] = 'k';   board[61] = 'b';   board[62] = 'n';   board[63] = 'r';
    // Black pawns
    board[48] = 'p';   board[49] = 'p';   board[50] = 'p';   board[51] = 'p';
    board[52] = 'p';   board[53] = 'p';   board[54] = 'p';   board[55] = 'p';
    
    return board;
}

/*
std::vector<char> Board::initializeWhiteAttackBoard() {
    std::vector<char> board(SIZE, '-'); // initialize vector with size: vector<int> x (size, value)

    board[16] = 'W';    board[17] = 'W';    board[18] = 'W';    board[19] = 'W';
    board[20] = 'W';    board[21] = 'W';    board[22] = 'W';    board[23] = 'W';
    
    return board;
}

std::vector<char> Board::initializeBlackAttackBoard() {
    std::vector<char> board(SIZE, '-'); // initialize vector with size: vector<int> x (size, value)
    
    board[32] = 'B';    board[33] = 'B';    board[34] = 'B';    board[35] = 'B';
    board[36] = 'B';    board[37] = 'B';    board[38] = 'B';    board[39] = 'B';
    
    return board;
}
*/

LAST_MOVE Board::initializeLastMove() {
    LAST_MOVE lm;
    lm.piece = 'n';
    lm.start = 42;
    lm.end = 57;
    
    return lm;
}

void Board::printBoard(const std::vector<char> & board) {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            std::cout << board[i * 8 + j] << ' ';
        }
        std::cout << std::endl;
    }
}

Board::~Board()
{
    
}

