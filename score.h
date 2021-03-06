#ifndef SCORE_H
#define SCORE_H

const int PAWN_SCORE = 10;
const int B_PAWN_POS[64] =
{
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    10,10,10,10,10,10,10,10,
    20,20,20,20,20,20,20,20,
    30,30,30,30,30,30,30,30,
    40,40,40,40,40,40,40,40,
    50,50,50,50,50,50,50,50,
    100,100,100,100,100,100,100,100
};  
const int W_PAWN_POS[64] =
{
    100,100,100,100,100,100,100,100,
    50,50,50,50,50,50,50,50,
    40,40,40,40,40,40,40,40,
    30,30,30,30,30,30,30,30,
    20,20,20,20,20,20,20,20,
    10,10,10,10,10,10,10,10,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};


const int KNIGHT_SCORE = 30;
const int KNIGHT_POS[64] = 
{
    0,5,5,5,5,5,5,5,
    5,7,7,7,7,7,7,5,
    5,10,10,10,10,10,10,5,
    5,20,20,20,20,20,20,5,
    5,20,20,20,20,20,20,5,
    5,10,10,10,10,10,10,5,
    5,7,7,7,7,7,7,5,
    5,5,5,5,5,5,5,5

};

const int BISHOP_SCORE = 30;
const int BISHOP_POS[64] = 
{   
    0,0,0,0,0,0,0,0,
    10,10,10,10,10,10,10,10,
    20,20,20,20,20,20,20,20,
    30,30,30,30,30,30,30,30,
    30,30,30,30,30,30,30,30,
    20,20,20,20,20,20,20,20,
    10,10,10,10,10,10,10,10,
    0,0,0,0,0,0,0,0

};

const int ROOK_SCORE = 50;
const int B_ROOK_POS[64] = 
{
    10,2,2,2,2,2,2,10,
    3,3,3,3,3,3,3,3,
    2,2,2,2,2,2,2,2,
    2,2,2,2,2,2,2,2,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10
};

const int W_ROOK_POS[64] = 
{
    10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,
    1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,
    2,2,2,2,2,2,2,2,
    3,3,3,3,3,3,3,3,
    10,2,2,2,2,2,2,10
};

const int ROOK_POS_END[64] = 
{
    20,20,20,20,20,20,20,20,
    20,20,20,20,20,20,20,20,
    10,10,10,10,10,10,10,10,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    10,10,10,10,10,10,10,10,
    20,20,20,20,20,20,20,20,
    20,20,20,20,20,20,20,20
};



const int QUEEN_SCORE = 90;
const int W_QUEEN_POS[64] = 
{
    20,20,20,20,20,20,20,20,
    10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,
    20,20,20,20,20,20,20,20,
    30,30,30,30,30,30,30,30,
    20,20,20,20,20,20,20,20,
    10,10,10,10,10,10,10,10
};

const int B_QUEEN_POS[64] = 
{
    10,10,10,10,10,10,10,10,
    20,20,20,20,20,20,20,20,
    30,30,30,30,30,30,30,30,
    20,20,20,20,20,20,20,20,
    10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,
    10,10,10,10,10,10,10,10,
    20,20,20,20,20,20,20,20
};

const int QUEEN_POS_END[64] = 
{
  10,10,10,10,10,10,10,10,
  10,20,20,20,20,20,20,10,
  10,20,30,30,30,30,20,10,
  10,20,30,40,40,30,20,10,
  10,20,30,40,40,30,20,10,
  10,20,30,30,30,30,20,10,
  10,20,30,30,30,30,20,10,
  10,10,10,10,10,10,10,10,
};

const int KING_SCORE = 900;
const int W_KING_POS[64] = 
{
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    5,5,40,5,5,5,40,5
};

const int B_KING_POS[64] = 
{
    5,5,40,5,5,5,40,5,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

const int KING_POS_END[64] = {
  0,0,0,0,0,0,0,0,
  0,10,10,10,10,10,10,0,
  0,10,20,20,20,20,10,0,
  0,10,20,30,30,20,10,0,
  0,10,20,30,30,20,10,0,
  0,10,20,20,20,20,10,0,
  0,10,10,10,10,10,10,0,
  0,0,0,0,0,0,0,0,
};


#endif
