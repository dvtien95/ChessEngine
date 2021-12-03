#ifndef BOARD_H
#define BOARD_H

#include <vector>

const int SIZE = 64;

struct LAST_MOVE {
    char piece; // What piece made the last move
    unsigned int start;  // Starting square of last move
    unsigned int end;    // Ending square of last move
};

class Board
{
public: // This can change to private later
    // Variable
    
    // Make board of 64 char, capital character represents white, non-cap represents black. Ex: 'K' is white King
    // The board index will take care of the position. Ex: Board[0] is a1. Board[1] is b1. Board[63] is h8.
    std::vector<char> cb; // current board
    
    LAST_MOVE lm;
    
    bool wcp;   // white castle privilege
    bool bcp;   // black castle privilege
    
    bool wic;   // white in check
    bool bic;   // black in check
    
    unsigned int wk;     // current White King position, make default 64 (max is 63)
    unsigned int bk;     // current Black King position, make default 65 (max is 63)
    
    bool turn;  // false or 0 is White, true or 1 is black
    
public:
    // Method
    Board();

    Board(std::vector<char> CB, LAST_MOVE LM, bool WCP, bool BCP, bool WIC, bool BIC, unsigned int WK, unsigned int BK, bool t);
    
    std::vector<char> initializeBoard();
    //std::vector<char> initializeWhiteAttackBoard();
    //std::vector<char> initializeBlackAttackBoard();
    LAST_MOVE initializeLastMove();
    
    void printBoard(const std::vector<char> & board);
    
    ~Board();
};

#endif
