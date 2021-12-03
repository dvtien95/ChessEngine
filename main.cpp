#include <iostream>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <vector>
#include <ctype.h> // toupper, tolower
#include <ctime>
#include <fstream>
#include <stack>
#include "board.h"
#include "tree.h"
#include "score.h"

#include <omp.h>

using namespace std;

const char PROMOTIONLISTSIZE = 4;
const char promotionList[PROMOTIONLISTSIZE] = {'N', 'B', 'R', 'Q'}; // List of what pawn can promote to
const string chessOfficialSquares[64] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
};

int myNode = 1;    // Total node count

vector<char> readBoard(string filename);
void writeBoard(string filename, vector<Board> &allPossibleBoards);
vector<char> testBoard();
void printBoard(const vector<char> &currentBoard);


void calculatePawnMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);
void calculateKnightMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);
void calculateRookMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);
void calculateBishopMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);
void calculateQueenMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);
void calculateKingMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);

void nextStates(const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);
void updateStates(int curPos, int nextPos, char curPiece, char nextPiece, vector<char> newBoard, bool wcp, bool bcp, unsigned int wk, unsigned int bk, bool t, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode);

void calculatingDepth(Tree & boardTree, Node* & bestNode);

int calculateScoreCurBoard(const Board & board);

void insert(const Board & b, Node* & curNode, Node* & parent, const int & myScore, int & curScore, Node* & bestNode);

void playChess(Board & curBoard);

int convertChessSquare(const string & s);

bool isWhiteInCheck(const vector<char> & cb, int pos);  // Give current board and king position
bool isBlackInCheck(const vector<char> & cb, int pos);  // Give current board and king position

bool isEmpty(char c);
bool isNotEmpty(char c);
bool isWhite(char c);
bool isBlack(char c);
bool isSameSide(char p1, char p2);
bool isDifferentSide(char p1, char p2);
bool isOnBoard(int pos);
bool isValidRC(int rc);

int checkPosScore(int pos);

int main()
{
    // Initialize board
    
    //Board(std::vector<char> CB, LAST_MOVE LM, bool WCP, bool BCP, bool WIC, bool BIC, unsigned int WK, unsigned int BK, bool t);
    vector<char> tb = testBoard();
    //vector<char> tb = readBoard("test1.txt");
//    LAST_MOVE lm; lm.piece = 'P'; lm.start = 8; lm.end = 24;
    LAST_MOVE lm; lm.piece = 'p'; lm.start = 51; lm.end = 35;
    bool turn = 0;  // Change turn
    Board testBoard(tb, lm, true, true, false, false, 4, 60, turn);
    if (turn == 0) { cout << "White's turn to move" << endl; }
    else { cout << "Black's turn to move" << endl;  }
    
    Board tmpBoard;
    //Tree boardTree(tmpBoard);
    
    cout << "--------------------" << endl;
    printBoard(tmpBoard.cb);
    cout << "--------------------" << endl;
    
    /* --Branching out from starting node--*/
//    Tree boardTree(tmpBoard);
//    Node * myNode = new Node;
//    calculatingDepth(boardTree, myNode);
//    myNode = NULL;
//    delete myNode;
    
    /* --Playing chess-- */
    playChess(tmpBoard);
}

vector<char> testBoard()
{
    vector<char> Board(SIZE, '-'); // initialize vector with size: vector<int> x (size, value)
    
    // PAWN TEST
    /*
    Board[14] = 'P';    // Check starting pawn

    Board[11] = 'P';    // Check block
    Board[19] = 'n';
    
    Board[55] = 'P';    // Check Promotion
    Board[15] = 'p';
    
    Board[36] = 'P';    // Check en-Passant
    Board[37] = 'p';
    Board[35] = 'p';
    
    Board[25] = 'p';    // Check en-Passant
    Board[24] = 'P';
    */
    
    // Knight test
//    Board[8] = 'N';     // Knight corner
//    Board[15] = 'n';
//
//    Board[28] = 'N';    // Knight capture
//    Board[18] = 'b';
//    Board[43] = 'Q';
//    Board[22] = 'K';
    // Check test
//    Board[31] = 'q';
//    Board[0] = 'R';
//    Board[11] = 'N';
//    Board[41] = 'N';
//    Board[24] = 'q';
    //Board[51] = 'P';
    
     //Castle Move
    Board[11] = 'P';
    Board[12] = 'P';
    Board[4] = 'K';
    Board[0] = 'R';
    Board[7] = 'R';
    Board[17] = 'n';
    
//    Board[56] = 'r';
//    Board[30] = 'N';
//    Board[2] = 'R';

    // Put king on both side
    // Board[4] = 'K';
    // Board[60] = 'k';
    
    return Board;
}


void playChess(Board & curBoard) {
    while (true) {
        /*-- Check possible moves ahead for player --*/
        int tmpScore = 0;
        Node * tmpBestNode = new Node;
        Tree playerNextBoard(curBoard);
        // Check next states ahead
        nextStates(playerNextBoard.root->board, playerNextBoard.root, playerNextBoard.root, tmpScore, tmpBestNode);
        
        if (playerNextBoard.root->children.size() == 0) {
            cout << "Check mate!" << endl;
            tmpBestNode = NULL;
            delete tmpBestNode;
            break;
        }
        cout << "Opponent last move: " << curBoard.lm.piece << "-" << chessOfficialSquares[curBoard.lm.start] << "-" << chessOfficialSquares[curBoard.lm.end] << endl;
        /*-- List possible moves ahead for player --*/
        cout << "List of possible moves: " << endl;
        for (unsigned int i = 0; i < playerNextBoard.root->children.size(); i++) {
            cout << playerNextBoard.root->children[i]->board.lm.piece << "-";
            cout << chessOfficialSquares[playerNextBoard.root->children[i]->board.lm.start] << "-";
            cout << chessOfficialSquares[playerNextBoard.root->children[i]->board.lm.end] << "  ";
        }
        cout << endl;
        
        /*-- User Input --*/
        bool flag = false;
        
        while (flag == false) {
            string s;
            do {
            cout << "Enter valid move (ex: Piece-starting-ending) " << endl; // Type a number and press enter
            cin >> s; // Get user input from the keyboard
            } while (s.length() != 7);
                
            /*-- Process user input --*/
            string curPos, nextPos;
            curPos = s.substr(2,2);     // s.substr(index, length)
            nextPos = s.substr(5,2);
            char curPiece;
            curPiece = s[0];
            
            /*-- Check legal move --*/
            for (unsigned int i = 0; i < playerNextBoard.root->children.size(); i++) {
                if (playerNextBoard.root->children[i]->board.lm.piece == curPiece &&
                    chessOfficialSquares[playerNextBoard.root->children[i]->board.lm.start] == curPos &&
                    chessOfficialSquares[playerNextBoard.root->children[i]->board.lm.end] == nextPos) {
                    // INSERT HERE ..: If pawn move to back rank, promote, but right now always promote to Queen
                    curBoard = playerNextBoard.root->children[i]->board;
                    flag = true;
                }
            }
        }
        
        tmpBestNode = NULL;
        delete tmpBestNode;
        
        printBoard(curBoard.cb);
        
        /*-- Computer response --*/
        // Calculate moves
        Tree boardTree(curBoard);
        Node * curBestNode = new Node;
        
        calculatingDepth(boardTree, curBestNode);
        
        if (boardTree.root->children.size() == 0) {
            tmpBestNode = NULL;
            delete tmpBestNode;
            curBestNode = NULL;
            delete curBestNode;
            cout << "Check mate!" << endl;
            break;
        }
        
        // Evaluates moves
        
        // Pick a move, update board
        //int depth1 = rand() % boardTree.root->children.size();
        curBoard = curBestNode->board;
        
        printBoard(curBoard.cb);
        
        curBestNode = NULL;
        delete curBestNode;
    }
}

