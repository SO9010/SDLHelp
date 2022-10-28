
#ifndef TestCpp1_hpp
#define TestCpp1_hpp

#include <iostream>
#include <array>
#include <iostream>
#include <vector>
#include "Pieces.hpp"
using namespace std;

class Game {
    
private:
    vector<vector<Piece>> board;
    Piece emptyInstance = Piece();
    bool whiteToMove;
    bool checkmate;
    bool stalemate;
    
    
public:
    Game(){
        this->PopulateBoard();
        this->InstantiatePieces();

        whiteToMove = true;
        checkmate = false;
        stalemate = false;
    }
    
    void PopulateBoard(){
        board.resize(8, vector<Piece>(8, emptyInstance));
    }
    
    void InstantiatePieces(){
        map <int, string> piecesTable = {{0, "Rook"}, {1, "Knight"}, {2, "Bishop"}};

        for(int i=0; i<board.size(); i++){
            board[1][i] = Piece("Pawn", "black");
            board[6][i] = Piece("Pawn", "white");
            if(i < 3){
                board[0][i] = Piece(piecesTable[i], "black");
                board[0][7-i] = Piece(piecesTable[i], "black");
                board[7][i] = Piece(piecesTable[i], "white");
                board[7][7-i] = Piece(piecesTable[i], "white");
            }
        }
        board[0][3] = Piece("Queen", "black");
        board[7][3] = Piece("Queen", "white");
        board[0][4] = Piece("King", "black");
        board[7][4] = Piece("King", "white");
    }
    
    
    static Piece EmptySquare(){
        return Piece();
    }
    
    vector<vector<Piece>> GetBoard(){
        return this->board;
    }
    
};


#endif