void calculatingDepth(Tree & boardTree, Node* & bestNode) {
    /*--GetTime OMP--*/
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    /*--GetTime Serial--*/
//    srand(time(NULL));
//    const clock_t begin_time = clock();
    
    boardTree.root->score = 0;
    
    int curScore = -10000;
    /*--Depth1--*/
    nextStates(boardTree.root->board, boardTree.root, boardTree.root, curScore, bestNode);   // Make the root point to itself, should change this
    
    cout << "---------------------------------" << endl;
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    cout << "Nodes: " << myNode << " Depth 1: " << float(exec_time) << "s" << endl;
    
    curScore = -10000;
    /*--Depth2--*/
    for (unsigned int i = 0; i < boardTree.root->children.size(); i++) {  // for each node in depth 1
        nextStates(boardTree.root->children[i]->board, boardTree.root->children[i], boardTree.root, curScore, bestNode);
    }
    
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    cout << "Nodes: " << myNode << " Depth 2: " << float(exec_time) << "s" << endl;
    
    curScore = -10000;
    /*--Depth3--*/
    #pragma omp parallel for
    for (unsigned int i = 0; i < boardTree.root->children.size(); i++) {   // Depth 1
        //#pragma omp parallel for
        for (unsigned int j = 0; j < boardTree.root->children[i]->children.size(); j++) {  // Depth 2
            nextStates(boardTree.root->children[i]->children[j]->board, boardTree.root->children[i]->children[j], boardTree.root->children[i], curScore, bestNode);
        }
    }
    
    
    /* Pruning min-max alpha beta at depth 3 (look forward 2 moves), choosing best 2 Nodes: */
    #pragma omp parallel for
    for (unsigned int i = 0; i < boardTree.root->children.size(); i++) {   // Depth 1
        for (unsigned int j = 0; j < boardTree.root->children[i]->children.size(); j++) {  // Depth 2
            Node * nodeOne = NULL;
            Node * nodeTwo = NULL;

            // Pointer to parent
            Node * curParent = boardTree.root->children[i]->children[j];
            
            int nodeSize = curParent->children.size();
            myNode = myNode - nodeSize + 2;

            // Find loop through parent, find two best nodes
            for (unsigned int k = 0; k < curParent->children.size(); k++) { // Depth 3
                Node * myCurNode = curParent->children[k];
                if (nodeOne == NULL) {  // nodeOne not assigned
                    nodeOne = myCurNode;
                } else if (nodeTwo == NULL) { // nodeTwo not assigned
                    if (myCurNode->score > nodeOne->score) { // If curNode > NodeOne
                        nodeTwo = myCurNode;
                    } else { // If curNode < NodeOne
                        nodeTwo = nodeOne;
                        nodeOne = myCurNode;
                    }
                } else { // Both node assigned
                    // Comparision:
                    if (myCurNode->score <= nodeOne->score) { // myCureNode < nodeOne < nodeTwo
                        continue;
                    }
                    else if (nodeOne->score < myCurNode->score && myCurNode->score <= nodeTwo->score) {
                        nodeOne = myCurNode;
                    }
                    else {
                        nodeOne = nodeTwo;
                        nodeTwo = myCurNode;
                    }
                }

                myCurNode = NULL;
                delete myCurNode;
            }

            // Delete unecessary node
            for (unsigned int k = 0; k < curParent->children.size(); k++) {
                curParent->children[k] = NULL;
                delete curParent->children[k];
            }
            curParent->children.clear();
            curParent->children.shrink_to_fit();

            // Assigning 2 best nodes
            if (nodeOne != NULL) { nodeOne->parent = curParent; curParent->children.push_back(nodeOne); bestNode = nodeOne; curScore = nodeOne->score; }
            if (nodeTwo != NULL) { nodeTwo->parent = curParent; curParent->children.push_back(nodeTwo); bestNode = nodeTwo; curScore = nodeTwo->score; }
            if (nodeOne == NULL && nodeTwo == NULL) { bestNode = curParent; curScore = curParent->score; };


            // Delete tmpUsingNode
            curParent = NULL; nodeOne = NULL; nodeTwo = NULL;
            delete curParent; delete nodeOne; delete nodeTwo;
        }
    }
    
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    cout << "Nodes: " << myNode << " Depth 3: " << float(exec_time) << "s" << endl;
    
    curScore = -10000;
    /*--Depth4--*/
    #pragma omp parallel for
    for (unsigned int i = 0; i < boardTree.root->children.size(); i++) {   // Depth 1
        //#pragma omp parallel for
        for (unsigned int j = 0; j < boardTree.root->children[i]->children.size(); j++) {  // Depth 2
            for (unsigned int k = 0; k < boardTree.root->children[i]->children[j]->children.size(); k++) { // Depth 3
                nextStates(boardTree.root->children[i]->children[j]->children[k]->board, boardTree.root->children[i]->children[j]->children[k], boardTree.root->children[i]->children[j], curScore, bestNode);
            }
        }
    }
    
    /* Pruning min-max alpha beta at depth 4 (look forward 3 moves), choosing best 2 Nodes: */
    #pragma omp parallel for
    for (unsigned int i = 0; i < boardTree.root->children.size(); i++) {   // Depth 1
        for (unsigned int j = 0; j < boardTree.root->children[i]->children.size(); j++) {  // Depth 2
            for (unsigned int k = 0; k < boardTree.root->children[i]->children[j]->children.size(); k++) { // Depth 3
                Node * nodeOne = NULL;
                Node * nodeTwo = NULL;

                // Pointer to parent
                Node * curParent = boardTree.root->children[i]->children[j]->children[k];
                
                int nodeSize = curParent->children.size();
                myNode = myNode - nodeSize + 2;

                // Find loop through parent, find two best nodes
                for (unsigned int l = 0; l < curParent->children.size(); l++) { // Depth 3
                    Node * myCurNode = curParent->children[l];
                    if (nodeOne == NULL) {  // nodeOne not assigned
                        nodeOne = myCurNode;
                    } else if (nodeTwo == NULL) { // nodeTwo not assigned
                        if (myCurNode->score > nodeOne->score) { // If curNode > NodeOne
                            nodeTwo = myCurNode;
                        } else { // If curNode < NodeOne
                            nodeTwo = nodeOne;
                            nodeOne = myCurNode;
                        }
                    } else { // Both node assigned
                        // Comparision:
                        if (myCurNode->score <= nodeOne->score) { // myCureNode < nodeOne < nodeTwo
                            continue;
                        }
                        else if (nodeOne->score < myCurNode->score && myCurNode->score <= nodeTwo->score) {
                            nodeOne = myCurNode;
                        }
                        else {
                            nodeOne = nodeTwo;
                            nodeTwo = myCurNode;
                        }
                    }

                    myCurNode = NULL;
                    delete myCurNode;
                }

                // Delete unecessary node
                for (unsigned int l = 0; l < curParent->children.size(); l++) {
                    curParent->children[l] = NULL;
                    delete curParent->children[l];
                }
                curParent->children.clear();
                curParent->children.shrink_to_fit();

                // Assigning 2 best nodes
                if (nodeOne != NULL) { nodeOne->parent = curParent; curParent->children.push_back(nodeOne); bestNode = nodeOne; curScore = nodeOne->score; }
                if (nodeTwo != NULL) { nodeTwo->parent = curParent; curParent->children.push_back(nodeTwo); bestNode = nodeTwo; curScore = nodeTwo->score; }
                if (nodeOne == NULL && nodeTwo == NULL) { bestNode = curParent; curScore = curParent->score; };
                
                // Delete tmpUsingNode
                curParent = NULL; nodeOne = NULL; nodeTwo = NULL;
                delete curParent; delete nodeOne; delete nodeTwo;
            }
        }
    }
    
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    cout << "Nodes: " << myNode << " Depth 4: " << float(exec_time) << "s" << endl;
    
    curScore = -10000;
    /*--Depth5--*/
    #pragma omp parallel for
    for (unsigned int i = 0; i < boardTree.root->children.size(); i++) {   // Depth 1
        //#pragma omp parallel for
        for (unsigned int j = 0; j < boardTree.root->children[i]->children.size(); j++) {  // Depth 2
            //#pragma omp parallel for
            for (unsigned int k = 0; k < boardTree.root->children[i]->children[j]->children.size(); k++) { // Depth 3
                for (unsigned int l = 0; l < boardTree.root->children[i]->children[j]->children[k]->children.size(); l++) { // Depth 4
                    nextStates(boardTree.root->children[i]->children[j]->children[k]->children[l]->board, boardTree.root->children[i]->children[j]->children[k]->children[l], boardTree.root->children[i]->children[j]->children[k], curScore, bestNode);
                }
            }
        }
    }
    
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    cout << "Nodes: " << myNode << " Depth 5: " << float(exec_time) << "s" << endl;
    
    curScore = -10000;
    /*--Depth6--*/
    #pragma omp parallel for
    for (unsigned int i = 0; i < boardTree.root->children.size(); i++) {   // Depth 1
        //#pragma omp parallel for
        for (unsigned int j = 0; j < boardTree.root->children[i]->children.size(); j++) {  // Depth 2
            //#pragma omp parallel for
            for (unsigned int k = 0; k < boardTree.root->children[i]->children[j]->children.size(); k++) { // Depth 3
                //#pragma omp parallel for
                for (unsigned int l = 0; l < boardTree.root->children[i]->children[j]->children[k]->children.size(); l++) { // Depth 4
                    for (unsigned int m = 0; m < boardTree.root->children[i]->children[j]->children[k]->children[l]->children.size(); m++) { // Depth 5
                        nextStates(boardTree.root->children[i]->children[j]->children[k]->children[l]->children[m]->board, boardTree.root->children[i]->children[j]->children[k]->children[l]->children[m], boardTree.root->children[i]->children[j]->children[k]->children[l], curScore, bestNode);
                    }
                }
            }
        }
    }
    
//    ftime = omp_get_wtime();
//    exec_time = ftime - itime;
//    cout << "Nodes: " << myNode << " Time: " << float(exec_time) << "s" << endl;
//    cout << "Time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    //cout << "Nodes: " << myNode << endl;
//    cout << "Size of 1 node: " << sizeof(boardTree.root) << endl;
//    cout << "Size of 1 board: " << sizeof(boardTree.root->board) << endl;
    
    cout << "---------------------------------" << endl;
    cout << "Cur Score: " << curScore << endl;
    cout << "AI suggested moves: " << endl;
    
    if (bestNode != NULL) {
        Node * tmpNode = bestNode;
        Node * prevNode = bestNode;
        stack<Node *> tmpStack;
        
        while (tmpNode->parent != NULL) {
            tmpStack.push(tmpNode);
            prevNode = tmpNode;
            tmpNode = tmpNode->parent;
        }
        
        while (!tmpStack.empty()) {
            if (tmpStack.top() != NULL) {
                printBoard(tmpStack.top()->board.cb);
            }
            else {
                cout << "No suggested moves! " << endl;
            }
            tmpStack.pop();
        }
        
        bestNode = prevNode;
        
        
        prevNode = NULL;
        delete prevNode;
        tmpNode = NULL;
        delete tmpNode;
    }
    
    cout << "---------------------------------" << endl;
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    cout << "Nodes: " << myNode << " Depth 6: " << float(exec_time) << "s" << endl;
    cout << "Size of Tree: " << myNode*sizeof(boardTree.root) / 1000000.0 << "mb "  << endl;
    cout << "---------------------------------" << endl;
    
//    cout << "One Possible branch: " << endl;
//    int depth1 = rand() % boardTree.root->children.size();
//    printBoard(boardTree.root->children[depth1]->board.cb);
//
//    int depth2 = rand() % boardTree.root->children[depth1]->children.size();
//    printBoard(boardTree.root->children[depth1]->children[depth2]->board.cb);
//
//    int depth3 = rand() % boardTree.root->children[depth1]->children[depth2]->children.size();
//    printBoard(boardTree.root->children[depth1]->children[depth2]->children[depth3]->board.cb);
//
//    int depth4 = rand() % boardTree.root->children[depth1]->children[depth2]->children[depth3]->children.size();
//    printBoard(boardTree.root->children[depth1]->children[depth2]->children[depth3]->children[depth4]->board.cb);
    
//    int depth5 = rand() % boardTree.root->children[depth1]->children[depth2]->children[depth3]->children[depth4]->children.size();
//    printBoard(boardTree.root->children[depth1]->children[depth2]->children[depth3]->children[depth4]->children[depth5]->board.cb);
    
//    int depth6 = rand() % boardTree.root->children[depth1]->children[depth2]->children[depth3]->children[depth4]->children[depth5]->children.size();
//    printBoard(boardTree.root->children[depth1]->children[depth2]->children[depth3]->children[depth4]->children[depth5]->children[depth6]->board.cb);
    
    myNode = 1;
}


vector<char> readBoard(char *filename)
{   
    cout<<"Reading file"<<endl;
    vector<char> Board(SIZE, '-'); 
    int i = 0;
    int j = 56;
    int k = 0;
    FILE *fp = fopen(filename,"r");
    fseek(fp,5,SEEK_SET);
     do
    {
        // Taking input single character at a time
        char c = fgetc(fp);
        if(c != '\n' && c != '\r'){
            Board[i+j] = c;
            i++;
            if (i % 8 == 0 && i != 0){
                j = j - 8;
                i = 0;   
            }
            // Tracks size 
            k++;
        }
        // Checking for end of file
        if (k == SIZE)
            break;
    }  while(1);
    fclose(fp);
    cout<<"Reading file completed"<<endl;
    return Board;
}

void writeBoard(char *filename, vector<Board> &allPossibleBoards){
    FILE *fp = fopen(filename, "w");
    int numNode = 0;
    for(unsigned int k = 0; k < allPossibleBoards.size();k++){
        for (int i = 7; i >= 0; i--)
        {
            for (int j = 0; j < 8; j++)
            {   
                putc(allPossibleBoards[k].cb[i * 8 + j], fp);
            }
            putc('\n',fp);
            
        }
        putc('\n',fp);
        numNode++;
    }
    fprintf(fp, "Total amount of possible boards is: %d \n", numNode);
    fclose(fp);
}


// Print playing chessboard 8x8 in viewer's eyes
void printBoard(const vector<char> &currentBoard)
{   
    for (int i = 7; i >= 0; i--)
    {
        cout << i+1 << "| " ;
        for (int j = 0; j < 8; j++)
        {
            cout << currentBoard[i * 8 + j] << " ";
        }
        cout << endl;
    }
    cout << "   ---------------" << endl;
    cout << "   ";
    for (int i = 0; i < 8; i++) {
        cout << char(97+i) << ' ' ;
    }
    cout << endl;
//    cout << "---------------" << endl;
}

void nextStates(const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode) {
    // Calculate all squares of the board
    for (unsigned int i = 0; i < SIZE; i++) {
        // if there is a piece and the pice is white, calculate next move, push result
        if (isNotEmpty(board.cb[i]) && ( (board.turn==0 && isWhite(board.cb[i])) || (board.turn==1 && isBlack(board.cb[i])) ) ) {
            switch (board.cb[i])
            {
            case 'P':
            case 'p':
                // Case Pawn
                    calculatePawnMoves(board.cb[i], i, board, curNode, parent, curScore, bestNode);
                    break;
            case 'N':
            case 'n':
                // Case Knight
                    calculateKnightMoves(board.cb[i], i, board, curNode, parent, curScore, bestNode);
                    break;
            case 'R':
            case 'r':
                // Case Rook
                    calculateRookMoves(board.cb[i], i, board, curNode, parent, curScore, bestNode);
                    break;
            case 'B':
            case 'b':
                // Case Bishop
                
                    calculateBishopMoves(board.cb[i], i, board, curNode, parent, curScore, bestNode);
                    break;
            case 'Q':
            case 'q':
                // Case Queen
                    calculateQueenMoves(board.cb[i], i, board, curNode, parent, curScore, bestNode);
                    break;
            case 'K':
            case 'k':
                // Case King
                    calculateKingMoves(board.cb[i], i, board, curNode, parent, curScore, bestNode);
                break;
            default:
                break;
            }
        }
    }
}



// Calculate all possible moves of this Pawn given pos and currentBoard.
// If there are possible move(s), push the next state to children of curNode (pass by reference).
void calculatePawnMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode)
{
    int row = pos / 8;
    int col = pos % 8;
    
    // White Pawn
    if (isWhite(piece)) {
        if (pos / 8 == 8) return; // take care of stupid case (whitePawn at row 8)
        
        // White Pawn at previous-to-promote rank
        if (pos / 8 == 6) {
            // Pawn move forward and promote
            if (board.cb[pos+8] == '-') {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateStates(pos, pos+8, piece, promotionList[i], board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
                }
            }
            // Check for ability to capture and promote
            // If up left square is valid and has a black piece
            int posUL = (row+1)*8 + col-1;
            if (row+1 < 8 && col-1 >= 0 && isNotEmpty(board.cb[posUL]) && isBlack(board.cb[posUL]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateStates(pos, posUL, piece, promotionList[i], board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
                }
            }
            // If up right square is valid and has a black piece
            int posUR = (row+1)*8 + col+1;
            if (row+1 < 8 && col+1 < 8 && isNotEmpty(board.cb[posUL]) && isBlack(board.cb[posUR]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateStates(pos, posUR, piece, promotionList[i], board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
                }
            }
            return;
        }
        
        // -- // White Pawn at rank 5 and check for En Passant
        if ( (pos / 8 == 4) && board.lm.piece == 'p' && (board.lm.start - board.lm.end == 16) && (board.lm.end - pos == 1 || int(board.lm.end) - int(pos) == -1 ) ) {
            vector<char> nb = board.cb;
            nb[board.lm.end] = '-';
            int nextPos = (board.lm.start + board.lm.end) / 2;
            updateStates(pos, nextPos, piece, piece, nb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        
        // -- //  White Pawn at regular rank
        // Pawn at starting square and the forward two squares is empty
        if (pos / 8 == 1 && board.cb[pos+8] == '-' && board.cb[pos+16] == '-') {
            updateStates(pos, pos+16, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        // If forward square is valid
        if (board.cb[pos+8] == '-') {
            updateStates(pos, pos+8, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        // If up left square is valid and not empty and has a black piece
        int posUL = (row+1)*8 + col-1;
        if (row+1 < 8 && col-1 >= 0 && isNotEmpty(board.cb[posUL]) && isBlack(board.cb[posUL]) ) {
            updateStates(pos, posUL, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        // If up right square is valid and not empty and  has a black piece
        int posUR = (row+1)*8 + col+1;
        if (row+1 < 8 && col+1 < 8 && isNotEmpty(board.cb[posUR]) && isBlack(board.cb[posUR]) ) {
            updateStates(pos, posUR, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
    }
    // Black Pawn
    else {
        if (pos / 8 == 0) return; // take care of stupid case (blackPawn at row 8)
        
        // -- //  Black Pawn at previous-to-promote rank
        if (pos / 8 == 1) {
            // Pawn move forward and promote
            if (board.cb[pos-8] == '-') {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateStates(pos, pos-8, piece, promotionList[i], board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
                    
                }
            }
            // Check for ability to capture and promote
            // If up left square is valid and has a black piece
            int posDL = (row-1)*8 + col-1;
            if (row-1 >= 0 && col-1 >= 0 && isNotEmpty(board.cb[posDL]) && isWhite(board.cb[posDL]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateStates(pos, posDL, piece, promotionList[i], board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
                }
            }
            // If up right square is valid and has a black piece
            int posDR = (row-1)*8 + col+1;
            if (row-1 >= 0 && col+1 < 8 && isNotEmpty(board.cb[posDR]) && isWhite(board.cb[posDR]) ) {
                for (int i = 0; i < PROMOTIONLISTSIZE; i++) {
                    updateStates(pos, posDR, piece, promotionList[i], board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
                }
            }
            return;
        }
        
        // -- // Black Pawn at rank 4 and check for En Passant
        if ( (pos / 8 == 3) && board.lm.piece == 'P' && (board.lm.end - board.lm.start == 16) && (board.lm.end - pos == 1 || int(board.lm.end) - int(pos) == -1) ) {
            vector<char> nb = board.cb;
            nb[board.lm.end] = '-';
            int nextPos = (board.lm.start + board.lm.end) / 2;
            updateStates(pos, nextPos, piece, piece, nb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        
        // -- //  Black Pawn at regular rank
        // Pawn at starting square and the forward two squares is empty
        if (pos / 8 == 6 && board.cb[pos-8] == '-' && board.cb[pos-16] == '-') {
            updateStates(pos, pos-16, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        // If forward square is valid
        if (board.cb[pos-8] == '-') {
            updateStates(pos, pos-8, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        // If up left square is valid and not empty and has a black piece
        int posDL = (row-1)*8 + col-1;
        if (row-1 >= 0 && col-1 >= 0 && isNotEmpty(board.cb[posDL]) && isWhite(board.cb[posDL]) ) {
            updateStates(pos, posDL, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        // If up right square is valid and not empty and  has a black piece
        int posDR = (row-1)*8 + col+1;
        if (row-1 >= 0 && col+1 < 8 && isNotEmpty(board.cb[posDR]) && isWhite(board.cb[posDR]) ) {
            updateStates(pos, posDR, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
    }
}


// Calculate all possible moves of this Knight given pos and currentBoard.
// If there are possible move(s), push the next state to children of curNode (pass by reference).
void calculateKnightMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode)
{
    // nnp holds Next (legal) Knight Positions
    vector<int> nnp;
    //int validPos;
    
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
    
    for (unsigned int i = 0; i < nnp.size(); i++) {
        int n = nnp[i];
        // if n onBoard && currentBoard at n is Empty || (currentBoard at n is not empty but piece are on different sides )
        // then add new next states of the board to children of curNode.
        if ((board.cb[n] == '-') || ( isNotEmpty(board.cb[n]) && isDifferentSide(piece, board.cb[n])) ) {
            updateStates(pos, n, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
    }
}


// Calculate all possible moves of this Rook given pos and currentBoard.
// If there are possible move(s), push the next state to curNode (pass by reference).
void calculateRookMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode)
{ 
    int row = pos / 8;
    int col = pos % 8;

    //Rook forward movement
    int fwd = row + 1;
    while(board.cb[8*fwd+col] == '-'  && fwd < 8) {
            updateStates(pos, 8*fwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
            fwd++;
        }
    // Rook forward capture piece
    if (isDifferentSide(piece, board.cb[8*fwd+col]) && fwd < 8)
    {
       updateStates(pos, 8*fwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }
    
     //Rook backward movement
    int bwd = row - 1;
    while(board.cb[8*bwd+col] == '-'  && bwd >= 0) {
            updateStates(pos, 8*bwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
            bwd--;
        }


    // Rook backward capture piece
    if (isDifferentSide(piece,board.cb[8*bwd+col]) && bwd >= 0)
    {
        updateStates(pos, 8*bwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }

    // Rook right movement
    int rw = col + 1;
    while(board.cb[8*row+rw] == '-' && rw < 8){
        updateStates(pos, 8*row+rw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        rw++;
    }
    if (isDifferentSide(piece,board.cb[8*row+rw]) && rw < 8)
    {
       updateStates(pos, 8*row+rw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }

    // Rook left movement
    int lw = col - 1;
    while(board.cb[8*row+lw] == '-' && lw >= 0) {
        updateStates(pos, 8*row+lw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        lw--;
    }
    if (isDifferentSide(piece,board.cb[8*row+lw]) && lw >= 0)
    {   
        updateStates(pos, 8*row+lw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }
}

// Calculate all possible moves of this Bishop given pos and currentBoard.
// If there are possible move(s), push the next state to curNode (pass by reference).
void calculateBishopMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode)
{   
    int row = pos / 8;
    int col = pos % 8;
    
    // Forward diagonal right
   while(board.cb[8*(row+1)+col+1] == '-' && (row+1 < 8 && col+1 < 8)) {
       updateStates(pos, 8*(row+1)+col+1, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row++;
       col++;
   }
   // Capture forward diagonal right
   if (isDifferentSide(piece,board.cb[8*(row+1)+col+1]) && (row + 1 < 8 && col + 1 < 8)) {
       updateStates(pos, 8*(row+1)+col+1, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }

   // Forward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(board.cb[8*(row+1)+(col-1)] == '-' && row+1 < 8 && col > 0) {
       updateStates(pos, 8*(row+1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row++;
       col--;
   }
   // Capture forward diagonal left
   if (isDifferentSide(piece,board.cb[8*(row+1)+col-1]) && row+1 < 8 && col > 0){
        updateStates(pos, 8*(row+1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }

   // Backward diagonal right
   row = pos / 8;
   col = pos % 8;
   while(board.cb[8*(row-1)+(col+1)] == '-' && row > 0 && col+1 < 8) {
       updateStates(pos, 8*(row-1)+(col+1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row--;
       col++;
   }
   // Capture Backward diagonal right
    if (isDifferentSide(piece,board.cb[8*(row-1)+col+1]) && row > 0 && col+1 < 8){
        updateStates(pos, 8*(row-1)+(col+1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }
   // Backward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(board.cb[8*(row-1)+(col-1)] == '-' && row > 0 && col > 0) {
       updateStates(pos, 8*(row-1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row--;
       col--;
   }
   // Capture Backward diagonal left
    if (isDifferentSide(piece,board.cb[8*(row-1)+col-1]) && row > 0 && col > 0){
       updateStates(pos, 8*(row-1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }
}

// Calculate all possible moves of this Queen given pos and currentBoard.
// If there are possible move(s), push the next state to curNode (pass by reference).
void calculateQueenMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode)
{
    /* Write code here*/
    int row = pos / 8;
    int col = pos % 8;

    //Forward movement
    int fwd = row + 1;
    while(board.cb[8*fwd+col] == '-'  && fwd < 8) {
            updateStates(pos, 8*fwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
            fwd++;
        }
    // Forward capture piece
    if (isDifferentSide(piece, board.cb[8*fwd+col]) && fwd < 8)
    {
       updateStates(pos, 8*fwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }
    
     //Backward movement
    int bwd = row - 1;
    while(board.cb[8*bwd+col] == '-'  && bwd >= 0) {
            updateStates(pos, 8*bwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
            bwd--;
        }


    // Backward capture piece
    if (isDifferentSide(piece,board.cb[8*bwd+col]) && bwd >= 0)
    {
        updateStates(pos, 8*bwd+col, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }

    // Right movement
    int rw = col + 1;
    while(board.cb[8*row+rw] == '-' && rw < 8){
        updateStates(pos, 8*row+rw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        rw++;
    }
    if (isDifferentSide(piece,board.cb[8*row+rw]) && rw < 8)
    {
       updateStates(pos, 8*row+rw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }

    // Left movement
    int lw = col - 1;
    while(board.cb[8*row+lw] == '-' && lw >= 0) {
        updateStates(pos, 8*row+lw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        lw--;
    }
    if (isDifferentSide(piece,board.cb[8*row+lw]) && lw >= 0)
    {   
        updateStates(pos, 8*row+lw, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
    }
  
   // Forward diagonal right
   while(board.cb[8*(row+1)+col+1] == '-' && (row+1 < 8 && col+1 < 8)) {
       updateStates(pos, 8*(row+1)+col+1, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row++;
       col++;
   }
   // Capture forward diagonal right
   if (isDifferentSide(piece,board.cb[8*(row+1)+col+1]) && (row + 1 < 8 && col + 1 < 8)) {
       updateStates(pos, 8*(row+1)+col+1, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }

   // Forward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(board.cb[8*(row+1)+(col-1)] == '-' && row+1 < 8 && col > 0) {
       updateStates(pos, 8*(row+1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row++;
       col--;
   }
   // Capture forward diagonal left
   if (isDifferentSide(piece,board.cb[8*(row+1)+col-1]) && row+1 < 8 && col > 0){
        updateStates(pos, 8*(row+1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }

   // Backward diagonal right
   row = pos / 8;
   col = pos % 8;
   while(board.cb[8*(row-1)+(col+1)] == '-' && row > 0 && col+1 < 8) {
       updateStates(pos, 8*(row-1)+(col+1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row--;
       col++;
   }
   // Capture Backward diagonal right
    if (isDifferentSide(piece,board.cb[8*(row-1)+col+1]) && row > 0 && col+1 < 8){
        updateStates(pos, 8*(row-1)+(col+1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }
   // Backward diagonal left
   row = pos / 8;
   col = pos % 8;
   while(board.cb[8*(row-1)+(col-1)] == '-' && row > 0 && col > 0) {
       updateStates(pos, 8*(row-1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
       row--;
       col--;
   }
   // Capture Backward diagonal left
    if (isDifferentSide(piece,board.cb[8*(row-1)+col-1]) && row > 0 && col > 0){
       updateStates(pos, 8*(row-1)+(col-1), piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent, curScore, bestNode);
   }
}

// Calculate all possible moves of this King given pos and currentBoard.
// If there are possible move(s), push the next state to curNode (pass by reference).
void calculateKingMoves(char piece, int pos, const Board & board, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode)
{
    int row = pos / 8;
    int col = pos % 8;
    
    bool whiteBCP = board.turn == 0 ? false : board.wcp;
    bool blackBCP = board.turn == 1 ? false : board.bcp;
    
    // ---- // King regular moves
    //Forward
    int forward = 8*(row+1)+col;
    if(row + 1 < 8 && (board.cb[forward] == '-' || isDifferentSide(piece,board.cb[forward]))) {
        //updateStates(curPos, nextPos, piece, piece, board.cb, board.wcp, board.bcp, board.wk, board.bk, !board.turn, curNode, parent)
        int whiteWK = board.turn == 0 ? forward : board.wk;
        int blackWK = board.turn == 1 ? forward : board.bk;
        updateStates(pos, forward, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    //Backward
    int backward = 8*(row-1)+col;
    if(row - 1 >= 0 && (board.cb[backward] == '-' || isDifferentSide(piece,board.cb[backward]))) {
        int whiteWK = board.turn == 0 ? backward : board.wk;
        int blackWK = board.turn == 1 ? backward : board.bk;
        updateStates(pos, backward, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    //Right
    int right = 8*row+col+1;
    if(col + 1 < 8 && (board.cb[right] == '-' || isDifferentSide(piece,board.cb[right]))){
        int whiteWK = board.turn == 0 ? right : board.wk;
        int blackWK = board.turn == 1 ? right : board.bk;
        updateStates(pos, right, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    //Left
    int left = 8*row+col-1;
    if(col-1 >= 0 && (board.cb[left] == '-' || isDifferentSide(piece,board.cb[left]))) {
        int whiteWK = board.turn == 0 ? left : board.wk;
        int blackWK = board.turn == 1 ? left : board.bk;
        updateStates(pos, left, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    //Diagonal forward-right
    int UR = 8*(row+1)+col+1;
    if(row + 1 < 8 && col + 1 < 8 && (board.cb[UR] == '-' || isDifferentSide(piece,board.cb[UR]))){
        int whiteWK = board.turn == 0 ? UR : board.wk;
        int blackWK = board.turn == 1 ? UR : board.bk;
        updateStates(pos, UR, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    //Diagonal forward-left
    int UL = 8*(row+1)+col-1;
    if(row + 1 < 8 && col - 1 >= 0 && (board.cb[UL] == '-' || isDifferentSide(piece,board.cb[UL]))){
        int whiteWK = board.turn == 0 ? UL : board.wk;
        int blackWK = board.turn == 1 ? UL : board.bk;
        updateStates(pos, UL, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    //Diagonal backward-right
    int DR = 8*(row-1)+col+1;
    if(row - 1 >= 0 && col + 1 < 8 && (board.cb[DR] == '-' || isDifferentSide(piece,board.cb[DR]))){
        int whiteWK = board.turn == 0 ? DR : board.wk;
        int blackWK = board.turn == 1 ? DR : board.bk;
        updateStates(pos, DR, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    //Diagonal backward-left
    int DL = 8*(row-1)+col-1;
    if(row - 1 >= 0 && col - 1 >= 0 && (board.cb[DL] == '-' || isDifferentSide(piece,board.cb[DL]))){
        int whiteWK = board.turn == 0 ? DL : board.wk;
        int blackWK = board.turn == 1 ? DL : board.bk;
        updateStates(pos, DR, piece, piece, board.cb, whiteBCP, blackBCP, whiteWK, blackWK, !board.turn, curNode, parent, curScore, bestNode);
    }
    
    // ---- // King castle moves
    // If not in check, has castlePrivilege, clear path -> check square 3,5 for WhiteKing/59, 61 for BlackKing -> make a move, then updateStates takes care of pos 2,6 and 58,62.
    // White
    //cout << "Evaluate board.turn ==0: " << (board.turn == 0) << endl;
    //cout << "Evaluate board.wic == false: " << (board.wic == false) << endl;
    //cout << "Evaluate board.wcp == true: " << (board.wcp == true) << endl;
    //cout << "Evaluate board.cb[pos] == 'K': " << (board.cb[pos] == 'K') << endl;
    //cout << "Evaluate board.wk == 4: " << (board.wk == 4) << endl;
    if (board.turn == 0 && board.wic == false && board.wcp == true && board.cb[pos] == 'K' && board.wk == 4) {
        // king-side castle
        if (board.cb[7] == 'R' && board.cb[5] == '-' && board.cb[6] == '-' && !isWhiteInCheck(board.cb, 5)) {    // In path check
            vector<char> nb = board.cb;
            nb[5] = 'R'; nb[7] = '-'; // Change Rook position first, King position change in updateStates
            // Castle Move: curPos whiteKing = 4, nextPos whiteKing = 6, update whiteKing pos, whiteCastlePrivilege = false, piece is King
            updateStates(4, 6, 'K', 'K', nb, false, board.bcp, 6, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
        // queen-side castle
        if (board.cb[0] == 'R' && board.cb[1] == '-' && board.cb[2] == '-' && board.cb[3] == '-' && !isWhiteInCheck(board.cb, 3)) { // In path check
            vector<char> nb = board.cb;
            nb[3] = 'R'; nb[0] = '-'; // Change Rook position first, King position change in updateStates
            // Castle Move: curPos whiteKing = 4, nextPos whiteKing = 2, update whiteKing pos, whiteCastlePrivilege = false, piece is King
            updateStates(4, 2, 'K', 'K', nb, false, board.bcp, 2, board.bk, !board.turn, curNode, parent, curScore, bestNode);
        }
    }
    // Black
    if (board.turn == 1 && board.bic == false && board.bcp == true && board.cb[pos] == 'k' && board.bk == 60) {
        // king-side castle
        if (board.cb[63] == 'r' && board.cb[61] == '-' && board.cb[62] == '-' && !isBlackInCheck(board.cb, 61)) {    // In path check
            vector<char> nb = board.cb;
            nb[61] = 'r'; nb[63] = '-'; // Change Rook position first, King position change in updateStates
            // Castle Move: curPos blackKing = 60, nextPos blackKing = 62, update blackKing pos, blackCastlePrivilege = false, piece is King
            updateStates(60, 62, 'k', 'k', nb, board.wcp, false, board.wk, 62, !board.turn, curNode, parent, curScore, bestNode);
        }
        // queen-side castle
        if (board.cb[56] == 'r' && board.cb[57] == '-' && board.cb[58] == '-' && board.cb[59] == '-' && !isBlackInCheck(board.cb, 59)) {    // In path check
            vector<char> nb = board.cb;
            nb[59] = 'r'; nb[56] = '-'; // Change Rook position first, King position change in updateStates
            // Castle Move: curPos blackKing = 60, nextPos blackKing = 58, update blackKing pos, blackCastlePrivilege = false, piece is King
            updateStates(60, 58, 'k', 'k', nb, board.wcp, false, board.wk, 58, !board.turn, curNode, parent, curScore, bestNode);
        }
    }
}

void updateStates(int curPos, int nextPos, char curPiece, char nextPiece, vector<char> newBoard, bool wcp, bool bcp, unsigned int wk, unsigned int bk, bool t, Node* & curNode, Node* & parent, int & curScore, Node* & bestNode) {
    // making new move
    newBoard[curPos] = '-';
    newBoard[nextPos] = nextPiece;
    LAST_MOVE myLM; myLM.piece = curPiece; myLM.start = curPos; myLM.end = nextPos;
    
    bool isWIC = isWhiteInCheck(newBoard, wk);
    bool isBIC = isBlackInCheck(newBoard, bk);
    
    if ( (isWIC && t == 1) || (isBIC && t == 0)) {
        return;
    }
    else {
        Board myNextBoard(newBoard, myLM, wcp, bcp, isWIC, isBIC, wk, bk, t);
        int myScore = calculateScoreCurBoard(myNextBoard);
        insert(myNextBoard, curNode, parent, myScore, curScore, bestNode);
    }
}

void insert(const Board & b, Node* & curNode, Node* & parent, const int & myScore, int & curScore, Node* & bestNode) {
    Node *n = new Node;
    n->board = b;
    n->score = myScore + curNode->score;
    n->parent = curNode;
    curNode->children.push_back(n);
    
    if (curScore <= n->score) {
        curScore = n->score;
        bestNode = n;
    }
    myNode++;
}

int calculateScoreCurBoard(const Board & curBoard) {
    srand(time(NULL));
    
    int res = 0;
    int whitePiece = 0; int whitePos = 0; int whiteScore = 0;
    int blackPiece = 0; int blackPos = 0; int blackScore = 0;

    for (unsigned int i = 0; i < curBoard.cb.size(); i++) {
        switch (curBoard.cb[i]){
            case 'P': whitePiece += PAWN_SCORE; whitePos += W_PAWN_POS[i];
            case 'p': blackPiece += PAWN_SCORE; blackPos += B_PAWN_POS[i];
            case 'N': whitePiece += KNIGHT_SCORE; whitePos += KNIGHT_POS[i];
            case 'n': blackPiece += KNIGHT_SCORE; blackPos += KNIGHT_POS[i];
            case 'R': whitePiece += ROOK_SCORE; whitePos += W_ROOK_POS[i];
            case 'r': blackPiece += ROOK_SCORE; blackPos += B_ROOK_POS[i];
            case 'B': whitePiece += BISHOP_SCORE; whitePos += W_PAWN_POS[i];
            case 'b': blackPiece += BISHOP_SCORE; blackPos += B_PAWN_POS[i];
            case 'Q': whitePiece += QUEEN_SCORE; whitePos += W_QUEEN_POS[i];
            case 'q': blackPiece += QUEEN_SCORE; blackPos += B_QUEEN_POS[i];
            case 'K': whitePiece += KING_SCORE; whitePos += W_KING_POS[i];
            case 'k': blackPiece += KING_SCORE; blackPos += B_KING_POS[i];
            default:
                break;
        }
    }

    whiteScore = whitePiece + whitePos;
    blackScore = blackPiece + blackPos;

    if (curBoard.turn == 0) {
        res = whiteScore - blackScore;
    } else {
        res = blackScore - whiteScore;
    }
    res = rand() % 200 - 100;
    return res;
}

// Branching the king. If meet the same piece using according movement, then you're in check
bool isWhiteInCheck(const vector<char> & cb, int pos) {
    if (pos > 63) { return false; }  // No King on Board
    
    // Converting pos (1D) to row and column (2D) by formula: pos = row * 8 + col;
    int row = pos / 8;
    int col = pos % 8;
    
    char ep = '-';  // Encounter piece
    
    // King:
    if (    (row+1 < 8 && col-1 >= 0 && cb[(row+1)*8 + col-1] == 'k')
        ||  (row+1 < 8 && cb[(row+1)*8 + col] == 'k')
        ||  (row+1 < 8 && col+1 < 8 && cb[(row+1)*8 + col+1] == 'k')
        ||  (col-1 >= 0 && cb[row*8 + col-1] == 'k')
        ||  (col+1 < 8 && cb[row*8 + col+1] == 'k')
        ||  (row-1 >= 0 && col-1 >=0 && cb[(row-1)*8 + col-1] == 'k')
        ||  (row-1 >= 0 && cb[(row-1)*8 + col] == 'k')
        ||  (row-1 >= 0 && col+1 < 8 && cb[(row-1)*8 + col+1] == 'k')
        )
    { return true; }
    
    // Pawn
    int posUL = (row+1)*8 + col-1;
    if (row+1 < 8 && col-1 >= 0 && cb[posUL] == 'p') {
        return true;
    }
    int posUR = (row+1)*8 + col+1;
    if (row+1 < 8 && col+1 >= 0 && cb[posUR] == 'p') {
        return true;
    }
    
    // Knight:
    if (    (row+1 < 8 && col-2 >= 0 && cb[(row+1)*8 + col-2] == 'n')
        ||  (row+1 < 8 && col+2 < 8 && cb[(row+1)*8 + col+2] == 'n')
        ||  (row+2 < 8 && col-1 >= 0 && cb[(row+2)*8 + col-1] == 'n')
        ||  (row+2 < 8 && col+1 < 8 && cb[(row+2)*8 + col+1] == 'n' )
        ||  (row-1 >= 0 && col-2 >= 0 && cb[(row-1)*8 + col-2] == 'n')
        ||  (row-1 >= 0 && col+2 < 8 && cb[(row-1)*8 + col+2] == 'n')
        ||  (row-2 >= 0 && col-1 >= 0 && cb[(row-2)*8 + col-1] == 'n')
        ||  (row-2 >= 0 && col+1 < 8 && cb[(row-2)*8 + col+1] == 'n') )
    { return true; }
    
    // Vertical - Rook, Queen:
    // Vertical Up
    ep = '-';
    for (int i = 1; row + i < 8; i++) {
        char curPiece = cb[(row+i)*8 + col];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'r' || ep == 'q') { return true; }
    // Vertical Down
    ep = '-';
    for (int i = 1; row - i >= 0; i++) {
        char curPiece = cb[(row-i)*8 + col];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'r' || ep == 'q') { return true; }
    
    // Horizontal - Rook, Queen:
    // Horizontal right
    ep = '-';
    for (int i = 1; col + i < 8; i++) {
        char curPiece = cb[row*8 + col+i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'r' || ep == 'q') { return true; }
    // Horizontal left
    ep = '-';
    for (int i = 1; col - i >= 0; i++) {
        char curPiece = cb[row*8 + col-i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'r' || ep == 'q') { return true; }
    
    // Diagonal - Rook, Queen:
    // Diagonal Up Right
    ep = '-';
    for (int i = 1; row + i < 8 && col + i < 8; i++) {
        char curPiece = cb[(row+i)*8 + col+i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'b' || ep == 'q') { return true; }
    // Diagonal Up Left
    ep = '-';
    for (int i = 1; row + i < 8 && col - i >= 0; i++) {
        char curPiece = cb[(row+i)*8 + col-i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'b' || ep == 'q') { return true; }
    // Diagonal Down Right
    ep = '-';
    for (int i = 1; row - i >= 0 && col + i < 8; i++) {
        char curPiece = cb[(row-i)*8 + col+i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'b' || ep == 'q') { return true; }
    // Diagonal Down Left
    ep = '-';
    for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
        char curPiece = cb[(row-i)*8 + col-i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'b' || ep == 'q') { return true; }
    
    
    return false;
}

bool isBlackInCheck(const vector<char> & cb, int pos) {
    if (pos > 63) { return false; }  // No King on Board
    
    // Converting pos (1D) to row and column (2D) by formula: pos = row * 8 + col;
    int row = pos / 8;
    int col = pos % 8;
    
    char ep = '-';  // Encounter piece
    
    // king:
    if (    (row+1 < 8 && col-1 >= 0 && cb[(row+1)*8 + col-1] == 'K')
        ||  (row+1 < 8 && cb[(row+1)*8 + col] == 'K')
        ||  (row+1 < 8 && col+1 < 8 && cb[(row+1)*8 + col+1] == 'K')
        ||  (col-1 >= 0 && cb[row*8 + col-1] == 'K')
        ||  (col+1 < 8 && cb[row*8 + col+1] == 'K')
        ||  (row-1 >= 0 && col-1 >=0 && cb[(row-1)*8 + col-1] == 'K')
        ||  (row-1 >= 0 && cb[(row-1)*8 + col] == 'K')
        ||  (row-1 >= 0 && col+1 < 8 && cb[(row-1)*8 + col+1] == 'K')
        )
    { return true; }
    
    // Pawn:
    int posDL = (row-1)*8 + col-1;
    if (row-1 >= 0 && col-1 >= 0 && cb[posDL] == 'P') {
        return true;
    }
    unsigned int posDR = (row-1)*8 + col+1;
    if (row-1 >= 0 && col+1 >= 0 && cb[posDR] == 'P') {
        return true;
    }
    
    // Knight:
    if ( (row+1 < 8 && col-2 >= 0 && cb[(row+1)*8 + col-2] == 'N')
        || (row+1 < 8 && col+2 < 8 && cb[(row+1)*8 + col+2] == 'N')
        || (row+2 < 8 && col-1 >= 0 && cb[(row+2)*8 + col-1] == 'N')
        || (row+2 < 8 && col+1 < 8 && cb[(row+2)*8 + col+1] == 'N' )
        || (row-1 >= 0 && col-2 >= 0 && cb[(row-1)*8 + col-2] == 'N')
        || (row-1 >= 0 && col+2 < 8 && cb[(row-1)*8 + col+2] == 'N')
        || (row-2 >= 0 && col-1 >= 0 && cb[(row-2)*8 + col-1] == 'N')
        || (row-2 >= 0 && col+1 < 8 && cb[(row-2)*8 + col+1] == 'N') )
    { return true; }
    
    // Vertical - Rook, Queen:
    // Vertical Up
    ep = '-';
    for (int i = 1; row + i < 8; i++) {
        char curPiece = cb[(row+i)*8 + col];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'R' || ep == 'Q') { return true; }
    // Vertical Down
    ep = '-';
    for (int i = 1; row - i >= 0; i++) {
        char curPiece = cb[(row-i)*8 + col];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'R' || ep == 'Q') { return true; }
    
    // Horizontal - Rook, Queen:
    // Horizontal right
    ep = '-';
    for (int i = 1; col + i < 8; i++) {
        char curPiece = cb[row*8 + col+i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'R' || ep == 'Q') { return true; }
    // Horizontal left
    ep = '-';
    for (int i = 1; col - i >= 0; i++) {
        char curPiece = cb[row*8 + col-i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'R' || ep == 'Q') { return true; }
    
    // Diagonal - Bishop, Queen:
    // Diagonal Up Right
    ep = '-';
    for (int i = 1; row + i < 8 && col + i < 8; i++) {
        char curPiece = cb[(row+i)*8 + col+i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'B' || ep == 'Q') { return true; }
    // Diagonal Up Left
    ep = '-';
    for (int i = 1; row + i < 8 && col - i >= 0; i++) {
        char curPiece = cb[(row+i)*8 + col-i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'B' || ep == 'Q') { return true; }
    // Diagonal Down Right
    ep = '-';
    for (int i = 1; row - i >= 0 && col + i < 8; i++) {
        char curPiece = cb[(row-i)*8 + col+i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'B' || ep == 'Q') { return true; }
    // Diagonal Down Left
    ep = '-';
    for (int i = 1; row - i >= 0 && col - i >= 0; i++) {
        char curPiece = cb[(row-i)*8 + col-i];
        if (curPiece != '-') {
            ep = curPiece; break;
        }
    }
    if (ep == 'B' || ep == 'Q') { return true; }
    
    return false;
}

int convertChessSquare(const string & s) {
    int row = s[1] - 48 - 1;
    int col = s[0] - 97;
    
    return (row * 8 + col);
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


//int checkPosScore(int pos){
//    vector<int> score = [
//    10,10,10,10,10,10,10,10,
//    10,10,10,10,10,10,10,10,
//    10,20,45,45,45,45,20,10,
//    10,20,45,90,90,45,20,10,
//    10,20,45,90,90,45,20,10,
//    10,20,45,45,45,45,20,10,
//    10,10,10,10,10,10,10,10,
//    10,10,10,10,10,10,10,10,
//    ];
//    return score[pos];
//}
            
        
